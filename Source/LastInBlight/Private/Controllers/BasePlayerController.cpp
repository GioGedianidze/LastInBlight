// Fill out your copyright notice in the Description page of Project Settings.

#include "Controllers/BasePlayerController.h"
#include "EnhancedInputSubsystemInterface.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interaction/EnemyInterface.h"
#include "Kismet/KismetSystemLibrary.h"

ABasePlayerController::ABasePlayerController()
{
}

void ABasePlayerController::PlayerTick(float DeltaTime)
{
    Super::PlayerTick(DeltaTime);
    CursorTrace();
}

void ABasePlayerController::BeginPlay()
{
    Super::BeginPlay();

    check(BaseContext);

    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    if (Subsystem)
    {
        Subsystem->AddMappingContext(BaseContext, 0);
    }
    bShowMouseCursor = true;

    FInputModeGameAndUI InputModeData;
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    InputModeData.SetHideCursorDuringCapture(false);
    SetInputMode(InputModeData);
}

void ABasePlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
    EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABasePlayerController::Move);
}

void ABasePlayerController::Move(const FInputActionValue& InputActionValue)
{
    const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
    
    if (!InputAxisVector.IsNearlyZero())
    {
        constexpr float Radians = PI / 4.0f;
        const float CosTheta = FMath::Cos(Radians);
        const float SinTheta = FMath::Sin(Radians);

        const float RotatedX = InputAxisVector.X * CosTheta - InputAxisVector.Y * SinTheta;
        const float RotatedY = InputAxisVector.X * SinTheta + InputAxisVector.Y * CosTheta;

        // Store the normalized input direction
        LastInputDirection = FVector2D(RotatedX, RotatedY).GetSafeNormal();

        if (APawn* ControlledPawn = GetPawn<APawn>())
        {
            ControlledPawn->AddMovementInput(FVector(1, 0, 0), RotatedX);
            ControlledPawn->AddMovementInput(FVector(0, 1, 0), RotatedY);
        }
    }
    else
    {
        // Reset input direction when there's no input
        LastInputDirection = FVector2D::ZeroVector;
    }
}

void ABasePlayerController::CursorTrace()
{
    // Check for cursor hit (mouse/keyboard priority)
    FHitResult CursorHit;
    GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
    TScriptInterface<IEnemyInterface> CursorEnemy = nullptr;

    if (CursorHit.bBlockingHit)
    {
        AActor* HitActor = CursorHit.GetActor();
        if (HitActor && HitActor->Implements<UEnemyInterface>())
        {
            CursorEnemy = HitActor;
        }
    }

    TScriptInterface<IEnemyInterface> BestEnemy = nullptr;

    if (CursorEnemy)
    {
        BestEnemy = CursorEnemy; // Cursor takes priority
    }
    else if (!LastInputDirection.IsNearlyZero())
    {
        // Auto-targeting for controller input
        TArray<AActor*> OverlappingActors;
        TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
        ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
        TArray<AActor*> ActorsToIgnore;
        ActorsToIgnore.Add(GetPawn());

        UKismetSystemLibrary::SphereOverlapActors(
            GetWorld(),
            GetPawn()->GetActorLocation(),
            AutoTargetRadius,
            ObjectTypes,
            AActor::StaticClass(),
            ActorsToIgnore,
            OverlappingActors
        );

        float MaxScore = -1.f;
        const float DotProductThreshold = 0.5f; // Only highlight enemies within ~60 degrees of input direction

        for (AActor* Actor : OverlappingActors)
        {
            if (Actor && Actor->Implements<UEnemyInterface>())
            {
                FVector PlayerLocation = GetPawn()->GetActorLocation();
                FVector EnemyLocation = Actor->GetActorLocation();
                FVector2D DirectionToEnemy = FVector2D(EnemyLocation.X - PlayerLocation.X, EnemyLocation.Y - PlayerLocation.Y).GetSafeNormal();
                float DotProduct = FVector2D::DotProduct(LastInputDirection, DirectionToEnemy);

                // Only consider enemies with a sufficiently high dot product
                if (DotProduct >= DotProductThreshold)
                {
                    float Score = (DotProduct + 1.f) / 2.f; // Score from 0 to 1
                    if (Score > MaxScore)
                    {
                        MaxScore = Score;
                        BestEnemy = Actor;
                    }
                }
            }
        }
    }

    // Update ThisActor with the best enemy
    ThisActor = BestEnemy;

    // Update highlighting
    if (LastActor != ThisActor)
    {
        if (LastActor)
        {
            LastActor->UnHighlightActor();
        }
        if (ThisActor)
        {
            ThisActor->HighlightActor();
        }
        LastActor = ThisActor;
    }
}
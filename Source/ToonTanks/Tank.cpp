// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm-> SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);                //TEXT 매크로 값은 프로젝트 세팅-입력에서 설정된 값과 동일해야 함
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::BeginPlay()
{
    Super::BeginPlay();

    TankPlayerController = Cast<APlayerController>(GetController());      //APlayerController 클래스는 AController 클래스의 하위 클래스임 => cast 형변환을 통해 포인터 타입을 변경 cast<바꾸고 싶은 타입> (바꾸려는 인스턴스)
/*
    DrawDebugSphere(
        GetWorld(),                                             //현재 월드 호출
        GetActorLocation() + FVector(0.f, 0.f, 200.f),          //구체의 중심       getactorlocation은 탱크폰의 위치 반환
        100.f,                                                  //구체 반경
        12,                                                     //세그먼트 개수    
        FColor::Red,
        true,                                                   //bPersistentLines
        30.f);                                                  //LifeTime 디폴트는 -1              뒤에 두 매개변수는 생략 가능
*/
}


void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(TankPlayerController) 
    {
        FHitResult HitResult;
        TankPlayerController->GetHitResultUnderCursor(                   //(트레이스채널, bTraceComplex, HitResult(결과를 저장할 hitresult 인스턴스))
            ECollisionChannel::ECC_Visibility,                          //ECC = E Collision Channel
            false, 
            HitResult);
        
        DrawDebugSphere(
            GetWorld(),                                             //현재 월드 호출
            HitResult.ImpactPoint,                                  //구체의 중심이 되는 위치       getactorlocation은 탱크폰의 위치 반환
            10.f,                                                   //구체 반경
            12,                                                     //세그먼트 개수 - 구체의 표면을 근사화하는데 사용되는 세그먼트의 수
            FColor::Red,
            false,                                                   //bPersistentLines - 영구적으로 구체가 생성됨
            -1.f);  
    
        RotateTurret(HitResult.ImpactPoint);
    }
}

void ATank::HandleDestruction()
{
    Super::HandleDestruction();
    //탱크는 파괴하지 않고 숨김 => 틱을 비활성화하여 월드에 존재하고 우리가 소유할 수 있도록 함. 카메라를 통한 뷰를 볼 수는 있지만 탱크를 보거나 움직일 수는 없음
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
}

void ATank::Move(float Value)
{
    FVector DeltaLocation = FVector::ZeroVector;
    DeltaLocation.X = Speed * Value * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalOffset(DeltaLocation,true); //AddActorLocalOffset(방향벡터(필수), 스윕(충돌 검사/디폴트=충돌검사 x), ,);
}

void ATank::Turn(float Value)
{                                                           //FRotator => pitch, yaw, roll 값으로 이루어짐 pitch는 Y축 기준, yaw는 Z축 기준, roll은 X축 기준  
    FRotator DeltaRotation = FRotator::ZeroRotator;
    //Yaw = value * DeltaTime * TurnRate
    DeltaRotation.Yaw =  Value * UGameplayStatics::GetWorldDeltaSeconds(this) * TurnRate;
    AddActorLocalRotation(DeltaRotation, true);
}
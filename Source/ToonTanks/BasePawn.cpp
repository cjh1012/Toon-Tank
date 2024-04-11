// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));		//capsulecomp라는 하위 오브젝트 생성. CreateDefaultSubobject<컴포넌트타입>(하위 오브젝트의 이름)
	RootComponent = CapsuleComp;															//루트컴포넌트로 capsulecomp 지정

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);													//CapsuleComp에 부착

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint -> SetupAttachment(TurretMesh);
}

void ABasePawn::RotateTurret(FVector LookAtTarget)				//포탑부분을 회전시키는 함수
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();				//포탑을 회전시키는 각도 = (바라보는 위치- 포탑의 위치)를 회전 값으로 변형시킨 값(.Rotation())
	FRotator LookAtRotation = FRotator(0.f,ToTarget.Rotation().Yaw, 0.f);				//포탑이 위아래로 회전하지 않도록 == z축(Yaw)만 회전하도록 만듦

	TurretMesh->SetWorldRotation(														//AddActorLocalOffset이 아니라 setWorldRotation 사용하는 이유 : 월드 스페이스를 기준으로 회전값을 정하기 때문 
															//TurretMesh의 위치 = 월드스페이스 위치값 LookAtTarget = 월드스페이스 위치값 따라서 LookAtRotation도 월드 스페이스 회전값
		FMath::RInterpTo(									//포탑이 서서히 회전하도록 도와주는 함수. 없으면 마우스 커서가 갑자기 변할때 포탑도 급격하게 회전되어 어색하기 때문
			TurretMesh->GetComponentRotation(), 			//현재 포탑의 방향
			LookAtRotation, 								//변경하고자 하는 포탑의 방향
			UGameplayStatics::GetWorldDeltaSeconds(this), 	//DeltaTime
			2.f												//변경에 소요되는 시간. 클수록 빠르게 보간됨
		)
	);										 	
	
}

void ABasePawn::HandleDestruction()
{
	// ToDo: Visual/sound effects
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePawn::Fire()			
{
	//DrawDebugSphere(GetWorld(), ProjectileSpawnPoint->GetComponentLocation(), 10.f, 12, FColor::Red, false, 3.f);
	
	auto Projectile = GetWorld()->SpawnActor<AProjectile>	(
		ProjectileClass, 
		ProjectileSpawnPoint->GetComponentLocation(), 
		ProjectileSpawnPoint->GetComponentRotation()
	);

	//발사체를 생성한 폰을 소유자로 지정함
	Projectile->SetOwner(this);
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->MaxSpeed = 1300.f;
	ProjectileMovementComponent->InitialSpeed = 1300.f;

	SmokeTrailParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));
	SmokeTrailParticle->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	//OnHit 함수를 delegate에 바인딩. OnComponentHit.AddDynamic(사용자객체, 콜백함수)
	ProjectileMesh -> OnComponentHit.AddDynamic(this, &AProjectile::OnHit); 						//생성자에서 콜백함수를 delegate에 바인딩하게 되면 시기가 너무 이르기에 바인딩 되지 않는 문제가 발생할 수 있음. =>BeginPlay함수에서 실행
	if(LaunchSound) UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation(), GetActorRotation());		//발사 소리 = 생성될 때 소리 재생 
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
	//Instigator의 컨트롤러에 접근
	AActor* MyOwner = GetOwner();

	if(MyOwner == nullptr) 
	{
		Destroy();
		return;
	}
	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();
	//UDamageType 클래스를 나타내는 UClass값이 필요할때 StaticClass 함수를 사용. StaticClass는 UClass 타입을 반환
	UClass* DamageTypeClass = UDamageType::StaticClass();

	if(OtherActor && OtherActor != this && OtherActor != MyOwner) 	//OtherActor가 Null이 아닌지, 자신이 아닌지, 소유자가 아닌지 확인
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);				//데미지 적용
		if (HitParticles)
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());	//파티클(피격 시 효과) 호출
		
		if(HitCameraShakeClass)																						//카메라 흔들림 효과
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);

		if (HitSound)
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation(), GetActorRotation());			//피격 시 음성효과 호출
	}
	Destroy();
}


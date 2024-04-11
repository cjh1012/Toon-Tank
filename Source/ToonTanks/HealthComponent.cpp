// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksGameMode.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	//delegate는 HealthComponent가 아니라 액터에 존재하는 상태, HealthComponent를 가진 폰에서 OnTakeAnyDamage 델리게이트에 연결해야 함
	GetOwner()-> OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);				// 컴포넌트를 소유한 액터를 반환함, AActor*의 형태로 호출 후 델리게이트에 연결하여 콜백함수를 바인드함
	ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this)); 									//GetGameMode는 GameModeBase를 반환함

}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser)
{
	if(Damage <= 0.f) return;

	Health -= Damage;
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);

	if(Health <= 0 && ToonTanksGameMode)	ToonTanksGameMode->ActorDied(DamagedActor);

}

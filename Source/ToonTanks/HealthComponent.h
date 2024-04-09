// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.f;
	float Health = 0.f;

	// 데미지 콜백함수
	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser);
	//DamageType => 화재로 인한 데미지, 독으로 인한 데미지, 폭발로 인한 데미지 등 각 데미지 타입에 따라 다른 기능을 구현하고 싶을때 사용, TSubclassOf<class DamageType> 형태
	//instigator => 데미지를 관리하는 컨트롤러, 폰을 조종하는 플레이어 때문에 데미지가 발생했다면 Instigator는 폰을 조종하는 컨트롤러가 됨, 없을땐 null e.g. 총을 쏜 컨트롤러가 instigator가 됨
	//DamageCauser => 데미지를 발생시킨 액터, 총, 수류탄 등등

};

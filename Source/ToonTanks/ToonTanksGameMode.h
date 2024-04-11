// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
	

public:

	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override; 

private:
	class ATank* Tank;															//죽은 액터가 탱크인지 확인하기 위해 탱크를 담을 변수 선언
	class AToonTanksPlayerController* ToonTanksPlayerController; 				//PlayerController에 접근할 포인터변수
};

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

	UFUNCTION(BlueprintImplementableEvent)										//블루프린트 구현가능 이벤트 : C++에서 함수바디를 작성할 필요가 없음
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

private:
	class ATank* Tank;															//죽은 액터가 탱크인지 확인하기 위해 탱크를 담을 변수 선언
	class AToonTanksPlayerController* ToonTanksPlayerController; 				//PlayerController에 접근할 포인터변수

	float StartDelay = 3.f;

	void HandleGameStart();

	int32 TargetTowers = 0;
	int32 GetTargetTowerCount();

};

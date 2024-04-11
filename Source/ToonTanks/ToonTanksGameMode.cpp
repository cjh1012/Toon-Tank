// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
    if(DeadActor == Tank){
        Tank->HandleDestruction();
        
        /*if(Tank -> GetTankPlayerController())  { 
            Tank -> DisableInput(Tank -> GetTankPlayerController());               //탱크의 입력을 중지
            Tank -> GetTankPlayerController() -> bShowMouseCursor = false;  //마우스커서가 보이지 않게 함 
            }*/

        if(ToonTanksPlayerController)   ToonTanksPlayerController->SetPlayerEnabledState(false);   
        
    }
    else if(ATower* DestroyedTower = Cast<ATower>(DeadActor))
    {
        DestroyedTower -> HandleDestruction();
    }
}

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));            //GetPlayerPawn(WorldContextObject, PlayerIndex) => APawn 포인터를 반환, 캐스팅이 필요함
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));   //현재 폰을 조종하는 컨트롤러에 접근
}
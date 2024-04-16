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
        GameOver(false);
    }
    else if(ATower* DestroyedTower = Cast<ATower>(DeadActor))
    {
        DestroyedTower -> HandleDestruction();
        TargetTowers--;
        if (!TargetTowers) GameOver(true);
    }
}

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    HandleGameStart();

}

void AToonTanksGameMode::HandleGameStart()                                   //게임이 시작될 때 다루어야하는 설정에 관련된 함수
{    
    TargetTowers = GetTargetTowerCount();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));            //GetPlayerPawn(WorldContextObject, PlayerIndex) => APawn 포인터를 반환, 캐스팅이 필요함
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));   //현재 폰을 조종하는 컨트롤러에 접근

    StartGame();

    if(ToonTanksPlayerController)    
    {
        ToonTanksPlayerController->SetPlayerEnabledState(false);                //시작한 직후에는 움직이지 못함

        FTimerHandle PlayerEnableTimerHandle;                                   //타이머 구현

        //CreateUObject(UserObject(콜백함수가 존재하는 클래스),&CallBackFunction, Inputs(콜백함수에 전달하고 싶은 입력값) ) 함수를 통해서 FTimerDelegate를 초기화 
        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController,&AToonTanksPlayerController::SetPlayerEnabledState, true);
        GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);   //SetTimer(TimerHandle, TimerDelegate, float PlayRate(지연시간), Looping)
    }
}

int32 AToonTanksGameMode::GetTargetTowerCount()
{
    //UGameplayStatics::GetAllActorsOfClass(UObject WorldContextObject, TSubclassOf<AActor> ActorClass, TArray<AActor*> &OutActors);
    //월드에 있는 특정 클래스의 액터를 전부 찾음 ()

    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATower::StaticClass(), Towers);
    return Towers.Num();

}

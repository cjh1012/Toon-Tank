// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


void ATower::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));       //탱크의 위치를 찾기 위해 탱크 컴포넌트 변수 선언 후 할당

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);  //(타이머핸들, userclass, 콜백함수의 주소, 속도(주기), 반복여부(false 시 1회만 반복되고 종료))
}

void ATower::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
    if(InFireRange()) {
        RotateTurret(Tank->GetActorLocation());
    }
}

void ATower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}

void ATower::CheckFireCondition()
{
    if (Tank == nullptr) 
    {
        return;
    }
    if(InFireRange() && Tank->bAlive == true) 
    {
        Fire();
    }
}

bool ATower::InFireRange()
{
    if(Tank){
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());       //탱크와 타워 사이 거리
        if(Distance <= FireRange)
        {
            return true;
        }
    }
    return false;
}
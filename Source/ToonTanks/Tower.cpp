// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"


void ATower::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));       //탱크의 위치를 찾기 위해 탱크 컴포넌트 변수 선언 후 할당


}

void ATower::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
    if(Tank){
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());       //탱크와 타워 사이 거리
        if(Distance <= FireRange)
        {
            RotateTurret(Tank->GetActorLocation());
        }
    }
}
   
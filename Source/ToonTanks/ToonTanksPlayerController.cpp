// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"
#include "GameFramework/Pawn.h"

void AToonTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)         //액터가 죽으면 게임모드에서 호출하도록 함, true를 넘겨주면 플레이어가 활성화, false를 넘겨주면 비활성화
{
    if (bPlayerEnabled)
    {   
        //플레이어가 소유한 폰에 접근, 폰 클래스에 존재하는 Disable/EnableInput(APlayerController* ) 함수를 통해 입력을 활성화/비활성화함
        GetPawn()->EnableInput(this);
    }
    else
    {
        GetPawn()->DisableInput(this);
    }
    bShowMouseCursor = bPlayerEnabled;
}
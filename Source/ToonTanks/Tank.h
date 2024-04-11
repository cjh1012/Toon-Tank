// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"


/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
	
public:
	ATank();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;		//입력을 처리하는 함수	

	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	//public Getter => 일반적으로 변수 앞에 이름에는 get을 붙이며 const도 사용함, 아무것도 바뀌게 하지 않고 반환만 하기 때문
	APlayerController* GetTankPlayerController() const { return TankPlayerController; }

protected:
	//Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed= 20;

	UPROPERTY(EditAnywhere, Category = "RotationRate")
	float TurnRate = 30;

	void Move(float Value);
	void Turn(float Value);

	APlayerController* TankPlayerController;			//변수 이름을 잘못 지었을 때는 해당 변수 드래그해서 선택 후 F2를 눌러 변경
};

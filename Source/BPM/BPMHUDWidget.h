// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "BPMHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class BPM_API UBPMHUDWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* CurAmmo;
	
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* MaxAmmo;
	
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* CurHP;
	
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* MaxHP;
	
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Coin;
	
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* ItemCost;
	
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* ItemInfo;
	
public:
	UFUNCTION()
	void SetCurAmmo(FString str) { CurAmmo->SetText(FText::FromString(str)); };
	
	UFUNCTION()
	void SetMaxAmmo(FString str) { MaxAmmo->SetText(FText::FromString(str)); };
	
	UFUNCTION()
	void SetCurHP(FString str) { CurHP->SetText(FText::FromString(str)); };
	
	UFUNCTION()
	void SetMaxHP(FString str) { MaxHP->SetText(FText::FromString(str)); };
	
	UFUNCTION()
	void SetCoin(FString str) { Coin->SetText(FText::FromString(str)); };
	
	UFUNCTION()	
	void SetItemCost(FString str) { ItemCost->SetText(FText::FromString(str)); };
	
	UFUNCTION()
	void SetItemInfo(FString str) { ItemInfo->SetText(FText::FromString(str)); };
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HitAlpha;

public:
	UFUNCTION(BlueprintCallable)
	void OnPlayerHit();

	
};
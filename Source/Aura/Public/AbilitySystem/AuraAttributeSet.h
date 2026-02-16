// AuraAttributeSet.h

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AuraAttributeSet.generated.h"


UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAuraAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")	// 복제 필요
	FGameplayAttributeData Health;	// 체력 정보
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")	// 복제 필요
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")	// 복제 필요
	FGameplayAttributeData Mana;	// 체력 정보
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attributes")	// 복제 필요
	FGameplayAttributeData MaxMana;
	
	UFUNCTION()
	void  OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	
	UFUNCTION()
	void  OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	UFUNCTION()
	void  OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	
	UFUNCTION()
	void  OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
};

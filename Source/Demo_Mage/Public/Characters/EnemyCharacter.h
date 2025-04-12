#pragma once

#include "CoreMinimal.h"
#include "DemoCharacter.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class DEMO_MAGE_API AEnemyCharacter : public ADemoCharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

	virtual void RespawnCharacter() override;
	
protected:
	virtual void BeginPlay() override;

	virtual void HealthDepleteHandler() override;

	UFUNCTION(BlueprintImplementableEvent, Category="Enemy Character")
	void OnRespawn();

	UFUNCTION(BlueprintImplementableEvent, Category="Enemy Character")
	void OnDeath();

	AController* AIController;

private:
	FVector MeshAttachmentLocation;
	FRotator MeshAttachmentRotation;
};

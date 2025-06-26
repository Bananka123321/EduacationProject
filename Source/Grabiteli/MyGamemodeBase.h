
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGamemodeBase.generated.h"

UCLASS()
class GRABITELI_API AMyGamemodeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	AMyGamemodeBase();
};

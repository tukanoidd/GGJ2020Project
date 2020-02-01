// Property of OTNH 2020

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"

#include "Blueprint/UserWidget.h"

#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GGJ2020PROJECT_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	/** Reference to UMG asset in the editor */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
		TSubclassOf<UUserWidget> HUDOverlayAsset;

	/** Variable to hold the widget after creating it */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
		UUserWidget* HUDOverlay;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "KoalaGPTDefinitions.h"
#include "HttpModule.h"
#include "KoalaGPTCallCompletions.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnGptResponseRecievedPin, const TArray<FCompletion>&, completions, const FString&, errorMessage, const FCompletionInfo&, completionInfo, bool, Success);

/**
 * 
 */
UCLASS()
class KOALAGPTAPI_API UKoalaGPTCallCompletions : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UKoalaGPTCallCompletions();
	~UKoalaGPTCallCompletions();
	
	FString prompt = "";
	FCompletionSettings settings;

	UPROPERTY(BlueprintAssignable, Category = "KoalaGPT")
	FOnGptResponseRecievedPin Finished;

private:
	KoalaGPTValueMapping mapping;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "KoalaGPT")
	static UKoalaGPTCallCompletions* KoalaGPTCallCompletions(FString prompt, FCompletionSettings settings);

	virtual void Activate() override;
	void OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool WasSuccessful);
};

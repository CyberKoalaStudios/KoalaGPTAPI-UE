// Copyright CyberKoala LLC 2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "KoalaGPTDefinitions.h"
#include "HttpModule.h"
#include "KoalaGPTCallChat.generated.h"

// DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnResponseRecievedPin, const FChatCompletion, message, const FString&, errorMessage, bool, Success);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnResponseRecievedPin, const FChatCompletionSimple, message, const FString&, errorMessage, bool, Success);
/**
 * 
 */
UCLASS()
class KOALAGPTAPI_API UKoalaGPTCallChat : public UBlueprintAsyncActionBase
{
public:
	GENERATED_BODY()

public:
	UKoalaGPTCallChat();
	~UKoalaGPTCallChat();

	FChatSettings chatSettings;

	UPROPERTY(BlueprintAssignable, Category = "KoalaGPT")
	FOnResponseRecievedPin Finished;

private:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "KoalaGPT")
	static UKoalaGPTCallChat* KoalaGPTCallChat(FChatSettings chatSettings);

	virtual void Activate() override;
	void OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool WasSuccessful);
	void OnResponseSimple(FHttpRequestPtr Request, FHttpResponsePtr Response, bool WasSuccessful);
};

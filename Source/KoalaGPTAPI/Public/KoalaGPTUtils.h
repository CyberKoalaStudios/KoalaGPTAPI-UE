// Copyright CyberKoala LLC 2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "KoalaGPTDefinitions.h"

#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

#if PLATFORM_WINDOWS
#include "Runtime/Core/Public/Windows/WindowsPlatformMisc.h"
#endif

#if PLATFORM_MAC
#include "Runtime/Core/Public/Apple/ApplePlatformMisc.h"
#endif

#if PLATFORM_LINUX
#include "Runtime/Core/Public/Linux/LinuxPlatformMisc.h"
#endif


#include "KoalaGPTUtils.generated.h"


/**
 * 
 */
UCLASS()
class KOALAGPTAPI_API UKoalaGPTUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "KoalaGPT")
	static void setKoalaGPTApiKey(FString apiKey);
	
	static FString getApiKey();

	UFUNCTION(BlueprintCallable, Category = "KoalaGPT")
	static void setUseKoalaGPTApiKeyFromEnvironmentVars(bool bUseEnvVariable);

	static bool getUseApiKeyFromEnvironmentVars();

	static FString GetEnvironmentVariable(FString key);

	static FString RemoveSpecialCharacters(const FString& Payload);
};

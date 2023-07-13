// Copyright CyberKoala LLC 2023. All Rights Reserved.


#include "KoalaGPTUtils.h"
#include "KoalaGPTDefinitions.h"
#include "KoalaGPTAPI.h"
#include "Modules/ModuleManager.h"

void UKoalaGPTUtils::setKoalaGPTApiKey(FString apiKey)
{
	FKoalaGPTAPIModule& mod = FModuleManager::Get().LoadModuleChecked<FKoalaGPTAPIModule>("KoalaGPTAPI");
	mod._apiKey = apiKey;
}

FString UKoalaGPTUtils::getApiKey()
{
	FKoalaGPTAPIModule& mod = FModuleManager::Get().LoadModuleChecked<FKoalaGPTAPIModule>("KoalaGPTAPI");
	return mod._apiKey;
}

void UKoalaGPTUtils::setUseKoalaGPTApiKeyFromEnvironmentVars(bool bUseEnvVariable)
{
	FKoalaGPTAPIModule& mod = FModuleManager::Get().LoadModuleChecked<FKoalaGPTAPIModule>("KoalaGPTAPI");
	mod._useApiKeyFromEnvVariable = bUseEnvVariable;
}

bool UKoalaGPTUtils::getUseApiKeyFromEnvironmentVars()
{

	FKoalaGPTAPIModule& mod = FModuleManager::Get().LoadModuleChecked<FKoalaGPTAPIModule>("KoalaGPTAPI");
	return mod._useApiKeyFromEnvVariable;
}

FString UKoalaGPTUtils::GetEnvironmentVariable(FString key)
{
	FString result;
#if PLATFORM_WINDOWS
	result = FWindowsPlatformMisc::GetEnvironmentVariable(*key);
#endif
#if PLATFORM_MAC
	result = FApplePlatformMisc::GetEnvironmentVariable(*key); 
#endif

#if PLATFORM_LINUX
	result = FLinuxPlatformMisc::GetEnvironmentVariable(*key);
#endif
	return result;
}

FString UKoalaGPTUtils::RemoveSpecialCharacters(const FString& Payload)
{
	FString CleanPayload = Payload;
    
	// Remove "\r" symbol
	CleanPayload.ReplaceInline(TEXT("\r"), TEXT(""));

	// Remove "\n" symbol
	CleanPayload.ReplaceInline(TEXT("\n"), TEXT(""));

	// Remove "\t" symbol
	CleanPayload.ReplaceInline(TEXT("\t"), TEXT(""));

	return CleanPayload;
}
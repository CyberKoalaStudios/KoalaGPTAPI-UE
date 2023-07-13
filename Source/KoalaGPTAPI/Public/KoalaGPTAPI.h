// Copyright CyberKoala LLC 2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FKoalaGPTAPIModule : public IModuleInterface
{
	friend class UKoalaGPTAPIUtils;
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

public:
	FString _apiKey = "";
	bool _useApiKeyFromEnvVariable = false;
};

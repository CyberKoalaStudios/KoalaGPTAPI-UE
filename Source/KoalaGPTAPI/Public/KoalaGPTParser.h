// Copyright CyberKoala LLC 2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Misc/DateTime.h"
#include "KoalaGPTDefinitions.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

/**
 * 
 */
class KOALAGPTAPI_API KoalaGPTParser
{
public:
	KoalaGPTParser();
	KoalaGPTParser(const FCompletionSettings&);
	KoalaGPTParser(const FChatSettings&);
	~KoalaGPTParser();

	FCompletionSettings completionSettings;
	
	FChatSettings chatSettings;

	FCompletion ParseCompletionsResponse(const FJsonObject&);
	FCompletionInfo ParseGPTCompletionInfo(const FJsonObject&);
	FChatCompletion ParseChatCompletion(const FJsonObject&);
	FChatCompletionSimple ParseChatCompletionSimple(const FJsonObject&);
	// FChatCompletionSimple ParseChatCompletionSimple(const FJsonObject&);
	// FString ParseTranscriptionCompletion(const FJsonObject&);
	// FString ParseGeneratedImage(FJsonObject&);
};

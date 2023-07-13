// Copyright CyberKoala LLC 2023. All Rights Reserved.


#include "KoalaGPTParser.h"

#include "JsonObjectConverter.h"
#include "KoalaGPTUtils.h"
#include "Dom/JsonObject.h"



// Constructor
KoalaGPTParser::KoalaGPTParser(const FCompletionSettings& settings)
	: completionSettings(settings)
{
}

KoalaGPTParser::KoalaGPTParser(const FChatSettings& settings)
	: chatSettings(settings)
{
}

//De-constructor
KoalaGPTParser::~KoalaGPTParser()
{
}

// parses a single Completion.
FCompletion KoalaGPTParser::ParseCompletionsResponse(const FJsonObject& json)
{
	FCompletion res = {};
	
	res.text = json.GetStringField(TEXT("text")) + completionSettings.injectRestartText;
	res.index = json.GetIntegerField(TEXT("index"));
	json.TryGetStringField(TEXT("finish_reason"), res.finishReason);
	
	return res;
}

// parses the response info
FCompletionInfo KoalaGPTParser::ParseGPTCompletionInfo(const FJsonObject& json)
{
	FCompletionInfo res = {};

	res.id = json.GetStringField("id");
	res.object = json.GetStringField("object");
	res.created = FDateTime::FromUnixTimestamp(json.GetNumberField("created"));
	res.model = json.GetStringField("model");

	return res;
}

// parses a single Generated messasge.
FChatCompletion KoalaGPTParser::ParseChatCompletion(const FJsonObject& json)
{
	FChatCompletion res = {};

	FChatLog message;
	message.role = EOAChatRole::ASSISTANT;
	TArray<TSharedPtr<FJsonValue>> choices = json.GetArrayField("choices");
	TSharedPtr<FJsonValue> choice = choices[0];
	TSharedPtr<FJsonObject> messageObject = choice->AsObject()->GetObjectField("message");
	message.content = messageObject->GetStringField("content");

	json.TryGetStringField(TEXT("finish_reason"), res.finishReason);
	res.message = message;
	
	return res;
}

// parses a single Generated messasge simple Text.
FChatCompletionSimple KoalaGPTParser::ParseChatCompletionSimple(const FJsonObject& json)
{
	FChatCompletionSimple res = {};
	FChatLogSimple message;

	message.content = json.GetStringField("message");

	res.message.content = message.content;
	return res;
}

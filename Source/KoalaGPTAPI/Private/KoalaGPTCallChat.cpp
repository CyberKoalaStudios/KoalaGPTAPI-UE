// Copyright CyberKoala LLC 2023. All Rights Reserved.

#include "KoalaGPTCallChat.h"
#include "KoalaGPTUtils.h"
#include "Http.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "KoalaGPTParser.h"

UKoalaGPTCallChat::UKoalaGPTCallChat()
{
}

UKoalaGPTCallChat::~UKoalaGPTCallChat()
{
}

UKoalaGPTCallChat* UKoalaGPTCallChat::KoalaGPTCallChat(FChatSettings chatSettingsInput)
{
	UKoalaGPTCallChat* BPNode = NewObject<UKoalaGPTCallChat>();
	BPNode->chatSettings = chatSettingsInput;
	return BPNode;
}


void UKoalaGPTCallChat::Activate()
{
	FString _apiKey;
	if (UKoalaGPTUtils::getUseApiKeyFromEnvironmentVars())
		_apiKey = UKoalaGPTUtils::GetEnvironmentVariable(TEXT("KOALAGPT_API_KEY"));
	else
		_apiKey = UKoalaGPTUtils::getApiKey();
	
	// checking parameters are valid
	if (_apiKey.IsEmpty())
	{
		Finished.Broadcast({}, TEXT("Api key is not set"), false);
	}	else
	{
	
		auto HttpRequest = FHttpModule::Get().CreateRequest();

		FString apiMethod;
		switch (chatSettings.model)
		{
		case EOAChatEngineType::GPT_3_5_TURBO:
			apiMethod = "gpt-3.5-turbo";
			break;
		case EOAChatEngineType::GPT_4:
			apiMethod = "gpt4";
			break;
		}

		// convert parameters to strings
		FString tempHeader = "Bearer ";
		tempHeader += _apiKey;

		// set headers
		FString url = FString::Printf(TEXT("https://gpt.cyberkoala.ru/backend-api/v2/unreal"));
		HttpRequest->SetURL(url);
		HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
		HttpRequest->SetHeader(TEXT("Authorization"), tempHeader);

		//build payload
		TSharedPtr<FJsonObject> _payloadObject = MakeShareable(new FJsonObject());
		_payloadObject->SetStringField(TEXT("model"), apiMethod);
		// _payloadObject->SetNumberField(TEXT("max_tokens"), chatSettings.maxTokens);

		
		// convert role enum to model string
		if (!(chatSettings.messages.Num() == 0))
		{
			TArray<TSharedPtr<FJsonValue>> Messages;
			FString role;
			for (int i = 0; i < chatSettings.messages.Num(); i++)
			{
				TSharedPtr<FJsonObject> Message = MakeShareable(new FJsonObject());
				switch (chatSettings.messages[i].role)
				{
				case EOAChatRole::USER:
					role = "user";
					break;
				case EOAChatRole::ASSISTANT:
					role = "assistant";
					break;
				case EOAChatRole::SYSTEM:
					role = "system";
					break;
				}
				Message->SetStringField(TEXT("role"), role);
				Message->SetStringField(TEXT("content"), chatSettings.messages[i].content);
				Messages.Add(MakeShareable(new FJsonValueObject(Message)));
			}
			TArray<TSharedPtr<FJsonValue>> Conversation;
			_payloadObject->SetStringField(TEXT("jailbreak"), "default");
			
			TArray<TSharedPtr<FJsonValue>> Metas;
			TSharedPtr<FJsonObject> Meta = MakeShareable(new FJsonObject());
			TSharedPtr<FJsonObject> Content = MakeShareable(new FJsonObject());
			
			Content->SetArrayField(TEXT("parts"), Messages);
			Content->SetBoolField(TEXT("internet_access"), false);
			Content->SetArrayField(TEXT("conversation"), Conversation);
			Content->SetStringField(TEXT("content_type"), "text");
			
			Meta->SetObjectField(TEXT("content"), Content);
			
			Metas.Add(MakeShareable(new FJsonValueObject(Meta)));
			
			_payloadObject->SetArrayField(TEXT("meta"), Metas);
			
		}

		// convert payload to string
		FString _payload;
		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&_payload);
		FJsonSerializer::Serialize(_payloadObject.ToSharedRef(), Writer);

		// commit request
		HttpRequest->SetVerb(TEXT("POST"));
		HttpRequest->SetContentAsString(_payload);

		if (HttpRequest->ProcessRequest())
		{
			HttpRequest->OnProcessRequestComplete().BindUObject(this, &UKoalaGPTCallChat::OnResponseSimple);
		}
		else
		{
			Finished.Broadcast({}, ("Error sending request"), false);
		}
	}
}

void UKoalaGPTCallChat::OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool WasSuccessful)
{
	// print response as debug message
	if (!WasSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("Error processing request. \n%s \n%s"), *Response->GetContentAsString(), *Response->GetURL());
		if (Finished.IsBound())
		{
			Finished.Broadcast({}, *Response->GetContentAsString(), false);
		}

		return;
	}

	TSharedPtr<FJsonObject> ResponseObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	if (FJsonSerializer::Deserialize(Reader, ResponseObject))
	{
		bool err = ResponseObject->HasField("error");

		if (err)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Response->GetContentAsString());
			Finished.Broadcast({}, TEXT("Api error"), false);
			return;
		}

		KoalaGPTParser parser(chatSettings);
		FChatCompletion _out = parser.ParseChatCompletion(*ResponseObject);

		// Finished.Broadcast(_out, "", true);
	}
}

void UKoalaGPTCallChat::OnResponseSimple(FHttpRequestPtr Request, FHttpResponsePtr Response, bool WasSuccessful)
{
	// print response as debug message
	if (!WasSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("Error processing request. \n%s \n%s"), *Response->GetContentAsString(), *Response->GetURL());
		if (Finished.IsBound())
		{
			Finished.Broadcast({}, *Response->GetContentAsString(), false);
		}

		return;
	}

	TSharedPtr<FJsonObject> ResponseObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	if (FJsonSerializer::Deserialize(Reader, ResponseObject))
	{
		bool err = ResponseObject->HasField("error");

		if (err)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Response->GetContentAsString());
			Finished.Broadcast({}, TEXT("Api error"), false);
			return;
		}

		KoalaGPTParser parser(chatSettings);
		FChatCompletionSimple _out = parser.ParseChatCompletionSimple(*ResponseObject);

		Finished.Broadcast(_out, "", true);
	}
}


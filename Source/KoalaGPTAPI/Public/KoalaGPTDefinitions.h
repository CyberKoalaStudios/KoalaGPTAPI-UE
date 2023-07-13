// Copyright CyberKoala LLC 2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Misc/DateTime.h"
#include "KoalaGPTDefinitions.generated.h"


UENUM(BlueprintType)
enum class EOAChatEngineType : uint8
{
	GPT_3_5_TURBO = 0 UMETA(ToolTip = "More capable than any GPT-3.5 model, able to do more complex tasks, and optimized for chat."),
	GPT_4 = 1 UMETA(ToolTip = "More capable than any GPT-3.5 model, able to do more complex tasks, and optimized for chat. "),
};

UENUM(BlueprintType)
enum class EOAChatRole : uint8
{
	SYSTEM = 0 UMETA(ToolTip = "More capable than any GPT-3.5 model, able to do more complex tasks, and optimized for chat."),
	USER= 1 UMETA(ToolTip = "More capable than any GPT-3.5 model, able to do more complex tasks, and optimized for chat."),
	ASSISTANT = 2 UMETA(ToolTip = "Same capabilities as the base gpt-4 model but with 4x the context length."),
};

// Structs for GPT

USTRUCT(BlueprintType)
struct FChatLog
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KoalaGPT")
	EOAChatRole role = EOAChatRole::SYSTEM;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KoalaGPT")
	FString content = "";
};

USTRUCT(BlueprintType)
struct FChatLogSimple
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KoalaGPT")
	FString content = "";
};

USTRUCT(BlueprintType)
struct FCompletionInfo
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KoalaGPT")
			FString id = "Null";

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KoalaGPT")
			FString object = "Null";

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KoalaGPT")
			FDateTime created;

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KoalaGPT")
			FString model = "Null";

};

USTRUCT(BlueprintType)
struct FCompletion
{
	GENERATED_USTRUCT_BODY()

	// KoalaGPT's response.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KoalaGPT")
		FString text = "";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KoalaGPT")
		int32 index = 0;
	

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KoalaGPT")
		FString finishReason = "";
};

USTRUCT(BlueprintType)
struct FChatCompletion
{
	GENERATED_USTRUCT_BODY()

	// KoalaGPT's response.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KoalaGPT")
	FChatLog message;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KoalaGPT")
	FString finishReason = "";
};

USTRUCT(BlueprintType)
struct FChatCompletionSimple
{
	GENERATED_USTRUCT_BODY()

	// KoalaGPT's response.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KoalaGPT")
	FChatLogSimple message;

};


class KoalaGPTValueMapping
{
public:
	KoalaGPTValueMapping();
};

USTRUCT(BlueprintType)
struct FCompletionSettings
{
	GENERATED_BODY()

	/** A sequence that is appended to the start of your prompt */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KoalaGPT")
		FString startSequence = "";

	/** A sequence that is appended at the beginning of your prompt */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KoalaGPT")
		FString injectStartText = "";

	/** A sequence that is appended to the start of your prompt */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KoalaGPT")
		FString injectRestartText = "";

	/** Up to four sequences where the API will stop generating further tokens. The returned text will not contain the stop sequence. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KoalaGPT")
		TArray<FString> stopSequences;

	/** The maximum number of tokens to generate. Requests can use up to 2048 tokens shared between prompt and completion. (One token is roughly 4 characters for normal English text) */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KoalaGPT")
		int32 maxTokens = 250;

	/** What sampling temperature to use. Higher values means the model will take more risks. Try 0.9 for more creative applications, and 0 (argmax sampling) for ones with a well-defined answer. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KoalaGPT")
		float temperature = 0.7f;

	/** An alternative to sampling with temperature, called nucleus sampling, where the model considers the results of the tokens with top_p probability mass. So 0.1 means only the tokens comprising the top 10% probability mass are considered.  */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KoalaGPT")
		float topP = 1.0f;

	/** If logProbs is greater than 0, the model returns tokens, token_logprobs, and the text_offsets for a given completion. (support for top_logprobs will be added soon)*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KoalaGPT")
		int32 logprobs = 0;

	/** How many completions to generate for each prompt. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KoalaGPT")
		int32 numCompletions = 1;

	/** Number between 0 and 1 that penalizes new tokens based on their existing frequency in the text so far. Decreases the model's likelihood to repeat the same line verbatim. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KoalaGPT")
		float frequencyPenalty = 0.0f;

	/** Number between 0 and 1 that penalizes new tokens based on whether they appear in the text so far. Increases the model's likelihood to talk about new topics. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KoalaGPT")
		float presencePenalty = 0.0f;

	/** Generates best_of completions server-side and returns the "best" (the one with the lowest log probability per token). */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KoalaGPT")
		int32 bestOf = 1;

};

USTRUCT(BlueprintType)
struct FChatSettings
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KoalaGPT")
	EOAChatEngineType model = EOAChatEngineType::GPT_4;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KoalaGPT")
	TArray<FChatLog> messages;

	// UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KoalaGPT")
	// float temperature = 0.7f;
	//
	// UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KoalaGPT")
	// int32 maxTokens = 250;
};
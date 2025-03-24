#pragma once

#include "CoreMinimal.h"

#define PRINT(LineNumber, Message, Color, ...) GEngine->AddOnScreenDebugMessage(LineNumber, 10, FColor::Color, FString::Printf(TEXT(Message), ##__VA_ARGS__))






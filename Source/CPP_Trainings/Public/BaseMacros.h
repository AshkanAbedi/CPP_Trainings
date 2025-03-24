#pragma once

#include "CoreMinimal.h"

#define PRINT(LineNumber, Message, Color, ...) GEngine->AddOnScreenDebugMessage(LineNumber, 3, FColor::Color, FString::Printf(TEXT(Message), ##__VA_ARGS__))






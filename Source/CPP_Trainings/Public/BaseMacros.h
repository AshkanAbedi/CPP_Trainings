#pragma once

#include "CoreMinimal.h"

#define PRINT(Message, Color, ...) GEngine->AddOnScreenDebugMessage(1, 3, FColor::Color, FString::Printf(TEXT(Message), ##__VA_ARGS__))






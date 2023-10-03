// Copyright Epic Games, Inc. All Rights Reserved.


#include "InputProjectGameModeBase.h"
#include "Player/MainCharacter.h"

AInputProjectGameModeBase::AInputProjectGameModeBase()
{
	DefaultPawnClass = AMainCharacter::StaticClass();
}

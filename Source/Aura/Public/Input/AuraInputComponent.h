﻿// Copyright XiaoYao.

#pragma once

#include "CoreMinimal.h"
#include "AuraInputConfig.h"
#include "EnhancedInputComponent.h"
#include "AuraInputComponent.generated.h"


struct FAuraInputAction;
class UAuraInputConfig;

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class AURA_API UAuraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	UAuraInputComponent();

	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const UAuraInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);
	
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UAuraInputComponent::BindAbilityActions(const UAuraInputConfig* InputConfig, UserClass* Object,
	PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputConfig);

	for(const FAuraInputAction& AuraInputAction : InputConfig->AbilityInputActions)
	{
		if(AuraInputAction.InputAction && AuraInputAction.InputTag.IsValid())
		{
			if(PressedFunc)
			{
				BindAction(AuraInputAction.InputAction, ETriggerEvent::Started, Object, PressedFunc, AuraInputAction.InputTag);
			}
			if(ReleasedFunc)
			{
				BindAction(AuraInputAction.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, AuraInputAction.InputTag);
			}
			if(HeldFunc)
			{
				BindAction(AuraInputAction.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, AuraInputAction.InputTag);
			}
		}
	}
}

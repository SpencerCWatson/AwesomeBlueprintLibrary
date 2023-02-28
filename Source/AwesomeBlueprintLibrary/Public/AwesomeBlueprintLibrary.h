// Copyright 2022 Just2Devs. All Rights Reserved.

#pragma once
#include "Modules/ModuleManager.h"

class FAwesomeBlueprintLibraryModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

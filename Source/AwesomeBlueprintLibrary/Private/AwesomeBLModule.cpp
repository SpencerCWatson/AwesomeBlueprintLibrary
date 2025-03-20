// Copyright 2022 Just2Devs. All Rights Reserved.

#include "..\Public\AwesomeBLModule.h"

#define LOCTEXT_NAMESPACE "FAwesomeBlueprintLibraryModule"

void FAwesomeBlueprintLibraryModule::StartupModule()
{
}

void FAwesomeBlueprintLibraryModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAwesomeBlueprintLibraryModule, AwesomeBlueprintLibrary)

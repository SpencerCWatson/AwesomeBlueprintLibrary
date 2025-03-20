
#include "AwesomeBL.h"

#include "BlueprintEditor.h"
#include "Engine/AssetManager.h"


bool UAwesomeBL::GetPrimaryAssetData(const FPrimaryAssetId& PrimaryAssetId, FAssetData& OutAssetData)
{
	if (const UAssetManager* AssetManager = UAssetManager::GetIfInitialized())
	{
		return AssetManager->GetPrimaryAssetData(PrimaryAssetId, OutAssetData);
	}
	
	OutAssetData = FAssetData();
	return false;
}

void UAwesomeBL::AsyncLoadPrimaryAsset(const FPrimaryAssetId& AssetToLoad, const TArray<FName>& LoadBundles, const FAsyncLoadPrimaryAsset& OnLoad)
{
	TDelegate<void(const FPrimaryAssetId&, UObject*)> Delegate;
	Delegate.BindUFunction(const_cast<UObject*>(OnLoad.GetUObject()), OnLoad.GetFunctionName());
	TAsyncLoadPrimaryAsset<UObject>(AssetToLoad, LoadBundles, Delegate);
}

void UAwesomeBL::AsyncLoadPrimaryAssetWithTags(const FPrimaryAssetId& AssetToLoad, const TArray<FName>& LoadBundles, const FAsyncLoadPrimaryAssetWithGameplayTags& OnLoad, const FGameplayTagContainer& Tags)
{
	TDelegate<void(const FPrimaryAssetId&, UObject*)> Delegate;
	Delegate.BindLambda([OnLoad, Tags](const FPrimaryAssetId& AssetToLoad, UObject* LoadedObject)
	{
		OnLoad.ExecuteIfBound(AssetToLoad, LoadedObject, Tags);
	});
	TAsyncLoadPrimaryAsset<UObject>(AssetToLoad, LoadBundles, Delegate);
}

void UAwesomeBL::AsyncLoadPrimaryAssets(const TArray<FPrimaryAssetId>& AssetsToLoad, const TArray<FName>& LoadBundles, const FAsyncLoadPrimaryAssetList& OnLoad)
{
	TDelegate<void(const TArray<FPrimaryAssetId>&, const TArray<UObject*>&)> Delegate;
	Delegate.BindUFunction(const_cast<UObject*>(OnLoad.GetUObject()), OnLoad.GetFunctionName());
	TAsyncLoadPrimaryAssetList(AssetsToLoad, LoadBundles, Delegate);
}

void UAwesomeBL::AsyncLoadPrimaryAssetsWithTags(const TArray<FPrimaryAssetId>& AssetsToLoad, const TArray<FName>& LoadBundles, const FAsyncLoadPrimaryAssetListWithGameplayTags& OnLoad, const FGameplayTagContainer& Tags)
{
	TDelegate<void(const TArray<FPrimaryAssetId>&, const TArray<UObject*>&)> Delegate;
	Delegate.BindLambda([OnLoad, Tags](const TArray<FPrimaryAssetId>& AssetsToLoad, const TArray<UObject*>& LoadedObjects)
	{
		OnLoad.ExecuteIfBound(AssetsToLoad, LoadedObjects, Tags);
	});
	TAsyncLoadPrimaryAssetList(AssetsToLoad, LoadBundles, Delegate);
}

void UAwesomeBL::AsyncLoadAsset(const TSoftObjectPtr<UObject> AssetToLoad, const FAsyncLoadAsset& OnLoad)
{
	TDelegate<void(UObject*)> Delegate;
	Delegate.BindUFunction(const_cast<UObject*>(OnLoad.GetUObject()), OnLoad.GetFunctionName());
	TAsyncLoadAsset(AssetToLoad, Delegate);
}

void UAwesomeBL::AsyncLoadAssetWithNameTags(const TSoftObjectPtr<UObject> AssetToLoad, const TArray<FName>& Tags, const FAsyncLoadAssetWithNameTags& OnLoad)
{
	TDelegate<void(UObject*)> Delegate;
	Delegate.BindLambda([OnLoad, Tags](UObject* LoadedObject)
	{
		OnLoad.ExecuteIfBound(LoadedObject, Tags);
	});
	TAsyncLoadAsset(AssetToLoad, Delegate);
}

void UAwesomeBL::AsyncLoadAssets(const TArray<TSoftObjectPtr<UObject>>& AssetListToLoad, const FAsyncLoadAssetList& OnLoad)
{
	TDelegate<void(const TArray<UObject*>&)> Delegate;
	Delegate.BindUFunction(const_cast<UObject*>(OnLoad.GetUObject()), OnLoad.GetFunctionName());
	TAsyncLoadAssets(AssetListToLoad, Delegate);
}

void UAwesomeBL::AsyncLoadAssetsWithNameTags(const TArray<TSoftObjectPtr<UObject>>& AssetListToLoad, const TArray<FName>& Tags, const FAsyncLoadAssetListWithNameTags& OnLoad)
{
	TDelegate<void(const TArray<UObject*>&)> Delegate;
	Delegate.BindLambda([OnLoad, Tags](const TArray<UObject*>& LoadedObject)
	{
		OnLoad.ExecuteIfBound(LoadedObject, Tags);
	});
	TAsyncLoadAssets(AssetListToLoad, Delegate);
}

void UAwesomeBL::NameArrayToStringArray(const TArray<FName>& Source, TArray<FString>& Target)
{
	Target.Reset(Source.Num());
	for (const FName& Name : Source)
	{
		Target.Emplace(Name.ToString());
	}
}

void UAwesomeBL::StringArrayToNameArray(const TArray<FString>& Source, TArray<FName>& Target)
{
	ConvertArray(Source, Target);
}

void UAwesomeBL::IntArrayToFloatArray(const TArray<int32>& Source, TArray<float>& Target)
{
	ConvertArray(Source, Target);
}

void UAwesomeBL::FloatArrayToIntArray(const TArray<float>& Source, TArray<int32>& Target)
{
	ConvertArray(Source, Target);
}

void UAwesomeBL::QuitGame()
{
	FPlatformMisc::RequestExit(false);
}

void UAwesomeBL::RegisterWithGameInstance(const UObject* WorldContextObject, UObject* Object)
{
	if (WorldContextObject && Object)
	{
		if (UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
		{
			GameInstance->RegisterReferencedObject(Object);
		}
	}
}

void UAwesomeBL::UnregisterWithGameInstance(const UObject* WorldContextObject, UObject* Object)
{
	if (WorldContextObject && Object)
	{
		if (UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
		{
			GameInstance->UnregisterReferencedObject(Object);
		}
	}
}

void UAwesomeBL::DebugBreak()
{
	UE_DEBUG_BREAK();
}

void UAwesomeBL::InjectControllerAnalog(const FKey& Key, const float AnalogValue, const bool bRepeat)
{
	const uint32* KeyCodePtr;
	const uint32* CharCodePtr;
	FInputKeyManager::Get().GetCodesFromKey(Key, KeyCodePtr, CharCodePtr);

	const uint32 KeyCode = KeyCodePtr ? *KeyCodePtr : 0;
	const uint32 CharCode = CharCodePtr ? *CharCodePtr : 0;

	const FAnalogInputEvent AnalogInputEvent(Key, FModifierKeysState(), 0, bRepeat, CharCode, KeyCode, AnalogValue );
	FSlateApplication::Get().ProcessAnalogInputEvent(AnalogInputEvent);
	
}

void UAwesomeBL::InjectControllerButtonPress(const FKey& Key, const bool bRepeat)
{
	const uint32* KeyCodePtr;
	const uint32* CharCodePtr;
	FInputKeyManager::Get().GetCodesFromKey(Key, KeyCodePtr, CharCodePtr);

	const uint32 KeyCode = KeyCodePtr ? *KeyCodePtr : 0;
	const uint32 CharCode = CharCodePtr ? *CharCodePtr : 0;

	FKeyEvent KeyEvent(Key, FModifierKeysState(), 0, bRepeat, KeyCode, CharCode);
	const bool DownResult = FSlateApplication::Get().ProcessKeyDownEvent(KeyEvent);

	if (CharCodePtr)
	{
		FCharacterEvent CharacterEvent(CharCode, FModifierKeysState(), 0, bRepeat);
		FSlateApplication::Get().ProcessKeyCharEvent(CharacterEvent);
	}
}

void UAwesomeBL::InjectControllerButtonReleased(const FKey& Key, const bool bRepeat)
{
	const uint32* KeyCodePtr;
	const uint32* CharCodePtr;
	FInputKeyManager::Get().GetCodesFromKey(Key, KeyCodePtr, CharCodePtr);

	const uint32 KeyCode = KeyCodePtr ? *KeyCodePtr : 0;
	const uint32 CharCode = CharCodePtr ? *CharCodePtr : 0;

	FKeyEvent KeyEvent(Key, FModifierKeysState(), 0, bRepeat, KeyCode, CharCode);
	FSlateApplication::Get().ProcessKeyUpEvent(KeyEvent);
}

UActorComponent* UAwesomeBL::GetComponent(const FComponentReference& ComponentReference, AActor* OwningActor)
{
	return ComponentReference.GetComponent(OwningActor);
}

UActorComponent* UAwesomeBL::GetComponentSoft(const FSoftComponentReference& ComponentReference, AActor* OwningActor)
{
	return ComponentReference.GetComponent(OwningActor);
}

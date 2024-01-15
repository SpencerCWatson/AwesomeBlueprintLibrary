
#include "AwesomeBlueprintLibrary.h"
#include "Engine/AssetManager.h"


bool UAwesomeBlueprintLibrary::GetPrimaryAssetData(const FPrimaryAssetId& PrimaryAssetId, FAssetData& OutAssetData)
{
	if (const UAssetManager* AssetManager = UAssetManager::GetIfInitialized())
	{
		return AssetManager->GetPrimaryAssetData(PrimaryAssetId, OutAssetData);
	}
	
	OutAssetData = FAssetData();
	return false;
}

void UAwesomeBlueprintLibrary::AsyncLoadPrimaryAsset(const FPrimaryAssetId& AssetToLoad, const TArray<FName>& LoadBundles, const FAsyncLoadPrimaryAsset& OnLoad)
{
	TAsyncLoadPrimaryAsset(AssetToLoad, LoadBundles, OnLoad);
}

void UAwesomeBlueprintLibrary::AsyncLoadPrimaryAssetWithTags(const FPrimaryAssetId& AssetToLoad, const TArray<FName>& LoadBundles, const FAsyncLoadPrimaryAssetWithGameplayTags& OnLoad, const FGameplayTagContainer& Tags)
{
	TAsyncLoadPrimaryAsset(AssetToLoad, LoadBundles, OnLoad, Tags);
}

void UAwesomeBlueprintLibrary::AsyncLoadPrimaryAssets(const TArray<FPrimaryAssetId>& AssetsToLoad, const TArray<FName>& LoadBundles, const FAsyncLoadPrimaryAssetList& OnLoad)
{
	TAsyncLoadPrimaryAssetList(AssetsToLoad, LoadBundles, OnLoad);
}

void UAwesomeBlueprintLibrary::AsyncLoadPrimaryAssetsWithTags(const TArray<FPrimaryAssetId>& AssetsToLoad, const TArray<FName>& LoadBundles, const FAsyncLoadPrimaryAssetListWithGameplayTags& OnLoad, const FGameplayTagContainer& Tags)
{
	TAsyncLoadPrimaryAssetList(AssetsToLoad, LoadBundles, OnLoad,Tags);
}

void UAwesomeBlueprintLibrary::AsyncLoadAsset(const TSoftObjectPtr<UObject> AssetToLoad, const FAsyncLoadAsset& OnLoad)
{
	TAsyncLoadAsset(AssetToLoad, OnLoad);
}

void UAwesomeBlueprintLibrary::AsyncLoadAssetWithNameTags(const TSoftObjectPtr<UObject> AssetToLoad, const TArray<FName>& Tags, const FAsyncLoadAssetWithNameTags& OnLoad)
{
	TAsyncLoadAsset(AssetToLoad, OnLoad, Tags);
}

void UAwesomeBlueprintLibrary::AsyncLoadAssets(const TArray<TSoftObjectPtr<UObject>>& AssetListToLoad, const FAsyncLoadAssetList& OnLoad)
{
	TAsyncLoadAssets(AssetListToLoad, OnLoad);
}

void UAwesomeBlueprintLibrary::AsyncLoadAssetsWithNameTags(const TArray<TSoftObjectPtr<UObject>>& AssetListToLoad, const TArray<FName>& Tags, const FAsyncLoadAssetListWithNameTags& OnLoad)
{
	TAsyncLoadAssets(AssetListToLoad, OnLoad, Tags);
}

void UAwesomeBlueprintLibrary::NameArrayToStringArray(const TArray<FName>& Source, TArray<FString>& Target)
{
	Target.Reset(Source.Num());
	for (const FName& Name : Source)
	{
		Target.Emplace(Name.ToString());
	}
}

void UAwesomeBlueprintLibrary::StringArrayToNameArray(const TArray<FString>& Source, TArray<FName>& Target)
{
	ConvertArray(Source, Target);
}

void UAwesomeBlueprintLibrary::IntArrayToFloatArray(const TArray<int32>& Source, TArray<float>& Target)
{
	ConvertArray(Source, Target);
}

void UAwesomeBlueprintLibrary::FloatArrayToIntArray(const TArray<float>& Source, TArray<int32>& Target)
{
	ConvertArray(Source, Target);
}

void UAwesomeBlueprintLibrary::QuitGame()
{
	FPlatformMisc::RequestExit(false);
}

void UAwesomeBlueprintLibrary::RegisterWithGameInstance(const UObject* WorldContextObject, UObject* Object)
{
	if (WorldContextObject && Object)
	{
		if (UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
		{
			GameInstance->RegisterReferencedObject(Object);
		}
	}
}

void UAwesomeBlueprintLibrary::UnregisterWithGameInstance(const UObject* WorldContextObject, UObject* Object)
{
	if (WorldContextObject && Object)
	{
		if (UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
		{
			GameInstance->UnregisterReferencedObject(Object);
		}
	}
}

void UAwesomeBlueprintLibrary::DebugBreak()
{
	UE_DEBUG_BREAK();
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "AwesomeBL.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"


bool UAwesomeBL::GetPrimaryAssetData(const FPrimaryAssetId& PrimaryAssetId, FAssetData& AssetData)
{
	if (UAssetManager* Manager = UAssetManager::GetIfValid())
	{
		return Manager->GetPrimaryAssetData(PrimaryAssetId, AssetData);
	}
	
	AssetData = FAssetData();
	return false;
}

void UAwesomeBL::AsyncLoadPrimaryAsset(const FPrimaryAssetId& AssetToLoad, const TArray<FName>& LoadBundles,
	const FAsyncLoadPrimaryAssetSignature& OnLoad)
{
	if (UAssetManager* Manager = UAssetManager::GetIfValid())
	{
		// Lambda start
		FStreamableDelegate OnLoadDelegate = FStreamableDelegate::CreateLambda([AssetToLoad, OnLoad]()
		{
			FAssetData AssetData;
			//Check if the PrimaryAsset is loaded
			if(UAssetManager* Manager = UAssetManager::GetIfValid())
			{
				if(UObject* LoadedAsset = Manager->GetPrimaryAssetObject(AssetToLoad))
				{
					OnLoad.ExecuteIfBound(AssetToLoad, LoadedAsset);
				}
			}
		});
		// Lambda end
		
		Manager->LoadPrimaryAsset(AssetToLoad, LoadBundles, OnLoadDelegate);
	}
}

void UAwesomeBL::AsyncLoadPrimaryAssetWithGameplayTags(const FPrimaryAssetId& AssetToLoad, const TArray<FName>& LoadBundles,
	const FAsyncLoadPrimaryAssetWithGameplayTagsSignature& OnLoad, const FGameplayTagContainer& GameplayTags)
{
	if (UAssetManager* Manager = UAssetManager::GetIfValid())
	{
		// Lambda start
		FStreamableDelegate OnLoadDelegate = FStreamableDelegate::CreateLambda([AssetToLoad, OnLoad, GameplayTags]()
		{
			FAssetData AssetData;
			//Check if the PrimaryAsset is loaded
			if(UAssetManager* Manager = UAssetManager::GetIfValid())
			{
				if(UObject* LoadedAsset = Manager->GetPrimaryAssetObject(AssetToLoad))
				{
					OnLoad.ExecuteIfBound(AssetToLoad, LoadedAsset, GameplayTags);
				}
			}
		});
		// Lambda end
		
		Manager->LoadPrimaryAsset(AssetToLoad, LoadBundles, OnLoadDelegate);
	}
	
}

void UAwesomeBL::AsyncLoadPrimaryAssets(const TArray<FPrimaryAssetId>& AssetsToLoad, const TArray<FName>& LoadBundles,
                                                const FAsyncLoadPrimaryAssetsSignature& OnLoad)
{
	if (UAssetManager* Manager = UAssetManager::GetIfValid())
	{

		// Lambda Start
		FStreamableDelegate OnLoadDelegate = FStreamableDelegate::CreateLambda([AssetsToLoad, OnLoad]()
		{
			if (UAssetManager* Manager = UAssetManager::GetIfValid())
			{
				TArray<FPrimaryAssetId> LoadedPrimaryAssets;
				TArray<UObject*> LoadedAssets;
				
				for (FPrimaryAssetId AssetId : AssetsToLoad)
				{
					if(UObject* LoadedAsset= Manager->GetPrimaryAssetObject(AssetId))
					{
						LoadedPrimaryAssets.Emplace(AssetId);
						LoadedAssets.Emplace(LoadedAsset);
					}
				}
				
				if(!LoadedPrimaryAssets.IsEmpty())
				{
					OnLoad.ExecuteIfBound(LoadedPrimaryAssets, LoadedAssets);
				}
			}
		});
		//Lambda End
		
		Manager->LoadPrimaryAssets(AssetsToLoad, LoadBundles, OnLoadDelegate);
	}
}

void UAwesomeBL::AsyncLoadPrimaryAssetsWithGameplayTags(const TArray<FPrimaryAssetId>& AssetsToLoad, const TArray<FName>& LoadBundles,
	const FAsyncLoadPrimaryAssetsWithGameplayTagsSignature& OnLoad, const FGameplayTagContainer& GameplayTags)
{
	if (UAssetManager* Manager = UAssetManager::GetIfValid())
	{

		// Lambda Start
		FStreamableDelegate OnLoadDelegate = FStreamableDelegate::CreateLambda([AssetsToLoad, OnLoad, GameplayTags]()
		{
			if (UAssetManager* Manager = UAssetManager::GetIfValid())
			{
				TArray<FPrimaryAssetId> LoadedPrimaryAssets;
				TArray<UObject*> LoadedAssets;
				
				for (FPrimaryAssetId AssetId : AssetsToLoad)
				{
					if(UObject* LoadedAsset= Manager->GetPrimaryAssetObject(AssetId))
					{
						LoadedPrimaryAssets.Emplace(AssetId);
						LoadedAssets.Emplace(LoadedAsset);
					}
				}
				
				if(!LoadedPrimaryAssets.IsEmpty())
				{
					OnLoad.ExecuteIfBound(LoadedPrimaryAssets, LoadedAssets, GameplayTags);
				}
			}
		});
		//Lambda End
		
		Manager->LoadPrimaryAssets(AssetsToLoad, LoadBundles, OnLoadDelegate);
	}
}

void UAwesomeBL::AsyncLoadAsset(TSoftObjectPtr<UObject> AssetToLoad, const FAsyncLoadAssetSignature& OnLoadDelegate)
{
	FStreamableManager& AssetLoader = UAssetManager::GetStreamableManager();
	FStreamableDelegate OnLoad = FStreamableDelegate::CreateLambda([AssetToLoad, OnLoadDelegate]()
	{
		if(UObject* LoadedAsset = AssetToLoad.Get())
		{
			OnLoadDelegate.ExecuteIfBound(LoadedAsset);
		}
	});
	AssetLoader.RequestAsyncLoad(AssetToLoad.ToSoftObjectPath(), OnLoad);
}

void UAwesomeBL::AsyncLoadAssetWithTags(TSoftObjectPtr<UObject> AssetToLoad, const TArray<FName>& Tags, const FAsyncLoadAssetWithNameTagsSignature& OnLoadDelegate)
{
	FStreamableManager& AssetLoader = UAssetManager::GetStreamableManager();
	FStreamableDelegate OnLoad = FStreamableDelegate::CreateLambda([AssetToLoad, Tags, OnLoadDelegate]()
	{
		if(UObject* LoadedAsset = AssetToLoad.Get())
		{
			OnLoadDelegate.ExecuteIfBound(LoadedAsset, Tags);
		}
	});
	AssetLoader.RequestAsyncLoad(AssetToLoad.ToSoftObjectPath(), OnLoad);
}

void UAwesomeBL::AsyncLoadAssets(const TArray<TSoftObjectPtr<UObject>>& AssetsToLoad, const FAsyncLoadAssetsSignature& OnLoadDelegate)
{
	FStreamableManager& AssetLoader = UAssetManager::GetStreamableManager();
	// Lambda start
	FStreamableDelegate OnLoad = FStreamableDelegate::CreateLambda([AssetsToLoad, OnLoadDelegate]()
	{
		// Verify load and send back the object pointers
		TArray<UObject*> LoadedAssets;
		for (TSoftObjectPtr<UObject> Asset: AssetsToLoad)
		{
			if (UObject* LoadedAsset = Asset.Get())
			{
				LoadedAssets.Add(LoadedAsset);
			}
		}
		
		OnLoadDelegate.ExecuteIfBound(LoadedAssets);
	});
	// Lambda end

	//Make array of valid SoftObjectPaths for the request.
	TArray<FSoftObjectPath> SoftObjectPaths;
	for(TSoftObjectPtr<UObject> SoftObjectPointer : AssetsToLoad)
	{
		if(!SoftObjectPointer.IsNull())
		{
			SoftObjectPaths.Add(SoftObjectPointer.ToSoftObjectPath());
		}
	}
	AssetLoader.RequestAsyncLoad(SoftObjectPaths, OnLoad);
}

void UAwesomeBL::AsyncLoadAssetsWithTags(const TArray<TSoftObjectPtr<UObject>>& AssetsToLoad, const TArray<FName>& Tags, const FAsyncLoadAssetsWithNameTagsSignature& OnLoadDelegate)
{
	FStreamableManager& AssetLoader = UAssetManager::GetStreamableManager();

	//Lambda start
	FStreamableDelegate OnLoad = FStreamableDelegate::CreateLambda([AssetsToLoad, Tags, OnLoadDelegate]()
	{
		TArray<UObject*> LoadedAssets;
		for (TSoftObjectPtr<UObject> Asset: AssetsToLoad)
		{
			if (UObject* LoadedObject = Asset.Get())
			{
				LoadedAssets.Add(LoadedObject);
			}
		}
		
		OnLoadDelegate.ExecuteIfBound(LoadedAssets, Tags);
	});
	//Lambda end

	//Make array of valid SoftObjectPaths for the request.
	TArray<FSoftObjectPath> SoftObjectPaths;
	for(TSoftObjectPtr<UObject> SoftObjectPointer : AssetsToLoad)
	{
		if(!SoftObjectPointer.IsNull())
		{
			SoftObjectPaths.Add(SoftObjectPointer.ToSoftObjectPath());
		}
	}
	
	AssetLoader.RequestAsyncLoad(SoftObjectPaths, OnLoad);
}

void UAwesomeBL::NameArrayToStringArray(const TArray<FName>& NameArray, TArray<FString>& StringArray)
{
	StringArray.Empty();
	for(FName Name : NameArray)
	{
		StringArray.Emplace(Name.ToString());
	}
}

void UAwesomeBL::StringArrayToNameArray(const TArray<FString>& StringArray, TArray<FName>& NameArray)
{
	NameArray.Empty();
	for(FString String : StringArray)
	{
		NameArray.Emplace(FName(String));
	}
}

TArray<float> UAwesomeBL::IntArrayToFloatArray(const TArray<int32>& IntArray)
{
	TArray<float> FloatArrary;
	for(int32 Int : IntArray)
	{
		FloatArrary.Emplace(Int);
	}
	return FloatArrary;
}

TArray<int32> UAwesomeBL::FloatArrayToIntArray(const TArray<float>& FloatArray)
{
	TArray<int32> IntArray;
	for(float Float : FloatArray)
	{
		IntArray.Emplace(Float);
	}
	return IntArray;
}

void UAwesomeBL::QuitGame()
{
	FPlatformMisc::RequestExit(false);
}








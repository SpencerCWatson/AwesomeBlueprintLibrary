// Fill out your copyright notice in the Description page of Project Settings.


#include "AwesomeBL.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"


bool UAwesomeBL::GetPrimaryAssetData(const FPrimaryAssetId& PrimaryAssetId, FAssetData& AssetData)
{
	if (UAssetManager* AssetManager = UAssetManager::GetIfValid())
	{
		return AssetManager->GetPrimaryAssetData(PrimaryAssetId, AssetData);
	}
	
	AssetData = FAssetData();
	return false;
}

void UAwesomeBL::AsyncLoadPrimaryAsset(const FPrimaryAssetId& AssetToLoad, const TArray<FName>& LoadBundles,
	const FAsyncLoadPrimaryAssetSignature& OnLoad)
{
	if (UAssetManager* AssetManager = UAssetManager::GetIfValid())
	{
		// Lambda start
		FStreamableDelegate OnLoadDelegate = FStreamableDelegate::CreateLambda([AssetToLoad, OnLoad]()
		{
			FAssetData AssetData;
			//Check if the PrimaryAsset is loaded
			if(UAssetManager* AssetManager = UAssetManager::GetIfValid())
			{
				if(UObject* LoadedAsset = AssetManager->GetPrimaryAssetObject(AssetToLoad))
				{
					OnLoad.ExecuteIfBound(AssetToLoad, LoadedAsset);
				}
			}
		});
		// Lambda end
		
		AssetManager->LoadPrimaryAsset(AssetToLoad, LoadBundles, OnLoadDelegate);
	}
}

void UAwesomeBL::AsyncLoadPrimaryAssetWithGameplayTags(const FPrimaryAssetId& AssetToLoad, const TArray<FName>& LoadBundles,
	const FAsyncLoadPrimaryAssetWithGameplayTagsSignature& OnLoad, const FGameplayTagContainer& GameplayTags)
{
	if (UAssetManager* AssetManager = UAssetManager::GetIfValid())
	{
		// Lambda start
		FStreamableDelegate OnLoadDelegate = FStreamableDelegate::CreateLambda([AssetToLoad, OnLoad, GameplayTags]()
		{
			FAssetData AssetData;
			//Check if the PrimaryAsset is loaded
			if(UAssetManager* AssetManager = UAssetManager::GetIfValid())
			{
				if(UObject* LoadedAsset = AssetManager->GetPrimaryAssetObject(AssetToLoad))
				{
					OnLoad.ExecuteIfBound(AssetToLoad, LoadedAsset, GameplayTags);
				}
			}
		});
		// Lambda end
		
		AssetManager->LoadPrimaryAsset(AssetToLoad, LoadBundles, OnLoadDelegate);
	}
	
}

void UAwesomeBL::AsyncLoadPrimaryAssetList(const TArray<FPrimaryAssetId>& AssetsToLoad, const TArray<FName>& LoadBundles, const FAsyncLoadPrimaryAssetListSignature& OnLoad)
{
	if (UAssetManager* AssetManager = UAssetManager::GetIfValid())
	{

		// Lambda Start
		FStreamableDelegate OnLoadDelegate = FStreamableDelegate::CreateLambda([AssetsToLoad, OnLoad]()
		{
			if (UAssetManager* AssetManager = UAssetManager::GetIfValid())
			{
				TArray<FPrimaryAssetId> LoadedPrimaryAssets;
				TArray<UObject*> LoadedAssets;
				
				for (FPrimaryAssetId AssetId : AssetsToLoad)
				{
					if(UObject* LoadedAsset = AssetManager->GetPrimaryAssetObject(AssetId))
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
		
		AssetManager->LoadPrimaryAssets(AssetsToLoad, LoadBundles, OnLoadDelegate);
	}
}

void UAwesomeBL::AsyncLoadPrimaryAssetListWithGameplayTags(const TArray<FPrimaryAssetId>& AssetsToLoad, const TArray<FName>& LoadBundles, const FAsyncLoadPrimaryAssetListWithGameplayTagsSignature& OnLoad, const FGameplayTagContainer& GameplayTags)
{
	if (UAssetManager* AssetManager = UAssetManager::GetIfValid())
	{

		// Lambda Start
		FStreamableDelegate OnLoadDelegate = FStreamableDelegate::CreateLambda([AssetsToLoad, OnLoad, GameplayTags]()
		{
			if (UAssetManager* AssetManager = UAssetManager::GetIfValid())
			{
				TArray<FPrimaryAssetId> LoadedPrimaryAssets;
				TArray<UObject*> LoadedAssets;
				
				for (FPrimaryAssetId AssetId : AssetsToLoad)
				{
					if(UObject* LoadedAsset= AssetManager->GetPrimaryAssetObject(AssetId))
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
		
		AssetManager->LoadPrimaryAssets(AssetsToLoad, LoadBundles, OnLoadDelegate);
	}
}

void UAwesomeBL::AsyncLoadAsset(TSoftObjectPtr<UObject> AssetToLoad, const FAsyncLoadAssetSignature& OnLoadDelegate)
{
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
	FStreamableDelegate OnLoad = FStreamableDelegate::CreateLambda([AssetToLoad, OnLoadDelegate]()
	{
		if(UObject* LoadedAsset = AssetToLoad.Get())
		{
			OnLoadDelegate.ExecuteIfBound(LoadedAsset);
		}
	});
	StreamableManager.RequestAsyncLoad(AssetToLoad.ToSoftObjectPath(), OnLoad);
}

void UAwesomeBL::AsyncLoadAssetWithNameTags(TSoftObjectPtr<UObject> AssetToLoad, const TArray<FName>& Tags, const FAsyncLoadAssetWithNameTagsSignature& OnLoadDelegate)
{
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
	FStreamableDelegate OnLoad = FStreamableDelegate::CreateLambda([AssetToLoad, Tags, OnLoadDelegate]()
	{
		if(UObject* LoadedAsset = AssetToLoad.Get())
		{
			OnLoadDelegate.ExecuteIfBound(LoadedAsset, Tags);
		}
	});
	StreamableManager.RequestAsyncLoad(AssetToLoad.ToSoftObjectPath(), OnLoad);
}

void UAwesomeBL::AsyncLoadAssetList(const TArray<TSoftObjectPtr<UObject>>& AssetListToLoad, const FAsyncLoadAssetListSignature& OnLoadDelegate)
{
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
	// Lambda start
	FStreamableDelegate OnLoad = FStreamableDelegate::CreateLambda([AssetListToLoad, OnLoadDelegate]()
	{
		// Verify load and send back the object pointers
		TArray<UObject*> LoadedAssets;
		for (TSoftObjectPtr<UObject> Asset: AssetListToLoad)
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
	for(TSoftObjectPtr<UObject> SoftObjectPointer : AssetListToLoad)
	{
		if(!SoftObjectPointer.IsNull())
		{
			SoftObjectPaths.Add(SoftObjectPointer.ToSoftObjectPath());
		}
	}
	StreamableManager.RequestAsyncLoad(SoftObjectPaths, OnLoad);
}

void UAwesomeBL::AsyncLoadAssetListWithNameTags(const TArray<TSoftObjectPtr<UObject>>& AssetListToLoad, const TArray<FName>& Tags, const FAsyncLoadAssetListWithNameTagsSignature& OnLoadDelegate)
{
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();

	//Lambda start
	FStreamableDelegate OnLoad = FStreamableDelegate::CreateLambda([AssetListToLoad, Tags, OnLoadDelegate]()
	{
		TArray<UObject*> LoadedAssets;
		for (TSoftObjectPtr<UObject> Asset: AssetListToLoad)
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
	for(TSoftObjectPtr<UObject> SoftObjectPointer : AssetListToLoad)
	{
		if(!SoftObjectPointer.IsNull())
		{
			SoftObjectPaths.Add(SoftObjectPointer.ToSoftObjectPath());
		}
	}
	
	StreamableManager.RequestAsyncLoad(SoftObjectPaths, OnLoad);
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

void UAwesomeBL::RegisterWithGameInstance(UObject* Object)
{
	if(UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(Object))
	{
		GameInstance->RegisterReferencedObject(Object);
	}
}

void UAwesomeBL::UnegisterWithGameInstance(UObject* Object)
{
	if(UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(Object))
	{
		GameInstance->UnregisterReferencedObject(Object);
	}
}






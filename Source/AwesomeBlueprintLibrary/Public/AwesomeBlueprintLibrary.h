#pragma once

#include "GameplayTagContainer.h"
#include "Engine/AssetManager.h"
#include "kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "AwesomeBlueprintLibrary.generated.h"

/**
 * Blueprint library designed specifically to extend blueprint functionality. Some of these functions may be
 * useful in cpp but that is not their intent.
 */
UCLASS()
class AWESOMEBLUEPRINTLIBRARY_API UAwesomeBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//~~~~	PrimaryAsset Helpers	~~~~
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	DECLARE_DYNAMIC_DELEGATE_TwoParams(FAsyncLoadPrimaryAsset, const FPrimaryAssetId& , PrimaryAssetId, UObject*, LoadedAsset);
	DECLARE_DYNAMIC_DELEGATE_ThreeParams(FAsyncLoadPrimaryAssetWithGameplayTags, const FPrimaryAssetId& , PrimaryAssetId, UObject*, LoadedAsset, const FGameplayTagContainer& , GameplayTags);
	DECLARE_DYNAMIC_DELEGATE_TwoParams(FAsyncLoadPrimaryAssetList, const TArray<FPrimaryAssetId>& , PrimaryAssetIds, const TArray<UObject*>&, LoadedAssets);
	DECLARE_DYNAMIC_DELEGATE_ThreeParams(FAsyncLoadPrimaryAssetListWithGameplayTags, const TArray<FPrimaryAssetId>& , PrimaryAssetIds, const TArray<UObject*>&, LoadedAssets, const FGameplayTagContainer&, GameplayTags);

	/**
	 * Gets the FAssetData for a primary asset with the specified type/name, will only work for once that have been scanned for already. Returns true if it found a valid data
	 * @param PrimaryAssetId	Primary Asset Id to get the Asset Data from
	 * @param OutAssetData		Asset Data of the Primary Asset
	 * @return					Whether the Asset Data was successfully retrieved
	 */
	UFUNCTION(BlueprintPure, Category="Awesome Blueprint Library|Loading Helpers")
	static bool GetPrimaryAssetData(const FPrimaryAssetId& PrimaryAssetId, FAssetData& OutAssetData);
	
	/**
	 * Loads a PrimaryAsset.
	 * @param AssetToLoad		PrimaryAsset to be loaded.
	 * @param LoadBundles		Bundles to activate with load.
	 * @param OnLoad			Delegate to call when loading has finished.
	 */
	UFUNCTION(BlueprintCallable, Category="Awesome Blueprint Library|Loading Helpers")
	static void AsyncLoadPrimaryAsset(const FPrimaryAssetId& AssetToLoad, const TArray<FName>& LoadBundles, const FAsyncLoadPrimaryAsset& OnLoad);

	/**
	 * Loads a PrimaryAsset with Gameplay Tags attached.
	 * @param AssetToLoad		PrimaryAsset to be loaded.
	 * @param LoadBundles		Bundles to activate with load.
	 * @param OnLoad			Delegate to call when loading has finished.
	 * @param Tags				Tags available in delegate call. 
	 */
	UFUNCTION(BlueprintCallable, Category="Awesome Blueprint Library|Loading Helpers")
	static void AsyncLoadPrimaryAssetWithTags(const FPrimaryAssetId& AssetToLoad, const TArray<FName>& LoadBundles, const FAsyncLoadPrimaryAssetWithGameplayTags& OnLoad, const FGameplayTagContainer& Tags);

	/**
	 * Loads a list of PrimaryAssets.
	 * @param AssetsToLoad		PrimaryAsset to be loaded.
	 * @param LoadBundles		Bundles to activate with load.
	 * @param OnLoad			Delegate to call when loading has finished.
	 */
	UFUNCTION(BlueprintCallable, Category="Awesome Blueprint Library|Loading Helpers")
	static void AsyncLoadPrimaryAssets(const TArray<FPrimaryAssetId>& AssetsToLoad, const TArray<FName>& LoadBundles, const FAsyncLoadPrimaryAssetList& OnLoad);

	/**
	 * Loads a list of PrimaryAssets with GameplayTags attached.
	 * @param AssetsToLoad		PrimaryAsset to be loaded.
	 * @param LoadBundles		Bundles to activate with load.
	 * @param OnLoad			Delegate to call when loading has finished.
	 * @param Tags				Tags available in delegate call. 
	 */
	UFUNCTION(BlueprintCallable, Category="Awesome Blueprint Library|Loading Helpers")
	static void AsyncLoadPrimaryAssetsWithTags(const TArray<FPrimaryAssetId>& AssetsToLoad, const TArray<FName>& LoadBundles, const FAsyncLoadPrimaryAssetListWithGameplayTags& OnLoad, const FGameplayTagContainer& Tags);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~
	//~~~~	Loading Helpers	~~~~
	//~~~~~~~~~~~~~~~~~~~~~~~~~~

	DECLARE_DYNAMIC_DELEGATE_OneParam(FAsyncLoadAsset, UObject*, LoadedAsset);
	DECLARE_DYNAMIC_DELEGATE_TwoParams(FAsyncLoadAssetWithNameTags, UObject*, LoadedAsset, const TArray<FName>&, Tags);
	DECLARE_DYNAMIC_DELEGATE_OneParam(FAsyncLoadAssetList, const TArray<UObject*>&, LoadedAssets);
	DECLARE_DYNAMIC_DELEGATE_TwoParams(FAsyncLoadAssetListWithNameTags, const TArray<UObject*>&, LoadedAssets, const TArray<FName>&, Tags);

	/**
	 * Async load a SoftObjectPtr with a bindable delegate.
	 * @param AssetToLoad		SoftObjectPtr to be loaded.
	 * @param OnLoad			Delegate to call when loading has finished.
	 */
	UFUNCTION(BlueprintCallable, Category="Awesome Blueprint Library|Loading Helpers")
	static void AsyncLoadAsset(TSoftObjectPtr<UObject> AssetToLoad, const FAsyncLoadAsset& OnLoad);

	/**
	 * Async load a SoftObjectPtr with a bindable delegate and Name tags attached.
	 * @param AssetToLoad		SoftObjectPtr to be loaded.
	 * @param Tags				Tags available in delegate call. 
	 * @param OnLoad			Delegate to call when loading has finished.
	 */
	UFUNCTION(BlueprintCallable, Category="Awesome Blueprint Library|Loading Helpers")
	static void AsyncLoadAssetWithNameTags(TSoftObjectPtr<UObject> AssetToLoad, const TArray<FName>& Tags, const FAsyncLoadAssetWithNameTags& OnLoad);

	/**
	 * Async load a list of SoftObjectPtrs with a bindable delegate.
	 * @param AssetListToLoad	SoftObjectPtr list to be loaded.
	 * @param OnLoad			Delegate to call when loading has finished.
	 */
	UFUNCTION(BlueprintCallable, Category="Awesome Blueprint Library|Loading Helpers")
	static void AsyncLoadAssets(const TArray<TSoftObjectPtr<UObject>>& AssetListToLoad, const FAsyncLoadAssetList& OnLoad);

	/**
	 * Async load a list of SoftObjectPtrs with a bindable delegate and Name tags attached.
	 * @param AssetListToLoad	SoftObjectPtr list to be loaded.
	 * @param Tags				Tags available in delegate call. 
	 * @param OnLoad			Delegate to call when loading has finished.
	 */
	UFUNCTION(BlueprintCallable, Category="Awesome Blueprint Library|Loading Helpers")
	static void AsyncLoadAssetsWithNameTags(const TArray<TSoftObjectPtr<UObject>>& AssetListToLoad, const TArray<FName>& Tags, const FAsyncLoadAssetListWithNameTags& OnLoad);
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~
	//~~~~	Data Helpers	~~~~
	//~~~~~~~~~~~~~~~~~~~~~~~~~~

	/**
	 * Make a literal GameplayTag from a Name
	 * @param Tag				The Name of the tag to search for
	 * @return					Will return the corresponding FGameplayTag or an empty one if not found.
	 */
	UFUNCTION(BlueprintPure, Category="Awesome Blueprint Library|Data Helpers")
	static FGameplayTag MakeLiteralGameplayTag(const FName& Tag) { return FGameplayTag::RequestGameplayTag(Tag); }

	/**
	 * Turn a Name array to a String array
	 * @param Source			Source array
	 * @param Target			Target array
	 */
	UFUNCTION(BlueprintPure, Category="Awesome Blueprint Library|Data Helpers")
	static void NameArrayToStringArray(const TArray<FName>& Source, TArray<FString>& Target );

	/**
	 * Turn a Name array to a String array by reference
	 * @param Source			Source array
	 * @param Target_Ref		Target array
	 */
	UFUNCTION(BlueprintCallable, Category="Awesome Blueprint Library|Data Helpers")
	static void NameArrayToStringArrayRef(const TArray<FName>& Source, UPARAM(ref) TArray<FString>& Target_Ref ) { NameArrayToStringArray(Source, Target_Ref); }

	/**
	 * Turn a String array into a Name array
	 * @param Source			Source array
	 * @param Target			Target array
	 */
	UFUNCTION(BlueprintPure, Category="Awesome Blueprint Library|Data Helpers")
	static void StringArrayToNameArray(const TArray<FString>& Source, TArray<FName>& Target );

	/**
	 * Turn a String array into a Name array by reference
	 * @param Source			Source array
	 * @param Target_Ref		Target array
	 */
	UFUNCTION(BlueprintCallable, Category="Awesome Blueprint Library|Data Helpers")
	static void StringArrayToNameArrayRef(const TArray<FString>& Source, UPARAM(ref) TArray<FName>& Target_Ref ) { StringArrayToNameArray(Source, Target_Ref); }

	/**
	 * Turns an Int array into a Float array
	 * @param Source			Source array
	 * @param Target			Target array
	 */
	UFUNCTION(BlueprintPure, Category="Awesome Blueprint Library|Data Helpers")
	static void IntArrayToFloatArray(const TArray<int32>& Source, TArray<float>& Target);

	/**
	 * Turn a Float array into an Int array
	 * @param Source			Source array
	 * @param Target			Target array
	 */
	UFUNCTION(BlueprintPure, Category="Awesome Blueprint Library|Data Helpers")
	static void FloatArrayToIntArray(const TArray<float>& Source, TArray<int32>& Target);
	
	//~~~~~~~~~~~~~~~~~~
	//~~~~~ Basics	~~~~
	//~~~~~~~~~~~~~~~~~~

	/**
	 *	Quit game without a need for a player controller.
	 *	@note Useful for shutting down a dedicated server.
	 */
	UFUNCTION(BlueprintCallable, Category="Awesome Blueprint Library|Basic Helpers")
	static void QuitGame();

	/**
	 *	Returns the game instance object.
	 *	@note Callable from Objects.
	 *	@param WorldContextObject	Object that we can obtain a world context from
	 *	@return						GameInstance
	 */
	UFUNCTION(BlueprintPure, Category="Awesome Blueprint Library|Basic Helpers", meta=(WorldContext="WorldContextObject", CallableWithoutWorldContext))
	static UGameInstance* GetGameInstance(const UObject* WorldContextObject) { return UGameplayStatics::GetGameInstance(WorldContextObject); }

	/**
	 *	Returns the current GameModeBase or Null if it can't be retrieved, such as on the client.
	 *	@note Callable from Objects.
	 *	@param WorldContextObject	Object that we can obtain a world context from
	 *	@return						GameMode
	 */
	UFUNCTION(BlueprintPure, Category="Awesome Blueprint Library|Basic Helpers", meta=(WorldContext="WorldContextObject", CallableWithoutWorldContext))
	static AGameModeBase* GetGameMode(const UObject* WorldContextObject) { return UGameplayStatics::GetGameMode(WorldContextObject); }

	/**
	 *	Returns the current GameStateBase or Null if it can't be retrieved.
	 *	@note Callable from Objects.
	 *	@param WorldContextObject	Object that we can obtain a world context from
	 *	@return						GameState
	 */
	UFUNCTION(BlueprintPure, Category="Awesome Blueprint Library|Basic Helpers", meta=(WorldContext="WorldContextObject", CallableWithoutWorldContext))
	static AGameStateBase* GetGameState(const UObject* WorldContextObject) { return UGameplayStatics::GetGameState(WorldContextObject); }

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//~~~~~ GameInstance Helpers	~~~~
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
	/**
	 * Registers an object to keep alive as long as the GameInstance of the world it lives in is alive
	 * @param WorldContextObject	Object that we can obtain a world context from
	 * @param Object				Object to register
	 */
	UFUNCTION(BlueprintCallable, Category="Awesome Blueprint Library|GameInstance Helpers", meta=(WorldContext="WorldContextObject", CallableWithoutWorldContext))
	static void RegisterWithGameInstance(const UObject* WorldContextObject, UObject* Object);

	/**
	 * Remove a referenced object from the GameInstance of the world it lives in, this will allow it to GC out
	 * @param WorldContextObject	Object that we can obtain a world context from
	 * @param Object				Object to unregister
	 */
	UFUNCTION(BlueprintCallable, Category="Awesome Blueprint Library|GameInstance Helpers", meta=(WorldContext="WorldContextObject", CallableWithoutWorldContext))
	static void UnregisterWithGameInstance(const UObject* WorldContextObject, UObject* Object);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~
	//~~~~~ Debug Helpers	~~~~
	//~~~~~~~~~~~~~~~~~~~~~~~~~~

	/** Trigger break point in debugger. Exists for easy blueprint access */
	UFUNCTION(BlueprintCallable, Category="Awesome Blueprint Library|GameInstance Helpers")
	static void DebugBreak();	

	//~~~~~~~~~~~~~~~~~~~~~
	//~~~~~ Templates ~~~~~
	//~~~~~~~~~~~~~~~~~~~~~

private:

	template<typename Delegate, typename... ArgTypes>
	static void TAsyncLoadAssets(const TArray<TSoftObjectPtr<>>& AssetsToLoad, const Delegate& OnLoad, ArgTypes... Args)
	{
		const FStreamableDelegate OnAssetsLoad = FStreamableDelegate::CreateLambda([AssetsToLoad, OnLoad, Args...]()
		{
			TArray<UObject*> LoadedAssets;
			for (const TSoftObjectPtr<>& Asset: AssetsToLoad)
			{
				if (UObject* LoadedAsset = Asset.Get())
				{
					LoadedAssets.Add(LoadedAsset);
				}
			}
			
			OnLoad.ExecuteIfBound(LoadedAssets, Args...);
		});
		
		TArray<FSoftObjectPath> SoftObjectPaths;
		for (const TSoftObjectPtr<>& SoftObjectPointer : AssetsToLoad)
		{
			if (!SoftObjectPointer.IsNull())
			{
				SoftObjectPaths.Add(SoftObjectPointer.ToSoftObjectPath());
			}
		}
	
		UAssetManager::GetStreamableManager().RequestAsyncLoad(SoftObjectPaths, OnAssetsLoad);
	}

	DECLARE_DELEGATE_OneParam(FOnAssetsWrapper, TArray<UObject*>)
	template<typename Delegate, typename... ArgTypes>
	static void TAsyncLoadAsset(const TSoftObjectPtr<> AssetToLoad, const Delegate& OnLoad, ArgTypes... Args)
	{
		TAsyncLoadAssets(TArray<TSoftObjectPtr<>>{ AssetToLoad }, FOnAssetsWrapper::CreateLambda([OnLoad, Args...](TArray<UObject*> LoadedAssets)
		{
			OnLoad.ExecuteIfBound(LoadedAssets.IsEmpty() ? nullptr : LoadedAssets[0], Args...);
		}) );
	}
	
	template<typename Delegate, typename... ArgTypes>
	static void TAsyncLoadPrimaryAssetList(const TArray<FPrimaryAssetId>& AssetsToLoad, const TArray<FName>& LoadBundles, const Delegate& OnLoad, ArgTypes... Args)
	{
		if (UAssetManager* AssetManager = UAssetManager::GetIfInitialized())
		{
			const FStreamableDelegate OnLoadDelegate = FStreamableDelegate::CreateLambda([AssetsToLoad, OnLoad, Args...]()
			{
				TArray<FPrimaryAssetId> LoadedPrimaryAssets;
				TArray<UObject*> LoadedAssets;

				const UAssetManager* AssetManager = UAssetManager::GetIfInitialized();
				for (const FPrimaryAssetId& AssetId : AssetsToLoad)
				{
					if (UObject* LoadedAsset = AssetManager->GetPrimaryAssetObject(AssetId))
					{
						LoadedPrimaryAssets.Emplace(AssetId);
						LoadedAssets.Emplace(LoadedAsset);
					}
				}
				
				OnLoad.ExecuteIfBound(LoadedPrimaryAssets, LoadedAssets, Args...);
			});
		
			AssetManager->LoadPrimaryAssets(AssetsToLoad, LoadBundles, OnLoadDelegate);
		}
	}

	DECLARE_DELEGATE_TwoParams(FBaseDelegate, const TArray<FPrimaryAssetId>&, const TArray<UObject*>&);
	template<typename Delegate, typename... ArgTypes>
	static void TAsyncLoadPrimaryAsset(const FPrimaryAssetId& AssetToLoad, const TArray<FName>& LoadBundles, const Delegate& OnLoad, ArgTypes... Args)
	{
		TAsyncLoadPrimaryAssetList(TArray<FPrimaryAssetId>{ AssetToLoad }, LoadBundles, FBaseDelegate::CreateLambda([OnLoad, Args...](const TArray<FPrimaryAssetId>& PrimaryAssetIds, const TArray<UObject*>& LoadedAssets)
		{
			OnLoad.ExecuteIfBound(PrimaryAssetIds.IsEmpty() ? FPrimaryAssetId() : PrimaryAssetIds[0], LoadedAssets.IsEmpty() ? nullptr : LoadedAssets[0], Args...);
		}));
	}

	template<typename SourceType, typename TargetType>
	static FORCEINLINE void ConvertArray(const SourceType& Source, TargetType& Target)
	{
		Target.Reset(Source.Num());
		Target.Append(Source);
	}
};
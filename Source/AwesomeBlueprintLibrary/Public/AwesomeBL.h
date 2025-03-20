#pragma once

#include "GameplayTagContainer.h"
#include "Engine/AssetManager.h"
#include "kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "AwesomeBL.generated.h"

/**
 * Blueprint library designed specifically to extend blueprint functionality. Some of these functions may be
 * useful in cpp but that is not their intent.
 */
UCLASS()
class AWESOMEBLUEPRINTLIBRARY_API UAwesomeBL : public UBlueprintFunctionLibrary
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
	UFUNCTION(BlueprintCallable, Category="Awesome Blueprint Library|Loading Helpers", meta = (AutoCreateRefTerm = "LoadBundles"))
	static void AsyncLoadPrimaryAsset(const FPrimaryAssetId& AssetToLoad, const TArray<FName>& LoadBundles, const FAsyncLoadPrimaryAsset& OnLoad);

	/**
	 * Loads a PrimaryAsset with Gameplay Tags attached.
	 * @param AssetToLoad		PrimaryAsset to be loaded.
	 * @param LoadBundles		Bundles to activate with load.
	 * @param OnLoad			Delegate to call when loading has finished.
	 * @param Tags				Tags available in delegate call. 
	 */
	UFUNCTION(BlueprintCallable, Category="Awesome Blueprint Library|Loading Helpers", meta = (AutoCreateRefTerm = "LoadBundles"))
	static void AsyncLoadPrimaryAssetWithTags(const FPrimaryAssetId& AssetToLoad, const TArray<FName>& LoadBundles, const FAsyncLoadPrimaryAssetWithGameplayTags& OnLoad, const FGameplayTagContainer& Tags);

	/**
	 * Loads a list of PrimaryAssets.
	 * @param AssetsToLoad		PrimaryAsset to be loaded.
	 * @param LoadBundles		Bundles to activate with load.
	 * @param OnLoad			Delegate to call when loading has finished.
	 */
	UFUNCTION(BlueprintCallable, Category="Awesome Blueprint Library|Loading Helpers", meta = (AutoCreateRefTerm = "LoadBundles"))
	static void AsyncLoadPrimaryAssets(const TArray<FPrimaryAssetId>& AssetsToLoad, const TArray<FName>& LoadBundles, const FAsyncLoadPrimaryAssetList& OnLoad);

	/**
	 * Loads a list of PrimaryAssets with GameplayTags attached.
	 * @param AssetsToLoad		PrimaryAsset to be loaded.
	 * @param LoadBundles		Bundles to activate with load.
	 * @param OnLoad			Delegate to call when loading has finished.
	 * @param Tags				Tags available in delegate call. 
	 */
	UFUNCTION(BlueprintCallable, Category="Awesome Blueprint Library|Loading Helpers", meta = (AutoCreateRefTerm = "LoadBundles"))
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
	UFUNCTION(BlueprintCallable, Category="Awesome Blueprint Library|Loading Helpers", meta = (AutoCreateRefTerm = "Tags"))
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
	UFUNCTION(BlueprintCallable, Category="Awesome Blueprint Library|Loading Helpers", meta = (AutoCreateRefTerm = "Tags"))
	static void AsyncLoadAssetsWithNameTags(const TArray<TSoftObjectPtr<UObject>>& AssetListToLoad, const TArray<FName>& Tags, const FAsyncLoadAssetListWithNameTags& OnLoad);
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~
	//~~~~	Data Helpers	~~~~
	//~~~~~~~~~~~~~~~~~~~~~~~~~~

	/**
	 * Make a literal GameplayTag from a Name
	 * @param Tag				The Name of the tag to search for
	 * @return					Will return the corresponding FGameplayTag or an empty one if not found.
	 */
	UFUNCTION(BlueprintPure, Category="Awesome Blueprint Library|Data Helpers", meta = (AutoCreateRefTerm = "Tag"))
	static FGameplayTag MakeLiteralGameplayTag(const FName& Tag) { return FGameplayTag::RequestGameplayTag(Tag); }

	
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

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//~~~~~   GameInstance Helpers   ~~~~
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
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

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//~~~~~   Debug Helpers   ~~~~
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	/** Trigger break point in debugger. Exists for easy blueprint access */
	UFUNCTION(BlueprintCallable, Category="Awesome Blueprint Library|GameInstance Helpers")
	static void DebugBreak();

	//~~~~~~~~~~~~~~~~~~~~
	//~~~~~   Input   ~~~~
	//~~~~~~~~~~~~~~~~~~~~
	
	/**
	 * Simulate an analog key input as controller one
	 * @param Key Key to simulate
	 * @param AnalogValue Key value
	 * @param bRepeat Should repeat?
	 */
	UFUNCTION(BlueprintCallable, Category="Awesome Blueprint Library|Input", meta=(AutoCreateRefTerm=Key))
	static void InjectControllerAnalog(const FKey& Key, const float AnalogValue, const bool bRepeat);

	/**
	 * Simulate a button being pressed as controller 1
	 * @param Key Key to simulate
	 * @param bRepeat Should repeat?
	 */
	UFUNCTION(BlueprintCallable, Category="Awesome Blueprint Library|Input", meta=(AutoCreateRefTerm=Key))
	static void InjectControllerButtonPress(const FKey& Key, const bool bRepeat);

	/**
	 * Simulate a button being released as controller 1
	 * @param Key Key to simulate
	 * @param bRepeat Should repeat?
	 */
	UFUNCTION(BlueprintCallable, Category="Awesome Blueprint Library|Input", meta=(AutoCreateRefTerm=Key))
	static void InjectControllerButtonReleased(const FKey& Key, const bool bRepeat);

	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~
	//~~~~~   Conversions   ~~~~
	//~~~~~~~~~~~~~~~~~~~~~~~~~~

	/**
	 * Find the component this points to
	 * @param ComponentReference	Target to get component from
	 * @param OwningActor			Actor to search on. Ignored if OtherActor is set
	 * @return						Found ActorComponent
	 */
	UFUNCTION(BlueprintPure, Category="Awesome Blueprint Library|Conversion", meta=(BlueprintAutocast))
	static UActorComponent* GetComponent(const FComponentReference& ComponentReference, AActor* OwningActor);

	/**
	 * Find the component this points to
	 * @param ComponentReference	Target to get component from
	 * @param OwningActor			Actor to search on. Ignored if OtherActor is set
	 * @return						Found ActorComponent
	 */
	UFUNCTION(BlueprintPure, DisplayName="Get Component", Category="Awesome Blueprint Library|Conversion", meta=(BlueprintAutocast))
	static UActorComponent* GetComponentSoft(const FSoftComponentReference& ComponentReference, AActor* OwningActor);

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
	
	
	//~~~~~~~~~~~~~~~~~~~~~
	//~~~~~ Templates ~~~~~
	//~~~~~~~~~~~~~~~~~~~~~
	
	template<class Class = UObject>
	static void TAsyncLoadAssets(const TArray<TSoftObjectPtr<Class>>& AssetsToLoad, const TDelegate<void(const TArray<Class*>&)>& OnLoad)
	{
		const FStreamableDelegate OnAssetsLoad = FStreamableDelegate::CreateLambda([AssetsToLoad, OnLoad]()
			{
				// todo find a better way to convert an array.
				TArray<Class*> LoadedAssets;
				LoadedAssets.Reserve(AssetsToLoad.Num());
				for (const TSoftObjectPtr<Class>& Asset: AssetsToLoad)
				{
					if (UObject* LoadedAsset = Asset.Get())
					{
						check(Cast<Class>(LoadedAsset));
						LoadedAssets.Add(Cast<Class>(LoadedAsset));
					}
				}
				
				OnLoad.ExecuteIfBound(LoadedAssets);
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
	
	template<class Class = UObject>
	static void TAsyncLoadAsset(const TSoftObjectPtr<Class> AssetToLoad, const TDelegate<void(Class*)>& OnLoad)
	{
		TAsyncLoadAssets<Class>(TArray<TSoftObjectPtr<Class>>{ AssetToLoad }, TDelegate<void(const TArray<UObject*>&)>::CreateLambda([OnLoad](const TArray<Class*>& LoadedAssets)
			{
				OnLoad.ExecuteIfBound(LoadedAssets.IsEmpty() ? nullptr : LoadedAssets[0]);
			}
			));
	}
	
	template<class Class = UObject>
	static void TAsyncLoadPrimaryAssetList(const TArray<FPrimaryAssetId>& AssetsToLoad, const TArray<FName>& LoadBundles, const TDelegate<void(const TArray<FPrimaryAssetId>&, const TArray<Class*>&)>& OnLoad)
	{
		if (UAssetManager* AssetManager = UAssetManager::GetIfInitialized())
		{
			const FStreamableDelegate OnLoadDelegate = FStreamableDelegate::CreateLambda([AssetsToLoad, OnLoad]()
				{
					TArray<FPrimaryAssetId> LoadedPrimaryAssets;
					TArray<Class*> LoadedAssets;

					const UAssetManager* AssetManager = UAssetManager::GetIfInitialized();
					for (const FPrimaryAssetId& AssetId : AssetsToLoad)
					{
						if (UObject* LoadedAsset = AssetManager->GetPrimaryAssetObject(AssetId))
						{
							LoadedPrimaryAssets.Emplace(AssetId);
							Class* CastedObject = Cast<Class>(LoadedAsset);
							check(CastedObject); // Loaded type does not match class
							LoadedAssets.Emplace(CastedObject);
						}
					}
					
					OnLoad.ExecuteIfBound(LoadedPrimaryAssets, LoadedAssets);
				});
		
			AssetManager->LoadPrimaryAssets(AssetsToLoad, LoadBundles, OnLoadDelegate);
		}
	}
	
	template<class Class = UObject>
	static void TAsyncLoadPrimaryAsset(const FPrimaryAssetId& AssetToLoad, const TArray<FName>& LoadBundles, const TDelegate<void(const FPrimaryAssetId&, Class*)>& OnLoad)
	{
		TAsyncLoadPrimaryAssetList(TArray<FPrimaryAssetId>{ AssetToLoad }, LoadBundles, TDelegate<void(const TArray<FPrimaryAssetId>&, const TArray<Class*>&)>::CreateLambda([OnLoad](const TArray<FPrimaryAssetId>& PrimaryAssetIds, const TArray<Class*>& LoadedAssets)
			{
				const FPrimaryAssetId LoadedPrimaryAssets = PrimaryAssetIds.IsEmpty() ? FPrimaryAssetId() : PrimaryAssetIds[0];
				OnLoad.ExecuteIfBound(LoadedPrimaryAssets, LoadedAssets.IsEmpty() ? nullptr : LoadedAssets[0]);
			}));
	}

	/** Assumes implicit conversion */
	template<typename SourceType, typename TargetType>
	static FORCEINLINE void ConvertArray(const SourceType& Source, TargetType& Target)
	{
		Target.Reset(Source.Num());
		Target.Append(Source);
	}
};
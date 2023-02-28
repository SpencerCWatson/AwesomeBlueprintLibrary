// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "AwesomeBL.generated.h"

/**
 * 
 */
UCLASS()
class AWESOMEBLUEPRINTLIBRARY_API UAwesomeBL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//~~~~	PrimaryAsset Helpers	~~~~
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	DECLARE_DYNAMIC_DELEGATE_TwoParams(FAsyncLoadPrimaryAssetSignature, const FPrimaryAssetId& , PrimaryAssetId, UObject*, LoadedAsset);
	DECLARE_DYNAMIC_DELEGATE_ThreeParams(FAsyncLoadPrimaryAssetWithGameplayTagsSignature, const FPrimaryAssetId& , PrimaryAssetId, UObject*, LoadedAsset, const FGameplayTagContainer& , GameplayTags);
	DECLARE_DYNAMIC_DELEGATE_TwoParams(FAsyncLoadPrimaryAssetListSignature, const TArray<FPrimaryAssetId>& , PrimaryAssetIds, const TArray<UObject*>&, LoadedAssets);
	DECLARE_DYNAMIC_DELEGATE_ThreeParams(FAsyncLoadPrimaryAssetListWithGameplayTagsSignature, const TArray<FPrimaryAssetId>& , PrimaryAssetIds, const TArray<UObject*>&, LoadedAssets, const FGameplayTagContainer&, GameplayTags);

	/** Gets the FAssetData for a primary asset with the specified type/name, will only work for once that have been scanned for already. Returns true if it found a valid data */
	UFUNCTION(BlueprintPure, Category="LoadingHelpers")
	static bool GetPrimaryAssetData(const FPrimaryAssetId& PrimaryAssetId, FAssetData& AssetData);
	
	/**
	 * Loads a PrimaryAsset.
	 * @param AssetToLoad			PrimaryAsset to be loaded.
	 * @param LoadBundles			Bundles to activate with load.
	 * @param OnLoad				Delegate to call when loading has finished.
	 */
	UFUNCTION(BlueprintCallable, Category="LoadingHelpers")
	static void AsyncLoadPrimaryAsset(const FPrimaryAssetId& AssetToLoad, const TArray<FName>& LoadBundles, const FAsyncLoadPrimaryAssetSignature& OnLoad);

	/**
	 * Loads a PrimaryAsset with Gameplay Tags attached.
	 * @param AssetToLoad			PrimaryAsset to be loaded.
	 * @param LoadBundles			Bundles to activate with load.
	 * @param OnLoad				Delegate to call when loading has finished.
	 * @param GameplayTags			Tags available in delegate call. 
	 */
	UFUNCTION(BlueprintCallable, Category="LoadingHelpers")
	static void AsyncLoadPrimaryAssetWithGameplayTags(const FPrimaryAssetId& AssetToLoad, const TArray<FName>& LoadBundles, const FAsyncLoadPrimaryAssetWithGameplayTagsSignature& OnLoad, const FGameplayTagContainer& GameplayTags);

	/**
	 * Loads a list of PrimaryAssets.
	 * @param AssetsToLoad			PrimaryAsset to be loaded.
	 * @param LoadBundles			Bundles to activate with load.
	 * @param OnLoad				Delegate to call when loading has finished.
	 */
	UFUNCTION(BlueprintCallable, Category="LoadingHelpers")
	static void AsyncLoadPrimaryAssetList(const TArray<FPrimaryAssetId>& AssetsToLoad, const TArray<FName>& LoadBundles, const FAsyncLoadPrimaryAssetListSignature& OnLoad);

	/**
	 * Loads a list of PrimaryAssets with GameplayTags attached.
	 * @param AssetsToLoad			PrimaryAsset to be loaded.
	 * @param LoadBundles			Bundles to activate with load.
	 * @param OnLoad				Delegate to call when loading has finished.
	 * @param GameplayTags			Tags available in delegate call. 
	 */
	UFUNCTION(BlueprintCallable, Category="LoadingHelpers")
	static void AsyncLoadPrimaryAssetListWithGameplayTags(const TArray<FPrimaryAssetId>& AssetsToLoad, const TArray<FName>& LoadBundles, const FAsyncLoadPrimaryAssetListWithGameplayTagsSignature& OnLoad, const FGameplayTagContainer& GameplayTags);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~
	//~~~~	Loading Helpers	~~~~
	//~~~~~~~~~~~~~~~~~~~~~~~~~~

	DECLARE_DYNAMIC_DELEGATE_OneParam(FAsyncLoadAssetSignature, UObject*, Asset);
	DECLARE_DYNAMIC_DELEGATE_TwoParams(FAsyncLoadAssetWithNameTagsSignature, UObject*, Asset, const TArray<FName>&, Tags);
	DECLARE_DYNAMIC_DELEGATE_OneParam(FAsyncLoadAssetListSignature, const TArray<UObject*>&, Assets);
	DECLARE_DYNAMIC_DELEGATE_TwoParams(FAsyncLoadAssetListWithNameTagsSignature, const TArray<UObject*>&, Assets, const TArray<FName>&, Tags);

	/**
	 * Async load a SoftObjectPtr with a bindable delegate.
	 * @param AssetToLoad			SoftObjectPtr to be loaded.
	 * @param OnLoadDelegate		Delegate to call when loading has finished.
	 */
	UFUNCTION(BlueprintCallable, Category="LoadingHelpers")
	static void AsyncLoadAsset(TSoftObjectPtr<UObject> AssetToLoad, const FAsyncLoadAssetSignature& OnLoadDelegate);

	/**
	 * Async load a SoftObjectPtr with a bindable delegate and Name tags attached.
	 * @param AssetToLoad			SoftObjectPtr to be loaded.
	 * @param Tags					Tags available in delegate call. 
	 * @param OnLoadDelegate		Delegate to call when loading has finished.
	 */
	UFUNCTION(BlueprintCallable, Category="LoadingHelpers")
	static void AsyncLoadAssetWithNameTags(TSoftObjectPtr<UObject> AssetToLoad, const TArray<FName>& Tags, const FAsyncLoadAssetWithNameTagsSignature& OnLoadDelegate);

	/**
	 * Async load a list of SoftObjectPtrs with a bindable delegate.
	 * @param AssetListToLoad		SoftObjectPtr list to be loaded.
	 * @param OnLoadDelegate		Delegate to call when loading has finished.
	 */
	UFUNCTION(BlueprintCallable, Category="LoadingHelpers")
	static void AsyncLoadAssetList(const TArray<TSoftObjectPtr<UObject>>& AssetListToLoad, const FAsyncLoadAssetListSignature& OnLoadDelegate);

	/**
	 * Async load a list of SoftObjectPtrs with a bindable delegate and Name tags attached.
	 * @param AssetListToLoad		SoftObjectPtr list to be loaded.
	 * @param Tags					Tags available in delegate call. 
	 * @param OnLoadDelegate		Delegate to call when loading has finished.
	 */
	UFUNCTION(BlueprintCallable, Category="LoadingHelpers")
	static void AsyncLoadAssetListWithNameTags(const TArray<TSoftObjectPtr<UObject>>& AssetListToLoad, const TArray<FName>& Tags, const FAsyncLoadAssetListWithNameTagsSignature& OnLoadDelegate);
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~
	//~~~~	Data Helpers	~~~~
	//~~~~~~~~~~~~~~~~~~~~~~~~~~

	/** Make a literal GameplayTag from a Name */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="DataHelpers")
	static FGameplayTag MakeLiteralGameplayTag(FName Tag) { return FGameplayTag::RequestGameplayTag(Tag); }

	/** Turn a Name array to a String array */
	UFUNCTION(BlueprintPure, Category="DataHelpers")
	static void NameArrayToStringArray(const TArray<FName>& NameArray, TArray<FString>& StringArray );

	/** Turn a Name array to a String array by reference */
	UFUNCTION(BlueprintCallable, Category="DataHelpers")
	static void NameArrayToStringArrayRef(const TArray<FName>& NameArray, UPARAM(ref) TArray<FString>& StringArray_Ref ) { NameArrayToStringArray(NameArray, StringArray_Ref); }

	/** Turn a String array into a Name array */
	UFUNCTION(BlueprintPure, Category="DataHelpers")
	static void StringArrayToNameArray(const TArray<FString>& StringArray, TArray<FName>& NameArray );

	/** Turn a String array into a Name array by reference */
	UFUNCTION(BlueprintCallable, Category="DataHelpers")
	static void StringArrayToNameArrayRef(const TArray<FString>& StringArray, UPARAM(ref) TArray<FName>& NameArray_Ref ) { StringArrayToNameArray(StringArray, NameArray_Ref); }

	/** Turns an Int array into a Float array. */
	UFUNCTION(BlueprintPure, Category="DataHelpers")
	static TArray<float> IntArrayToFloatArray(const TArray<int32>& IntArray);

	/**
	 *	Turn a Float array into an Int array.
	 *  This will truncate the values.
	 */
	UFUNCTION(BlueprintPure, Category="DataHelpers")
	static TArray<int32> FloatArrayToIntArray(const TArray<float>& FloatArray);
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//~~~~~ Basics
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	/**
	 *	Quit game without a need for a player controller.
	 *	Useful for shutting down a dedicated server.
	 */
	UFUNCTION(BlueprintCallable, Category="BasicHelpers")
	static void QuitGame();

	/**
	 *	Returns the game instance object.
	 *	Callable from Objects.
	 *	@return						GameInstance
	 */
	UFUNCTION(BlueprintPure, Category="BasicHelpers", meta=(WorldContext="WorldContextObject", CallableWithoutWorldContext))
	static UGameInstance* GetGameInstance(const UObject* WorldContextObject) { return UGameplayStatics::GetGameInstance(WorldContextObject); }

	/**
	 *	Returns the current GameModeBase or Null if it can't be retrieved, such as on the client.
	 *	Callable from Objects.
	 *	@return						GameMode
	 */
	UFUNCTION(BlueprintPure, Category="BasicHelpers", meta=(WorldContext="WorldContextObject", CallableWithoutWorldContext))
	static  AGameModeBase* GetGameMode(const UObject* WorldContextObject) { return UGameplayStatics::GetGameMode(WorldContextObject); }

	/**
	 *	Returns the current GameStateBase or Null if it can't be retrieved.
	 *	Callable from Objects.
	 *	@return						GameState
	 */
	UFUNCTION(BlueprintPure, Category="BasicHelpers", meta=(WorldContext="WorldContextObject", CallableWithoutWorldContext))
	static  AGameStateBase* GetGameState(const UObject* WorldContextObject) { return UGameplayStatics::GetGameState(WorldContextObject);}
	
};


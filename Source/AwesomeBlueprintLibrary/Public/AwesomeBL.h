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

	DECLARE_DYNAMIC_DELEGATE_TwoParams(FAsyncLoadPrimaryAssetSignature, const FPrimaryAssetId& , PrimaryAssetId, UObject*, Asset);
	DECLARE_DYNAMIC_DELEGATE_ThreeParams(FAsyncLoadPrimaryAssetWithGameplayTagsSignature, const FPrimaryAssetId& , PrimaryAssetId, UObject*, Asset, const FGameplayTagContainer& , GameplayTags);
	DECLARE_DYNAMIC_DELEGATE_TwoParams(FAsyncLoadPrimaryAssetsSignature, const TArray<FPrimaryAssetId>& , PrimaryAssetIds, const TArray<UObject*>&, Assets);
	DECLARE_DYNAMIC_DELEGATE_ThreeParams(FAsyncLoadPrimaryAssetsWithGameplayTagsSignature, const TArray<FPrimaryAssetId>& , PrimaryAssetIds, const TArray<UObject*>&, Assets, const FGameplayTagContainer&, GameplayTags);

	/** Gets the FAssetData for a primary asset with the specified type/name, will only work for once that have been scanned for already. Returns true if it found a valid data */
	UFUNCTION(BlueprintPure, Category="LoadingHelpers")
	static bool GetPrimaryAssetData(const FPrimaryAssetId& PrimaryAssetId, FAssetData& AssetData);
	
	/**
	 * Loads a PrimaryAsset.
	 * @param WorldContextObject	Object making the call.
	 * @param AssetToLoad			PrimaryAsset to be loaded.
	 * @param LoadBundles			Bundles to activate with load.
	 * @param OnLoad				Delegate to call when loading has finished.
	 */
	UFUNCTION(BlueprintCallable, Category="LoadingHelpers")
	static void AsyncLoadPrimaryAsset(const FPrimaryAssetId& AssetToLoad, const TArray<FName>& LoadBundles, const FAsyncLoadPrimaryAssetSignature& OnLoad);

	/**
	 * Loads a PrimaryAsset with a list og Gameplay Tags attached.
	 * @param WorldContextObject	Object making the call.
	 * @param AssetToLoad			PrimaryAsset to be loaded.
	 * @param LoadBundles			Bundles to activate with load.
	 * @param OnLoad				Delegate to call when loading has finished.
	 * @param GameplayTags			Tags available in delegate call. 
	 */
	UFUNCTION(BlueprintCallable, Category="LoadingHelpers")
	static void AsyncLoadPrimaryAssetWithGameplayTags(const FPrimaryAssetId& AssetToLoad, const TArray<FName>& LoadBundles, const FAsyncLoadPrimaryAssetWithGameplayTagsSignature& OnLoad, const FGameplayTagContainer& GameplayTags);

	/**
	 * Loads a list of PrimaryAssets.
	 * @param WorldContextObject	Object making the call.
	 * @param AssetsToLoad			PrimaryAsset to be loaded.
	 * @param LoadBundles			Bundles to activate with load.
	 * @param OnLoad				Delegate to call when loading has finished.
	 */
	UFUNCTION(BlueprintCallable, Category="LoadingHelpers")
	static void AsyncLoadPrimaryAssets(const TArray<FPrimaryAssetId>& AssetsToLoad, const TArray<FName>& LoadBundles, const FAsyncLoadPrimaryAssetsSignature& OnLoad);

	/**
	 * Loads a list of PrimaryAssets with GameplayTags attached.
	 * @param WorldContextObject	Object making the call.
	 * @param AssetsToLoad			PrimaryAsset to be loaded.
	 * @param LoadBundles			Bundles to activate with load.
	 * @param OnLoad				Delegate to call when loading has finished.
	 * @param GameplayTags			Tags available in delegate call. 
	 */
	UFUNCTION(BlueprintCallable, Category="LoadingHelpers")
	static void AsyncLoadPrimaryAssetsWithGameplayTags(const TArray<FPrimaryAssetId>& AssetsToLoad, const TArray<FName>& LoadBundles, const FAsyncLoadPrimaryAssetsWithGameplayTagsSignature& OnLoad, const FGameplayTagContainer& GameplayTags);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~
	//~~~~	Loading Helpers	~~~~
	//~~~~~~~~~~~~~~~~~~~~~~~~~~

	DECLARE_DYNAMIC_DELEGATE_OneParam(FAsyncLoadAssetSignature, UObject*, Asset);
	DECLARE_DYNAMIC_DELEGATE_TwoParams(FAsyncLoadAssetWithNameTagsSignature, UObject*, Asset, const TArray<FName>&, Tags);
	DECLARE_DYNAMIC_DELEGATE_OneParam(FAsyncLoadAssetsSignature, const TArray<UObject*>&, Assets);
	DECLARE_DYNAMIC_DELEGATE_TwoParams(FAsyncLoadAssetsWithNameTagsSignature, const TArray<UObject*>&, Assets, const TArray<FName>&, Tags);

	/**
	 * Async load a SoftObjectPtr with a bindable delegate.
	 * @param WorldContextObject Object making  the call.
	 * @param AssetToLoad 
	 * @param OnLoadDelegate 
	 */
	UFUNCTION(BlueprintCallable, Category="LoadingHelpers")
	static void AsyncLoadAsset(TSoftObjectPtr<UObject> AssetToLoad, const FAsyncLoadAssetSignature& OnLoadDelegate);
	
	/** Async load an asset with tags attached to the callback */
	UFUNCTION(BlueprintCallable, Category="LoadingHelpers")
	static void AsyncLoadAssetWithTags(TSoftObjectPtr<UObject> AssetToLoad, const TArray<FName>& Tags, const FAsyncLoadAssetWithNameTagsSignature& OnLoadDelegate);

	/** Async load a list of assets */
	UFUNCTION(BlueprintCallable, Category="LoadingHelpers")
	static void AsyncLoadAssets(const TArray<TSoftObjectPtr<UObject>>& AssetsToLoad, const FAsyncLoadAssetsSignature& OnLoadDelegate);
	
	/** Async load a list of assets with tags attached to the callback */
	UFUNCTION(BlueprintCallable, Category="LoadingHelpers")
	static void AsyncLoadAssetsWithTags(const TArray<TSoftObjectPtr<UObject>>& AssetsToLoad, const TArray<FName>& Tags, const FAsyncLoadAssetsWithNameTagsSignature& OnLoadDelegate);
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~
	//~~~~	Data Helpers	~~~~
	//~~~~~~~~~~~~~~~~~~~~~~~~~~

	/** Makes a literal gameplay tag from a name */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="DataHelpers")
	static FGameplayTag MakeLiteralGameplayTag(FName Tag) { return FGameplayTag::RequestGameplayTag(Tag); }

	/** Turns a name array to a string array */
	UFUNCTION(BlueprintPure, Category="DataHelpers")
	static void NameArrayToStringArray(const TArray<FName>& NameArray, TArray<FString>& StringArray );

	/** Turns a name array to a string array by reference */
	UFUNCTION(BlueprintCallable, Category="DataHelpers")
	static void NameArrayToStringArrayRef(const TArray<FName>& NameArray, UPARAM(ref) TArray<FString>& StringArray_Ref ) { NameArrayToStringArray(NameArray, StringArray_Ref); }

	/** Turn a String array into a Name array */
	UFUNCTION(BlueprintPure, Category="DataHelpers")
	static void StringArrayToNameArray(const TArray<FString>& StringArray, TArray<FName>& NameArray );

	/** Turn a String array into a Name array by reference */
	UFUNCTION(BlueprintCallable, Category="DataHelpers")
	static void StringArrayToNameArrayRef(const TArray<FString>& StringArray, UPARAM(ref) TArray<FName>& NameArray_Ref ) { StringArrayToNameArray(StringArray, NameArray_Ref); }

	/** Turns an int array into a float array. */
	UFUNCTION(BlueprintPure, Category="DataHelpers")
	static TArray<float> IntArrayToFloatArray(const TArray<int32>& IntArray);

	/** Turn a float array into an int array while truncating the values. */
	UFUNCTION(BlueprintPure, Category="DataHelpers")
	static TArray<int32> FloatArrayToIntArray(const TArray<float>& FloatArray);
	
	

	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//~~~~~ Basics
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	/** Quit game without a need for a player controller. Useful for shutting down a dedicated server */
	UFUNCTION(BlueprintCallable, Category="BasicHelpers")
	static void QuitGame();

	/** Returns the game instance object. Callable from UObjects.
	 * @return GameInstance
	 */
	UFUNCTION(BlueprintPure, Category="BasicHelpers", meta=(WorldContext="WorldContextObject", CallableWithoutWorldContext))
	static UGameInstance* GetGameInstance(const UObject* WorldContextObject) { return UGameplayStatics::GetGameInstance(WorldContextObject); }

	/** Returns the current GameModeBase or Null if it can't be retrieved, such as on the client. Callable from UObjects.
	 * @return GameMode
	 */
	UFUNCTION(BlueprintPure, Category="BasicHelpers", meta=(WorldContext="WorldContextObject", CallableWithoutWorldContext))
	static  AGameModeBase* GetGameMode(const UObject* WorldContextObject) { return UGameplayStatics::GetGameMode(WorldContextObject); }

	/** Returns the current GameStateBase or Null if it can't be retrieved. Callable from UObjects.
	 * @return GameState
	 */
	UFUNCTION(BlueprintPure, Category="BasicHelpers", meta=(WorldContext="WorldContextObject", CallableWithoutWorldContext))
	static  AGameStateBase* GetGameState(const UObject* WorldContextObject) { return UGameplayStatics::GetGameState(WorldContextObject);}


	/**
	 *
	 * @brief 
	 * @param NameArray //////////////////////////////////////////////////////////////////////////////////////////////////////////
	 * @return 
	 */
	UFUNCTION(BlueprintPure, Category="DataHelpers")
	static TArray<FString> TestOutput(const TArray<FName>& NameArray)
	{
		TArray<FString> OutArray;
		NameArrayToStringArray(NameArray, OutArray);
		return OutArray;
	}
};


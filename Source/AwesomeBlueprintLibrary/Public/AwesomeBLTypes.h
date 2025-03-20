// Copyright Mortal Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AwesomeBLTypes.generated.h"

/**
 * Wrapper to expose FComponentReference to blueprints with the component picker enabled
 */
USTRUCT(BlueprintType)
struct FComponentReferenceWrapper
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Awesome Blueprint Library|Types", meta=(UseComponentPicker, AllowAnyActor))
	FComponentReference ComponentReference;
	
};

/**
 * Wrapper to expose FSoftComponentReference to blueprints with the component picker enabled
 */
USTRUCT(BlueprintType)
struct FSoftComponentReferenceWrapper
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Awesome Blueprint Library|Types", meta=(UseComponentPicker, AllowAnyActor))
	FSoftComponentReference SoftComponentReference;
	
};

/**
 * 
 */
UCLASS()
class AWESOMEBLUEPRINTLIBRARY_API UAwesomeBLTypes : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="Awesome Blueprint Library|Conversion", meta=(NativeBreakFunc, CompactNodeTitle = "->", BlueprintThreadSafe, BlueprintAutocast))
	static void Conv_ComponentReferenceWrapperToComponentReference(const FComponentReferenceWrapper& Wrapper, FComponentReference& OutComponentReference);

	UFUNCTION(BlueprintPure, Category="Awesome Blueprint Library|Conversion", meta=(NativeBreakFunc, CompactNodeTitle = "->", BlueprintThreadSafe, BlueprintAutocast))
	static void Conv_SoftComponentReferenceWrapperToSoftComponentReference(const FSoftComponentReferenceWrapper& Wrapper, FSoftComponentReference& OutSoftComponentReference);
};

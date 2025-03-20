// Copyright Mortal Games. All Rights Reserved.


#include "AwesomeBLTypes.h"

void UAwesomeBLTypes::Conv_ComponentReferenceWrapperToComponentReference(const FComponentReferenceWrapper& Wrapper,
	FComponentReference& OutComponentReference)
{
	OutComponentReference = Wrapper.ComponentReference;
}

void UAwesomeBLTypes::Conv_SoftComponentReferenceWrapperToSoftComponentReference(const FSoftComponentReferenceWrapper& Wrapper,
	FSoftComponentReference& OutSoftComponentReference)
{
	OutSoftComponentReference = Wrapper.SoftComponentReference;
}

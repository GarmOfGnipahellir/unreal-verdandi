// Fill out your copyright notice in the Description page of Project Settings.


#include "VerdandiTimeline.h"

FString UVerdandiTimeline::GetRootDir() const
{
	return FPaths::GetPath(Target.GetLongPackageName());
}

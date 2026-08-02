#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "OceanPerformanceLibrary.generated.h"

USTRUCT(BlueprintType)
struct FOceanPerformanceStats
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "Performance")
    float FPS = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Performance")
    float FrameTimeMs = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Performance")
    float GameThreadTimeMs = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Performance")
    float RenderThreadTimeMs = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Performance")
    float GPUTimeMs = 0.0f;
    
    UPROPERTY(BlueprintReadOnly, Category = "Performance")
    int32 DrawCalls = 0;

    UPROPERTY(BlueprintReadOnly, Category = "Performance")
    int64 TrianglesDrawn = 0;
};

UCLASS()
class OCEANRESEARCH_API UOceanPerformanceLibrary
    : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(
        BlueprintPure,
        Category = "Ocean Debug|Performance",
        meta = (DisplayName = "Get Ocean Performance Stats")
    )
    static FOceanPerformanceStats GetOceanPerformanceStats();
};
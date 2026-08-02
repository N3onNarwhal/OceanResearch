#include "OceanPerformanceLibrary.h"

#include "HAL/PlatformTime.h"
#include "Misc/App.h"
#include "RenderingThread.h"
#include "RHI.h"
#include "RHIStats.h"

FOceanPerformanceStats
UOceanPerformanceLibrary::GetOceanPerformanceStats()
{
    FOceanPerformanceStats Stats;

    const double DeltaSeconds = FApp::GetDeltaTime();

    if (DeltaSeconds > SMALL_NUMBER)
    {
        Stats.FrameTimeMs =
            static_cast<float>(DeltaSeconds * 1000.0);

        Stats.FPS =
            static_cast<float>(1.0 / DeltaSeconds);
    }

    Stats.GameThreadTimeMs =
        static_cast<float>(
            FPlatformTime::ToMilliseconds64(
                GGameThreadTime
            )
        );

    Stats.RenderThreadTimeMs =
        static_cast<float>(
            FPlatformTime::ToMilliseconds64(
                GRenderThreadTime
            )
        );

    Stats.GPUTimeMs =
        static_cast<float>(
            FPlatformTime::ToMilliseconds64(
                RHIGetGPUFrameCycles()
            )
        );
    
#if RHI_DRAW_CALL_STATS
    Stats.DrawCalls = static_cast<int32>(GNumDrawCallsRHI);
    Stats.TrianglesDrawn = static_cast<int64>(GNumPrimitivesDrawnRHI);
#else
    Stats.DrawCalls = -1;
    Stats.TrianglesDrawn = -1;
#endif

    return Stats;
}
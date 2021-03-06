//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  -------------------------------------------------------------------------
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//  -------------------------------------------------------------------------

#ifndef RAMSES_RENDERERTESTUTILS_H
#define RAMSES_RENDERERTESTUTILS_H

#include "ramses-renderer-api/RendererConfig.h"
#include "ramses-renderer-api/DisplayConfig.h"
#include "RendererAPI/EDeviceTypeId.h"
#include "Utils/Bitmap.h"
#include <chrono>

namespace ramses
{
    class RamsesRenderer;
    class RamsesDisplay;
    class WarpingMeshData;
}

namespace ramses_internal
{
    class String;
}

class RendererTestUtils
{
public:
    static void SaveScreenshotForDisplay(
        ramses::RamsesRenderer& renderer,
        ramses::displayId_t displayId,
        ramses_internal::UInt32 x,
        ramses_internal::UInt32 y,
        ramses_internal::UInt32 width,
        ramses_internal::UInt32 height,
        const ramses_internal::String& screenshotFileName);

    static bool PerformScreenshotTestForDisplay(
        ramses::RamsesRenderer& renderer,
        ramses::displayId_t displayId,
        ramses_internal::UInt32 x,
        ramses_internal::UInt32 y,
        ramses_internal::UInt32 width,
        ramses_internal::UInt32 height,
        const ramses_internal::String& screenshotFileName,
        float maxAveragePercentErrorPerPixel = DefaultMaxAveragePercentPerPixel
    );

    static ramses::displayId_t  CreateDisplayImmediate(ramses::RamsesRenderer& renderer, const ramses::DisplayConfig& displayConfig);
    static void                 DestroyDisplayImmediate(ramses::RamsesRenderer& renderer, ramses::displayId_t displayId);

    // All renderer tests should use this renderer config which adds dummy embedded compositor
    static ramses::RendererConfig CreateTestRendererConfig();
    // All renderer tests should use this display config which makes window visible by default for Wayland
    static ramses::DisplayConfig CreateTestDisplayConfig(uint32_t iviSurfaceIdOffset, bool iviWindowStartVisible = true);
    static void SetWaylandIviLayerID(ramses_internal::UInt32 layerId);
    static void SetWaylandSocketEmbedded(const ramses_internal::String& wse);
    static void SetWaylandSocketEmbeddedFileDescriptor(int fileDescriptor);
    static void SetWaylandSocketEmbeddedGroup(const ramses_internal::String& wsegn);
    static void SetMaxFrameCallbackPollingTime(std::chrono::microseconds time);
    static const ramses::WarpingMeshData& CreateTestWarpingMesh();

    static const float DefaultMaxAveragePercentPerPixel;

private:
    static ramses_internal::Bitmap ReadPixelData(
        ramses::RamsesRenderer& renderer,
        ramses::displayId_t displayId,
        ramses_internal::UInt32 x,
        ramses_internal::UInt32 y,
        ramses_internal::UInt32 width,
        ramses_internal::UInt32 height);

    static bool CompareBitmapToImageInFile(const ramses_internal::Bitmap& actualBitmap,
                                            const ramses_internal::String& expectedScreenshotFileName,
                                            float maxAveragePercentErrorPerPixel);

    static ramses_internal::UInt32 WaylandIviLayerIdForTestDisplayConfig;
    static ramses_internal::String WaylandSocketEmbedded;
    static int WaylandSocketEmbeddedFileDescriptor;
    static ramses_internal::String WaylandSocketEmbeddedGroup;
    static std::chrono::microseconds MaxFrameCallbackPollingTime;
};

#endif

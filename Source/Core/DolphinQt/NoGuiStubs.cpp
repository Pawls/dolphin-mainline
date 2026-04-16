// Stubs for DolphinNoGUI symbols (g_platform, Platform::RequestShutdown)
// that EXI_DeviceSlippi.cpp references directly for headless
// shutdown-after-replays on the batch-playback branch. EXI_DeviceSlippi
// lives in core.lib which is shared by dolphin-emu-nogui (which defines
// these) and Slippi_Dolphin (which does not). Without these stubs the
// Qt GUI fails to link. The Qt GUI shuts down via QApplication, so the
// g_platform instance here is a no-op NullPlatform and is never actually
// driven by the main loop.

#include "DolphinNoGUI/Platform.h"

Platform::~Platform() = default;

bool Platform::Init()
{
  return true;
}

void Platform::SetTitle(const std::string&)
{
}

void Platform::UpdateRunningFlag()
{
}

void Platform::Stop()
{
  m_running.Clear();
}

void Platform::RequestShutdown()
{
  m_shutdown_requested.Set();
}

namespace
{
class NullPlatform final : public Platform
{
public:
  void MainLoop() override {}
  WindowSystemInfo GetWindowSystemInfo() const override { return {}; }
};
}  // namespace

std::unique_ptr<Platform> g_platform = std::make_unique<NullPlatform>();

#ifndef EMULATOR_SRC_GRAPHICS_HOST_GPU_RENDERER_DEBUG_H_
#define EMULATOR_SRC_GRAPHICS_HOST_GPU_RENDERER_DEBUG_H_

#include "graphics/host_gpu/vulkanCommon.h"

#include <array>
#include <cstdint>
#include <string>

namespace Libs::Graphics {

class CommandBuffer;

namespace HW {
class Context;
class UserConfig;
struct RenderTarget;
struct ScanModeControl;
struct ScreenViewport;
} // namespace HW

struct ScissorRect {
	int left   = 0;
	int top    = 0;
	int right  = 0;
	int bottom = 0;
};

struct FrameTraceRecord {
	enum class Kind: uint8_t { IndexedDraw, AutoDraw, DirectDispatch, IndirectDispatch };
	Kind kind = Kind::IndexedDraw;
	uint64_t submit_id = 0;
	uint64_t vertex_hash = 0;
	uint64_t pixel_hash = 0;
	uint32_t work_count[3] = {};
	uint32_t target_count = 0;
	uint32_t texture_count = 0;
	uint32_t buffer_count = 0;
	std::array<uint64_t, 8> target_addresses {};
	std::array<uint32_t, 8> target_formats {};
	std::array<uint32_t, 8> target_slots {};
	std::array<uint32_t, 8> target_widths {};
	std::array<uint32_t, 8> target_heights {};
	std::array<uint64_t, 16> texture_addresses {};
	std::array<uint32_t, 16> texture_formats {};
	std::array<uint32_t, 16> texture_widths {};
	std::array<uint32_t, 16> texture_heights {};
	std::array<uint32_t, 16> texture_depths {};
	std::array<uint32_t, 16> texture_view_formats {};
	std::array<uint32_t, 16> texture_view_types {};
};

void RequestFrameTrace();
void FrameTraceOnGuestFlip();
bool FrameTraceActive();
void FrameTraceAdd(const FrameTraceRecord& record);
bool FrameTraceClaimColorProbe();

uint32_t                 render_target_mask_slot(uint32_t mask, uint32_t slot);
uint32_t                 render_target_first_bound_slot(const CommandBuffer& buffer);
bool                     graphics_debug_dump_enabled();
void                     uc_print(const char* func, const HW::UserConfig& uc);
void                     uc_check(const HW::UserConfig& uc);
std::string              rt_print(const char* func, const HW::RenderTarget& rt);
bool                     RenderIsColorTileModeLinear(Prospero::TileMode tile_mode);
void                     hw_print(const CommandBuffer& buffer);
void                     hw_check(const CommandBuffer& buffer);
void                     LogDrawPhase(const char* draw_name, const char* phase);
ScissorRect calc_final_scissor(const HW::ScreenViewport& vp, const HW::ScanModeControl& smc,
                               vk::Extent2D extent, uint32_t viewport_index);

} // namespace Libs::Graphics

#endif // EMULATOR_SRC_GRAPHICS_HOST_GPU_RENDERER_DEBUG_H_

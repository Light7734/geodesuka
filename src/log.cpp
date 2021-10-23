#include <geodesuka/core/util/log.h>

namespace geodesuka::core::util {



	const char* log::get_er_str(VkResult Res) {
		const char* temp;
		switch (Res) {
		default:
			temp = "Error: Unknown";
			break;
		case VK_SUCCESS:
			temp = "Success";
			break;
		case VK_NOT_READY:
			temp = "Not Ready.";
			break;
		case VK_TIMEOUT:
			temp = "Timeout.";
			break;
		case VK_EVENT_SET:
			temp = "Event Set.";
			break;
		case VK_EVENT_RESET:
			temp = "Event Reset.";
			break;
		case VK_INCOMPLETE:
			temp = "Incomplete.";
			break;
		case VK_ERROR_OUT_OF_HOST_MEMORY:
			temp = "Error: Out of Host Memory.";
			break;
		case VK_ERROR_OUT_OF_DEVICE_MEMORY:
			temp = "Error: Out of Device Memory.";
			break;
		case VK_ERROR_INITIALIZATION_FAILED:
			temp = "Error: Initialization failed.";
			break;
		case VK_ERROR_DEVICE_LOST:
			temp = "Error: Device Lost";
			break;
		case VK_ERROR_MEMORY_MAP_FAILED:
			temp = "Error: Memory Map Failed.";
			break;
		case VK_ERROR_LAYER_NOT_PRESENT:
			temp = "Error: Layer Not Present.";
			break;
		case VK_ERROR_EXTENSION_NOT_PRESENT:
			temp = "Error: Extension not present.";
			break;
		case VK_ERROR_FEATURE_NOT_PRESENT:
			temp = "Error: Feature Not Present.";
			break;
		case VK_ERROR_INCOMPATIBLE_DRIVER:
			temp = "Error: Incompatible Driver.";
			break;
		case VK_ERROR_TOO_MANY_OBJECTS:
			temp = "Error: Too many objects.";
			break;
		case VK_ERROR_FORMAT_NOT_SUPPORTED:
			temp = "Error: Format not supported.";
			break;
		case VK_ERROR_FRAGMENTED_POOL:
			temp = "Error: Fragmented pool.";
			break;
		case VK_ERROR_UNKNOWN:
			temp = "Error: Unknown.";
			break;
		case VK_ERROR_OUT_OF_POOL_MEMORY:
			temp = "Error: Out of pool memory.";
			break;
		case VK_ERROR_INVALID_EXTERNAL_HANDLE:
			temp = "Error: Invalid external handle.";
			break;
		case VK_ERROR_FRAGMENTATION:
			temp = "Error: Fragmentation.";
			break;
		case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
			temp = "Error: Invalid opaque capture address.";
			break;
		case VK_ERROR_SURFACE_LOST_KHR:
			temp = "Error: Surface lost (KHR)";
			break;
		case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
			temp = "Error: Native window in use (KHR)";
			break;
		case VK_SUBOPTIMAL_KHR:
			temp = "Suboptimal (khr)";
			break;
		case VK_ERROR_OUT_OF_DATE_KHR:
			temp = "Error: Out of date (khr)";
			break;
		case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
			temp = "Error: Incompatible display.";
			break;
		case VK_ERROR_VALIDATION_FAILED_EXT:
			temp = "Error: Validation failed (ext).";
			break;
		case VK_ERROR_INVALID_SHADER_NV:
			temp = "Error: Invalid shader (nv)";
			break;
		case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
			temp = "Error: Invalid DRM format modifier plane layout (ext)";
			break;
		case VK_ERROR_NOT_PERMITTED_EXT:
			temp = "Error: Not permitted extension";
			break;
		case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
			temp = "Error: Fullscreen exclusive mode lost.";
			break;
		case VK_THREAD_IDLE_KHR:
			temp = "Thread Idle (khr)";
			break;
		case VK_THREAD_DONE_KHR:
			temp = "Thread Done (khr)";
			break;
		case VK_OPERATION_DEFERRED_KHR:
			temp = "Operation Deferred (khr)";
			break;
		case VK_OPERATION_NOT_DEFERRED_KHR:
			temp = "Operation not deferred (khr)";
			break;
		case VK_PIPELINE_COMPILE_REQUIRED_EXT:
			temp = "Pipeline compile required. (ext)";
			break;
		}
		return temp;
		/*
		VK_ERROR_INVALID_EXTERNAL_HANDLE_KHR = VK_ERROR_INVALID_EXTERNAL_HANDLE,
		VK_ERROR_FRAGMENTATION_EXT = VK_ERROR_FRAGMENTATION,
		VK_ERROR_INVALID_DEVICE_ADDRESS_EXT = VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS,
		VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS_KHR = VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS,
		VK_ERROR_PIPELINE_COMPILE_REQUIRED_EXT = VK_PIPELINE_COMPILE_REQUIRED_EXT,
		VK_RESULT_MAX_ENUM = 0x7FFFFFFF
		*/
	}

}
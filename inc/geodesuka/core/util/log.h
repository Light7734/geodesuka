#pragma once
#ifndef GEODESUKA_CORE_UTIL_LOG_H
#define GEODESUKA_CORE_UTIL_LOG_H

#include <vulkan/vulkan.h>

namespace geodesuka::core::util {

	class log {
	public:

		// Parse error into string.
		static const char* get_er_str(VkResult Res);

	private:

	};

}

#endif // !GEODESUKA_CORE_UTIL_LOG_H

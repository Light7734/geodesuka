#pragma once
#ifndef GEODESUKA_CORE_STAGE_DESKTOP_H
#define GEODESUKA_CORE_STAGE_DESKTOP_H

#include "../gcl.h"

#include "../object/system_window.h"

#include "../stage.h"
#include "canvas.h"

namespace geodesuka::core::stage {

	class desktop : public stage_t {
	public:

		~desktop();

	protected:


		virtual VkSubmitInfo update(double aDeltaTime) override;

		virtual VkSubmitInfo compute() override;


		//virtual batch render() override;

		//system_window::present present();

	private:

		// Graphics Capable Device.
		//gcl::device* Device;
		//object::system_display* Display;

		desktop(engine* aEngine, gcl::device* aDevice, object::system_display* aDisplay);

	};

}
#endif // !GEODESUKA_CORE_STAGE_DESKTOP_H

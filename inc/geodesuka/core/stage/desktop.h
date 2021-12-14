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

		desktop(engine *aEngine, gcl::context* aContext, object::system_display* aDisplay);
		~desktop();

	protected:


		virtual VkSubmitInfo update(double aDeltaTime) override;

		//virtual batch render() override;

		//system_window::present present();

	private:

		object::system_display* Display;

	};

}
#endif // !GEODESUKA_CORE_STAGE_DESKTOP_H

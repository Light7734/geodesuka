#include <geodesuka/engine.h>

/* --------------- Standard C Libraries --------------- */

/* --------------- Standard C++ Libraries --------------- */
#include <vector>
#include <chrono>

/* --------------- Third Party Libraries --------------- */

/* --------------- Internal --------------- */

//#include <geodesuka/core/object.h>
//#include <geodesuka/core/object/window.h>
////#include <geodesuka/core/object/system_display.h>
//#include <geodesuka/core/object/system_window.h>
//#include <geodesuka/core/object/virtual_window.h>
//#include <geodesuka/core/object/camera.h>

/* --------------- Internal Callback Methods (Input Handling) --------------- */

namespace geodesuka {

	/*
	* Initializes the whole engine, and all backend APIs.
	* needed for context creation. Will manage all created objects
	* and loaded assets.
	*/
	engine::engine(int argc, char* argv[]) {
		// This function will initialize the engine as a whole, and
		// all the backend libraries it depends upon such as GLFW.

		this->ExitApp = false;
		this->dt = 0.0;
		this->t = 0.0;
		this->PrimaryDisplay = nullptr;

		glfwInit();

		// Queries for monitors.
		if (glfwGetPrimaryMonitor() != NULL) {
			// Get System displays.
			core::object::system_display* tmpDisplay = new core::object::system_display(glfwGetPrimaryMonitor());
			this->PrimaryDisplay = tmpDisplay;
			this->Display.push_back(tmpDisplay);
			this->Object.push_back(tmpDisplay);
			int lCount;
			GLFWmonitor** lMon = glfwGetMonitors(&lCount);
			for (int i = 0; i < lCount; i++) {
				if (PrimaryDisplay->Handle != lMon[i]) {
					// Excludes already cached primary monitor.
					tmpDisplay = new core::object::system_display(lMon[i]);
					this->Display.push_back(tmpDisplay);
					this->Object.push_back(tmpDisplay);
				}
			}
		}
		else {
			// No primary monitors found!
			this->ExitApp = true;
		}

		//// Will print out display info.
		//for (size_t i = 0; i < Display.size(); i++) {
		//	std::cout << "Display Name:\t\t" << Display[i]->Name << std::endl;
		//	std::cout << "Display Size:\t\t" << Display[i]->Size.x << ", " << Display[i]->Size.y << "\t[m]" << std::endl;
		//	std::cout << "Display Resolution:\t" << Display[i]->Resolution.x << ", " << Display[i]->Resolution.y << "\t[pixels]" << std::endl;
		//	std::cout << "Display Refresh Rate:\t" << Display[i]->Property.RefreshRate << "\t\t[1/s]" << std::endl;
		//	std::cout << std::endl;
		//}
	}

	/*
	* Since the engine manages all created objects, it is the responsibility of the engine.
	* Also must shut down backend API. 
	*/
	engine::~engine() {
		// The destructor will insure that all memory allocating objects are cleared from memory.
		//core::gcl::terminate();
		
		// Clear all active objects, starting from the end.
		for (size_t i = 1; i <= Object.size(); i++) {
			size_t ind = Object.size() - i;
			if (Object[ind] != nullptr) {
				delete Object[ind];
				Object[ind] = nullptr;
				Object.pop_back();
			}
		}

		glfwTerminate();
	}

	int engine::input() {
		// This will conduct system wide input polling and deliver input polls to respective objects in focus.
		glfwPollEvents();

		for (core::math::integer i = 0; i < SystemWindow.size(); i++) {

			// Check if window wants to close.
	

			// Check if system_window has entered new display region.

		}

		return 0;
	}

	int engine::update(core::math::real adt) {
		// This will conduct the time step interval and evaluate input poll from last section.

		for (core::math::integer i = 0; i < Display.size(); i++) {
			Display[i]->update(dt);
		}

		

		for (core::math::integer i = 0; i < Object.size(); i++) {
			Object[i]->update(dt);
		}

		return 0;
	}

	int engine::render() {
		// This will conduct all final draw calls required by the engine internally.

		// Should first submit all obj

		//for (core::math::integer i = 0; i < Object.size(); i++) {
		//	PrimaryDisplay->draw(Object[i]);
		//}

		
		// Will draw to (means update) system_displays.
		for (int i = 0; i < this->SystemWindow.size(); i++) {
			core::object::system_display* ParentDisplay = this->SystemWindow[i]->get_parent_display();
			ParentDisplay->draw(this->SystemWindow[i]);
		}

		return 0;
	}

	core::object::system_display* engine::get_primary_display() {
		return this->PrimaryDisplay;
	}

	std::vector<core::object::system_display*> engine::get_display_list() {
		return this->Display;
	}

	core::object::object* engine::create(core::object::object* aNewObject) {
		// Checks for redundant elements.
		for (core::math::integer i = 0; i < Object.size(); i++) {
			if (Object[i] == aNewObject) return aNewObject;
		}
		// Pushes onto list if not on list.
		Object.push_back(aNewObject);
		return aNewObject;
	}

	core::object::system_window* engine::create(core::object::system_window* aNewWindow) {
		// Checks for redundant elements.
		for (core::math::integer i = 0; i < SystemWindow.size(); i++) {
			if (SystemWindow[i] == aNewWindow) return aNewWindow;
		}
		// Pushes onto list if not on list.
		SystemWindow.push_back(aNewWindow);

		// Checks for redundant elements.
		for (core::math::integer i = 0; i < Object.size(); i++) {
			if (Object[i] == aNewWindow) return aNewWindow;
		}
		// Pushes onto list if not on list.
		Object.push_back(aNewWindow);
		return aNewWindow;
	}

	core::math::integer engine::destroy(core::object::object* aDestroyObject) {
		// Searches for object in list, then erases if it exists.
		for (core::math::integer i = 0; i < Object.size(); i++) {
			if (Object[i] == aDestroyObject) {
				Object.erase(Object.begin() + i);
				return 0;
			}
		}
		return -1;
	}

	double engine::get_time() {
		return glfwGetTime();
	}




}

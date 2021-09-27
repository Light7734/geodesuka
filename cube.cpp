#include <geodesuka/core/object/cube.h>

namespace geodesuka {
	namespace core {
		namespace object {

			using namespace gcl;

			cube::cube(gcl::context* Context) {
				// Compile time vertex data example.
				math::real VertexData[] = {
					-1.0, -1.0, -1.0,  0.0,  0.0,  0.0,	 // 0
					 1.0, -1.0, -1.0,  1.0,  0.0,  0.0,	 // 1
					 1.0,  1.0, -1.0,  0.0,  1.0,  0.0,	 // 2
					-1.0,  1.0, -1.0,  1.0,  1.0,  0.0,	 // 3
					-1.0, -1.0,  1.0,  0.0,  0.0,  1.0,	 // 4
					 1.0, -1.0,  1.0,  1.0,  0.0,  1.0,	 // 5
					 1.0,  1.0,  1.0,  0.0,  1.0,  1.0,	 // 6
					-1.0,  1.0,  1.0,  1.0,  1.0,  1.0	 // 7
				};

				// Compile time index data.
				short IndexData[] = {
					0, 3, 1, // -z
					2, 1, 3, // -z
					2, 6, 1, // +x
					5, 1, 6, // +x
					3, 7, 2, // +y
					6, 2, 7, // +y
					1, 5, 0, // -y
					4, 0, 5, // -y
					0, 4, 3, // -x
					7, 3, 4, // -x
					5, 6, 4, // +z
					7, 4, 6  // +z
				};

				// Specify Vertex Buffer
				type temp(type::id::STRUCT, "");
				temp.push(type::id::REAL3, "Pos");
				temp.push(type::id::REAL3, "Color");
				variable VertexLayout(temp, "VertexBuffer");

				// Create VertexBuffer
				//this->VertexBuffer = Context->create_buffer(buffer::id::ARRAY_BUFFER, 8, VertexLayout, VertexData);

				// Create Index Buffer
				//this->IndexBuffer = Context->create_buffer(buffer::id::INDEX_BUFFER, 3 * 6 * 2, variable(type::id::SINT16, ""), IndexData);
			}

			cube::~cube() {

			}

			math::integer cube::input(const hid::keyboard& aKeyboard) {
				return 0;
			}

			math::integer cube::input(const hid::mouse& aMouse) {
				return 0;
			}

			math::integer cube::update(math::real aDeltaTime) {
				return 0;
			}

			math::integer cube::draw(system_display* aTargetSystemDisplay) {
				return 0;
			}

			math::integer cube::draw(system_window* aTargetSystemWindow) {
				return 0;
			}

			math::integer cube::draw(virtual_window* aTargetVirtualWindow) {
				return 0;
			}

			math::integer cube::draw(camera2d* aTargetCamera2D) {
				return 0;
			}

			math::integer cube::draw(camera3d* aTargetCamera3D) {
				return 0;
			}

		}
	}
}

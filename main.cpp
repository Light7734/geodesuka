#include <iostream>
#include <algorithm>

#include <geodesuka/engine.h>

#include <geodesuka/builtin/object/triangle.h>

/*
* This main file is just used for debugging library.
*/

using namespace geodesuka::core;
using namespace gcl;
using namespace object;

using namespace geodesuka::builtin::object;

/*
* setProcessDPIAwarenessContext()
* dpichagned
* Checks for monitor swaps.
*/

/*
* Currently I am unsure how I wish to queue render calls.
* I want a sorting algorithm to be implemented for sorting
* objects queued to be rendered. The idea is to sort based
* on distance from camera, and by whether or not the object
* has an opaque component.
*/
// Creates a window on every display

/*
TODO:
Add functions.
waitfor(Seconds);
get_time();

Complete system_terminal class.

Finish texture class.

Finish system_window class.

Finish Triangle Example.
*/

void buffer_unit_test(geodesuka::core::gcl::context* Context);
void texture_unit_test(geodesuka::core::gcl::context* Context);

// Updated buffer.h, testing 
int main(int argc, char *argv[]) {
	geodesuka::engine Engine(argc, argv);
	if (!Engine.is_ready()) return -1;

	size_t DeviceCount = 0;
	device** Device = Engine.get_device_list(&DeviceCount);
	context* Context = nullptr;
	context* Context2 = nullptr;
	for (size_t i = 0; i < DeviceCount; i++) {
		if (Device[i]->get_properties().deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
			// Provide required extensions to allow context to create system windows.
			//std::cout << "Transfer Index: " << Device[i]->qfi(device::qfs::PRESENT);
			Context = new context(&Engine, Device[i], system_window::RequiredExtension.size(), (const char**)system_window::RequiredExtension.data());
			Context2 = new context(&Engine, Device[i], system_window::RequiredExtension.size(), (const char**)system_window::RequiredExtension.data());
		}
	}

	//buffer_unit_test(Context);
	texture_unit_test(Context);


	Engine.tsleep(1);

	return 0;
}

void buffer_unit_test(geodesuka::core::gcl::context *Context) {
	// This function tests the integrity of data by passing
	// it to the selected devices memory, and then retrieving it.
	math::real Vertices[] = {
		-1.0, 0.0, 0.5, 0.0, 0.0, 1.0, 0.0, 0.0,
		 0.0, 1.0, 0.5, 0.0, 1.0, 0.0, 1.0, 0.0,
		 1.0, 0.0, 0.5, 1.0, 0.0, 0.0, 0.0, 1.0
	};

	math::real VertexReturn[] = {
		 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
	};

	memset(VertexReturn, 0xAA, 24 * sizeof(float));

	util::variable Variable(util::type::id::STRUCT, "Vertex");
	Variable.Type.push(util::type::id::REAL3, "Position");
	Variable.Type.push(util::type::id::REAL2, "TexCoord");
	Variable.Type.push(util::type::id::REAL3, "Color");

	buffer HostBuffer(
		Context,
		device::memory::HOST_VISIBLE | device::memory::HOST_COHERENT,
		buffer::usage::VERTEX,
		3,
		Variable,
		Vertices
	);

	buffer DeviceBuffer(
		Context,
		device::memory::DEVICE_LOCAL,
		buffer::usage::VERTEX,
		3,
		Variable,
		NULL
	);

	buffer ReturnBuffer(
		Context,
		device::memory::HOST_VISIBLE | device::memory::HOST_COHERENT,
		buffer::usage::VERTEX,
		3,
		Variable,
		NULL
	);

	// Test methods later.
	buffer ConstructorCopy(HostBuffer);
	buffer ConstructorMove(buffer(
		Context,
		device::memory::HOST_VISIBLE | device::memory::HOST_COHERENT,
		buffer::usage::VERTEX,
		3,
		Variable,
		NULL
	));
	buffer AssignmentCopy;
	AssignmentCopy = HostBuffer;
	buffer AssignmentMove;
	AssignmentMove = buffer(
		Context,
		device::memory::HOST_VISIBLE | device::memory::HOST_COHERENT,
		buffer::usage::VERTEX,
		3,
		Variable,
		NULL
	);

	VkSubmitInfo Submission[2];
	VkCommandBuffer CommandBuffer[2];
	VkSemaphoreCreateInfo SemaphoreCreateInfo{};
	VkSemaphore Semaphore;
	VkFenceCreateInfo FenceCreateInfo{};
	VkFence Fence;

	FenceCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	FenceCreateInfo.pNext = NULL;
	FenceCreateInfo.flags = 0;

	SemaphoreCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	SemaphoreCreateInfo.pNext = NULL;
	SemaphoreCreateInfo.flags = 0;

	VkResult Result = VkResult::VK_SUCCESS;

	Result = vkCreateFence(Context->handle(), &FenceCreateInfo, NULL, &Fence);
	Result = vkCreateSemaphore(Context->handle(), &SemaphoreCreateInfo, NULL, &Semaphore);

	CommandBuffer[0] = (DeviceBuffer << HostBuffer);
	CommandBuffer[1] = (ReturnBuffer << DeviceBuffer);

	Submission[0].sType					= VkStructureType::VK_STRUCTURE_TYPE_SUBMIT_INFO;
	Submission[0].pNext					= NULL;
	Submission[0].waitSemaphoreCount	= 0;
	Submission[0].pWaitSemaphores		= NULL;
	Submission[0].pWaitDstStageMask		= 0;
	Submission[0].commandBufferCount	= 1;
	Submission[0].pCommandBuffers		= &CommandBuffer[0];
	Submission[0].signalSemaphoreCount	= 1;
	Submission[0].pSignalSemaphores		= &Semaphore;

	Submission[1].sType					= VkStructureType::VK_STRUCTURE_TYPE_SUBMIT_INFO;
	Submission[1].pNext					= NULL;
	Submission[1].waitSemaphoreCount	= 1;
	Submission[1].pWaitSemaphores		= &Semaphore;
	Submission[1].pWaitDstStageMask		= 0;
	Submission[1].commandBufferCount	= 1;
	Submission[1].pCommandBuffers		= &CommandBuffer[1];
	Submission[1].signalSemaphoreCount	= 0;
	Submission[1].pSignalSemaphores		= NULL;

	Context->submit(device::qfs::TRANSFER, 2, Submission, Fence);
	vkWaitForFences(Context->handle(), 1, &Fence, VK_TRUE, UINT_MAX);
	Context->destroy(context::cmdtype::TRANSFER_OTS, 2, CommandBuffer);
	vkResetFences(Context->handle(), 1, &Fence);

	ReturnBuffer.read(0, 24 * sizeof(math::real), VertexReturn);
	if (memcmp(Vertices, VertexReturn, 24 * sizeof(math::real)) == 0) {
		std::cout << "Data matches" << std::endl;
	}
	else {
		std::cout << "Data doesn't match" << std::endl;
	}

	memset(VertexReturn, 0xAA, 24 * sizeof(math::real));
	CommandBuffer[0] = (DeviceBuffer << ConstructorCopy);
	CommandBuffer[1] = (ReturnBuffer << DeviceBuffer);
	Context->submit(device::qfs::TRANSFER, 2, Submission, Fence);
	vkWaitForFences(Context->handle(), 1, &Fence, VK_TRUE, UINT_MAX);
	Context->destroy(context::cmdtype::TRANSFER_OTS, 2, CommandBuffer);
	vkResetFences(Context->handle(), 1, &Fence);
	ReturnBuffer.read(0, 24 * sizeof(math::real), VertexReturn);
	if (memcmp(Vertices, VertexReturn, 24 * sizeof(math::real)) == 0) {
		std::cout << "ConstructorCopy Data Integrity Test Status: Success" << std::endl;
	}
	else {
		std::cout << "ConstructorCopy Data Integrity Test Status: Failure" << std::endl;
	}

	memset(VertexReturn, 0xAA, 24 * sizeof(math::real));
	ConstructorMove.write(0, 24 * sizeof(math::real), Vertices);
	CommandBuffer[0] = (DeviceBuffer << ConstructorMove);
	CommandBuffer[1] = (ReturnBuffer << DeviceBuffer);
	Context->submit(device::qfs::TRANSFER, 2, Submission, Fence);
	vkWaitForFences(Context->handle(), 1, &Fence, VK_TRUE, UINT_MAX);
	Context->destroy(context::cmdtype::TRANSFER_OTS, 2, CommandBuffer);
	vkResetFences(Context->handle(), 1, &Fence);
	ReturnBuffer.read(0, 24 * sizeof(math::real), VertexReturn);
	if (memcmp(Vertices, VertexReturn, 24 * sizeof(math::real)) == 0) {
		std::cout << "CopyMove Data Integrity Test Status: Success" << std::endl;
	}
	else {
		std::cout << "CopyMove Data Integrity Test Status: Failure" << std::endl;
	}

	memset(VertexReturn, 0xAA, 24 * sizeof(math::real));
	CommandBuffer[0] = (DeviceBuffer << AssignmentCopy);
	CommandBuffer[1] = (ReturnBuffer << DeviceBuffer);
	Context->submit(device::qfs::TRANSFER, 2, Submission, Fence);
	vkWaitForFences(Context->handle(), 1, &Fence, VK_TRUE, UINT_MAX);
	Context->destroy(context::cmdtype::TRANSFER_OTS, 2, CommandBuffer);
	vkResetFences(Context->handle(), 1, &Fence);
	ReturnBuffer.read(0, 24 * sizeof(math::real), VertexReturn);
	if (memcmp(Vertices, VertexReturn, 24 * sizeof(math::real)) == 0) {
		std::cout << "AssignmentCopy Data Integrity Test Status: Success" << std::endl;
	}
	else {
		std::cout << "AssignmentCopy Data Integrity Test Status: Failure" << std::endl;
	}
}

void texture_unit_test(geodesuka::core::gcl::context *Context) {
	// This function tests the integrity of data by passing
	// it to the selected devices memory, and then retrieving it.
	texture::prop HostProp = texture::prop();

	//HostProp.MipLevelCount		= 1;
	HostProp.ArrayLayerCount		= 1;
	HostProp.SampleCounts			= texture::sample::COUNT_1;
	HostProp.Tiling					= texture::tiling::OPTIMAL;
	HostProp.Usage					= texture::usage::SAMPLED;

	unsigned char PixelData[4 * 4 * 4] = {
		0xAA, 0xBB, 0xCC, 0xDD, 0xAA, 0xBB, 0xCC, 0xDD,0xAA, 0xBB, 0xCC, 0xDD,0xAA, 0xBB, 0xCC, 0xDD,
		0xAA, 0xBB, 0xCC, 0xDD, 0xAA, 0xBB, 0xCC, 0xDD,0xAA, 0xBB, 0xCC, 0xDD,0xAA, 0xBB, 0xCC, 0xDD,
		0xAA, 0xBB, 0xCC, 0xDD, 0xAA, 0xBB, 0xCC, 0xDD,0xAA, 0xBB, 0xCC, 0xDD,0xAA, 0xBB, 0xCC, 0xDD,
		0xAA, 0xBB, 0xCC, 0xDD, 0xAA, 0xBB, 0xCC, 0xDD,0xAA, 0xBB, 0xCC, 0xDD,0xAA, 0xBB, 0xCC, 0xDD
	};

	texture HostTexture(Context, device::memory::DEVICE_LOCAL, HostProp, VkFormat::VK_FORMAT_R8G8B8A8_UINT, 4, 4, 1, (void*)PixelData);


}

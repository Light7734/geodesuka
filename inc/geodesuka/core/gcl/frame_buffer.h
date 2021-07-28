#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include "../gcl/gcl.h"
#include "../math/gmath.h"

#include "context.h"
// Holds no data, only references.

namespace geodesuka {
	namespace core {
		namespace gcl {

			class frame_buffer {
			public:

				// Enums go here

				struct prop {
					int ColorBits[4];
					int DepthBits;
					int StencilBits;
					int AccumColorBits[4];
					int AuxBuffers;
					int Stereo;
					int DoubleBuffer;
					int Transparent;
					int Samples;
					int sRGBCapable;

					// Default Contstructor
					prop();
				};

				// Parent Context
				context* Context;
				struct prop Property;
				// TODO: Maybe change to integer?
				math::integer ID;

				// Constructs Default Framebuffer.
				frame_buffer();

				// Constructs Default Framebuffer with hints
				frame_buffer(const struct prop& aProperty);

				// Constructs FBO with respect to context.
				frame_buffer(context *aContext, const struct prop& aProperty);

				~frame_buffer();

				//int set_output(const variable& Target, const texture& Variable);

			private:
				// TODO: Add back later.
				/*
				math::boolean EnableBlending;
				//boolean EnableColorLogic;
				math::boolean EnableFaceCulling;
				//boolean EnableDepthClamp;
				math::boolean EnableDepthTest;
				math::boolean EnableDithering;
				//boolean EnableFramebufferSRGB;
				//boolean EnableLineSmooth;
				math::boolean EnableMultisample;
				//boolean EnablePolygonSmooth;
				math::boolean EnableScissorTest;
				math::boolean EnableStencilTest;

				// Face Culling Options
				gl_enum FrontFaceSelect;
				gl_enum CullFaceSelect;

				// Scissor Options
				math::integer ScissorPositionX, ScissorPositionY;
				GLsizei ScissorSizeX, ScissorSizeY;

				// Multisample Options
				math::real MultisampleValue;
				math::boolean MultisampleInversion;

				// Depth Test Options
				gl_enum DepthOperation;
				math::boolean DepthFlag;
				GLclampd DepthNear, DepthFar;

				// Stencil Test Options
				gl_enum StencilOperation;
				math::integer StencilReferenceValue;
				math::natural StencilMask;
				gl_enum StencilTestFailureAction, DepthTestFailureAction, StencilAndDepthPassAction;

				// Blending Options
				math::real BlendRed, BlendGreen, BlendBlue, BlendAlpha;
				gl_enum BlendingSourceMultiplier, BlendingDestinationMultiplier, BlendingOperation;

				// Refresh Frame buffer
				math::integer FramePositionX, FramePositionY;
				GLsizei FrameSizeX, FrameSizeY;

				GLbitfield ClearOptions;
				math::real FrameClearRed, FrameClearGreen, FrameClearBlue, FrameClearAlpha;
				GLclampd FrameClearDepth;
				math::integer FrameClearStencil;

				//*/

			};

		}
	}
}

#endif // !FRAME_BUFFER_H
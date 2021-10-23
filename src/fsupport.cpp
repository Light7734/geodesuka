#include <geodesuka/core/math/util/fsupport.h>

#include <cmath>

/* This header configures usage. */
#include <geodesuka/core/math/config.h>

/* Internal Utility Functions */
#include <geodesuka/core/math/util/isupport.h>

/* -------------------- All Types Included here -------------------- */

/* Number Types */
#include <geodesuka/core/math/numbers/natural.h>
#include <geodesuka/core/math/numbers/integer.h>
#include <geodesuka/core/math/numbers/real.h>
#include <geodesuka/core/math/numbers/complex.h>
#include <geodesuka/core/math/numbers/quaternion.h>

/* Built In Numerical Constants */
#include <geodesuka/core/math/numbers/constants.h>

/* Vector Types */
#include <geodesuka/core/math/vectors/natural2.h>
#include <geodesuka/core/math/vectors/natural3.h>
#include <geodesuka/core/math/vectors/natural4.h>

#include <geodesuka/core/math/vectors/integer2.h>
#include <geodesuka/core/math/vectors/integer3.h>
#include <geodesuka/core/math/vectors/integer4.h>

#include <geodesuka/core/math/vectors/real2.h>
#include <geodesuka/core/math/vectors/real3.h>
#include <geodesuka/core/math/vectors/real4.h>

/* Matrix Types */
/*
* When accessing matrix elements, the notation is
* math::realmxn A;
*
* Value = A(Row,Column);
*/
#include <geodesuka/core/math/matrices/real2x2.h>
#include <geodesuka/core/math/matrices/real2x3.h>
#include <geodesuka/core/math/matrices/real2x4.h>
#include <geodesuka/core/math/matrices/real3x2.h>
#include <geodesuka/core/math/matrices/real3x3.h>
#include <geodesuka/core/math/matrices/real3x4.h>
#include <geodesuka/core/math/matrices/real4x2.h>
#include <geodesuka/core/math/matrices/real4x3.h>
#include <geodesuka/core/math/matrices/real4x4.h>

/* Inter-Matrix Multiplication */
#include <geodesuka/core/math/util/matrix_multiply.h>

//#include "R1.h"
//#include "R2.h"
//#include "R3.h"
//#include "R4.h"

//#include "real2_field.h"
//#include "real3_field.h"
//#include "real4_field.h"

namespace geodesuka {
	namespace core {
		namespace math {

			real4x4 perspective(real FOV, real AspectRatio, real Near, real Far) {
				//tex:
				// Aspect Ratio: $$a$$
				// Field of View (Radians): $$\theta$$
				// Near Point: $$n$$
				// Far Point: $$f$$
				// $$ x_{n} = \frac{1}{\tan{\frac{\theta}{2}}} \frac{x_{e}}{z_{e}}$$
				// $$ y_{n} = \frac{a}{\tan{\frac{\theta}{2}}} \frac{y_{e}}{z_{e}}$$
				// $$ z_{n} = \frac{1}{z_{e}} \bigg(-\frac{f+n}{f-n} z_{e} + \frac{2fn}{f-n} \bigg)$$ 
				// The $z$ term is why the perspective matrix must be a real4x4 type 
				// and not just a real3x3. The set of equations above describe
				// the transform from what the perspective of the camera
				// to the screen space of the context.
				// 
				// The matrix then takes the form of 
				// $$ P =
				// \begin{bmatrix}
				// \frac{1}{\tan{\frac{\theta}{2}}} & 0 & 0 & 0 \\
				// 0 & \frac{a}{\tan{\frac{\theta}{2}}} & 0 & 0 \\
				// 0 & 0 & - \frac{f + n}{f - n} & \frac{2fn}{f - n} \\
				// 0 & 0 & 1 & 0 \\
				// \end{bmatrix}
				// $$

				real tn = std::tan(FOV / 2.0);
				return real4x4(
					(1.0 / tn), 0.0, 0.0, 0.0,
					0.0, (AspectRatio / tn), 0.0, 0.0,
					0.0, 0.0, (-((Far + Near) / (Far - Near))), ((2.0 * Far * Near) / ((double)Far - (double)Near)),
					0.0, 0.0, 1.0, 0.0
				);
			}

			// This function generates a rotation matrix using a quaternions.
			real4x4 rotation(real Angle, real3 V) {
				//tex:
				// In quaternion notation, a rotation is of the form
				// $$ \vec{r}^{'} = q\vec{r}q^{-1} $$
				// Where 
				// $ q = e^{\phi} $
				// and $\phi$ is
				// $$ \phi = \frac{\theta}{2} \hat{u} $$
				// $\theta$ is the angle of rotation, and $\hat{u}$ is the vector
				// which the object is rotated around.
				// $$ s = \frac{1}{|q|^{2}} $$
				// The matrix below is to be used in the following way $\vec{r}^{'} = R \vec{r}$
				// and is equivalent to $ \vec{r}^{'} = q \vec{r} q^{-1} $.
				// $$ R = 
				// \begin{bmatrix}
				// 1 - s(c^{2} + d^{2}) & 2s(bc - da) & 2s(bd + ca) \\ 
				// 2s(bc + da) & 1 - 2s(b^{2} + d^{2}) & 2s(cd - ba) \\
				// 2s(bd - ca) & 2s(cd + ba) & 1 - 2s(b^{2} + c^{2})
				// \end{bmatrix}    
				// $$
				// Citation: http://www.faqs.org/faqs/graphics/algorithms-faq/

				// Normalizes the vector.
				real3 v = normalize(V);
				// Generates the rotator quaternion.
				quaternion q = exp((Angle / 2.0) * quaternion(0.0, v.x, v.y, v.z));
				double s = 1.0 / abs2(q);
				return real4x4(
					1.0 - 2.0 * s * (q.c * q.c + q.d * q.d), 2.0 * s * (q.b * q.c - q.d * q.a), 2.0 * s * (q.b * q.d + q.c * q.a), 0.0,
					2.0 * s * (q.b * q.c + q.d * q.a), 1.0 - 2.0 * s * (q.b * q.b + q.d * q.d), 2.0 * s * (q.c * q.d - q.b * q.a), 0.0,
					2.0 * s * (q.b * q.d - q.c * q.a), 2.0 * s * (q.c * q.d + q.b * q.a), 1.0 - 2.0 * s * (q.b * q.b + q.c * q.c), 0.0,
					0.0, 0.0, 0.0, 1.0
				);
			}

		}
	}
}

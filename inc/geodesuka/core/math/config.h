#pragma once
#ifndef MCONFIG_H
#define MCONFIG_H

/* Enable Common CS Math Notation */
//#define CS_PLEB_NOTATION

/* type 'real' precision */
//#define REAL_TYPE_HALF
#define REAL_TYPE_FLOAT
//#define REAL_TYPE_DOUBLE

/* Matrix Memory Layout */
//tex:
// Row Major Memory Format:
// $$ 
// \begin{bmatrix} 
//	m[0] & m[1] & m[2] \\
//  m[3] & m[4] & m[5] \\
//  m[6] & m[7] & m[8] \\
// \end{bmatrix}
// $$
// Access: A = i*M + j

//#define ROW_MAJOR_MEMORY_LAYOUT

//tex:
// Column Major Memory Format:
// $$ 
// \begin{bmatrix} 
//	m[0] & m[3] & m[6] \\
//  m[1] & m[4] & m[7] \\
//  m[2] & m[5] & m[8] \\
// \end{bmatrix}
// $$
// Access: A = i + j*N

#define COL_MAJOR_MEMORY_LAYOUT

//real A[3][2] = { {0,1}, {2,3}, {4,5} };
//real A[2][3] = { {0,1,2}, {3,4,5} };

/* Enable Output Debugging */
#define MATH_ENABLE_IO

#endif // !MCONFIG_H

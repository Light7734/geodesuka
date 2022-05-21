#pragma once
#ifndef GEODESUKA_CORE_UTIL_VARIABLE_H
#define GEODESUKA_CORE_UTIL_VARIABLE_H

/* --------------- Written By ShaderKitty 08/11/2019 --------------- */

/*
The purpose of this object is to manage memory layouts of buffer objects.


*/

/*
*/
/*
// --------------- Structure Form --------------- //

variable_descriptor DemoDesc;

struct {					//
	struct {				//
		vec3 Position;		//			O
		vec3 Momentum;		//			O
		vec3 Force;			//			O
		float Mass;			//			O
	} Particle;				//		O
	struct {				//
		vec3 Position;		//			O
		vec4 Color[3];		//			O
	} Light;				//		O
	mat4 Transform;			//		O
	vec3 Position;			//		O
	float Scale;			//		O
} Glow;						//	O


// --------------- Leaflet Form --------------- //
Glow.Particle.Position;	  // O
Glow.Particle.Momentum;	  // O
Glow.Particle.Force;	  // O
Glow.Particle.Mass;		  // O
Glow.Light.Position;	  // O
Glow.Light.Color[0];	  // O
Glow.Light.Color[1];	  // O
Glow.Light.Color[2];	  // O
Glow.Transform;			  // O
Glow.Position;			  // O
Glow.Scale;				  // O

// --------------- Usage --------------- //

// ivec2 Resolution;
descriptor SingleVariable(GCL_INT_VEC2, "Resolution"); // Childless

//struct particle {
//	vec3 Position;
//	vec3 Momentum;
//	vec3 Force;
//	float Mass;
//};
variable_descriptor P(GCL_STRUCT, "particle");		// Can set to "", or NULL for typeless structs
P.push(GCL_FLOAT_VEC3, "Position");
P.push(GCL_FLOAT_VEC3, "Momentum");
P.push(GCL_FLOAT_VEC3, "Force");
P.push(GCL_FLOAT, "Mass");

//struct light {
//	vec3 Position;
//	vec4 Color[3];
//};
variable_descriptor L(GCL_STRUCT, "light");
L.push(GCL_FLOAT_VEC3, "Position");
L.push(GCL_FLOAT_VEC4, "Color", 3);

//struct glow {
//	struct particle {
//		vec3 Position;
//		vec3 Momentum;
//		vec3 Force;
//		float Mass;
//	} Particle;
//	struct light {
//		vec3 Position;
//		vec4 Color[3];
//	} Light;
//	mat4 Transform;
//	vec3 Position;
//	float Scale;
//} Glow;
variable_descriptor G(variable_descriptor(GCL_STRUCT, "glow"), "Glow", 0, NULL);
G.push(P, "Particle");
G.push(L, "Light");


G			Glow
G[0]		Glow.Particle
G[0][2]		Glow.Particle.Force
G[1][1]		Glow.Light.Color
G[1][1][2]	Glow.Light.Color[2]

*/

/*


Describe Read/Write Values


buffer Buffer(GL_BUFFER_ARRAY, "glow");


*/

/*
Any node that is a part of a hierarchal tree cannot be hollow.

EMPTY
HARD
HOLLOW

B1 = B2;
!Hollow = !Hollow -> Hard Copy
!Hollow = Hollow -> Hard Copy to Non Hollow Location
Hollow = !Hollow -> Make Hollow Copy of right side
Hollow = Hollow -> Hollow Copy

*/

/*
struct_specifier:
		STRUCT IDENTIFIER LEFT_BRACE struct_declaration_list RIGHT_BRACE
		STRUCT LEFT_BRACE struct_declaration_list RIGHT_BRACE

struct_declaration_list:
		struct_declaration
		struct_declaration_list struct_declaration

struct_declaration:
		type_specifier struct_declarator_list SEMICOLON
		type_qualifier type_specifier struct_declarator_list SEMICOLON

struct_declarator_list:
		struct_declarator
		struct_declarator_list COMMA struct_declarator

struct_declarator:
		IDENTIFIER
		IDENTIFIER LEFT_BRACKET RIGHT_BRACKET
		IDENTIFIER LEFT_BRACKET constant_expression RIGHT_BRACKET
*/

//TODO: Add in support for sampler types, this is for the texture class.
//TODO: Add Location variable for shader_program.
//TODO: If possible, make support for hollow copies.

//#define MODE_DEBUG

#include <cstddef>
#include <cstdarg>

#ifdef MODE_DEBUG
#include <iostream>
#include <string>
#include <vector>
#endif // MODE_DEBUG

#include "../math.h"
//GEODESUKA_CORE_UTIL_VARIABLE_H
namespace geodesuka::core::util {

	class variable;

	class type {
	public:

		// Access to "type" private functions.
		friend class variable;

		enum class id {
			UNKNOWN = -1,
			// Composite Structure Type
			STRUCT,
			// Number Types
			UCHAR,
			USHORT,
			UINT,
			CHAR,
			SHORT,
			INT,
			//HALF,
			FLOAT,
			DOUBLE,
			// Vector Types
			UCHAR2,
			UCHAR3,
			UCHAR4,
			USHORT2,
			USHORT3,
			USHORT4,
			UINT2,
			UINT3,
			UINT4,
			CHAR2,
			CHAR3,
			CHAR4,
			SHORT2,
			SHORT3,
			SHORT4,
			INT2,
			INT3,
			INT4,
			//HALF2,
			//HALF3,
			//HALF4,
			FLOAT2,
			FLOAT3,
			FLOAT4,
			// Matrix Types
			FLOAT2X2,
			FLOAT2X3,
			FLOAT2X4,
			FLOAT3X2,
			FLOAT3X3,
			FLOAT3X4,
			FLOAT4X2,
			FLOAT4X3,
			FLOAT4X4
		};

		variable* Master;			// If this is in the possesion of master variable, not nullptr.
		id ID;						// Type ID enum of variable type. Base or Composite (i.e. struct)	
		size_t Size;				// Size of the the type.
		int MemberCount;			// Number of member variables if composite type.
		variable* Member;			// Array of member variables of composite type.
		char* Name;					// String name of type, can be set if composite type (i.e. struct)

		// default constructor.
		type();

		// Constructor for composite types.
		type(id TypeSpecifier, const char* TypeName);

		// Constructor for base types.
		type(id TypeSpecifier);

		// Copy Constructor: deep copies type.
		type(const type& Arg);

		// Move Constructor: swaps the type. (Pointer swap)
		type(type&& Arg) noexcept;

		// Destructor: Clears all memory allocated for the object.
		~type();

		// Can be used to overwrite type with simple enum id.
		type& operator=(id Rhs);

		// Copy Assignment: Will deep copy right hand side into left hand side.
		type& operator=(const type& Rhs);

		// Move Assignment: Will swap left and right contents.
		type& operator=(type&& Rhs) noexcept;

		// ---------- Member Variable Modifier ---------- //
		// Options: push, pop, insert, remove, exchange, reverse, permute.
		// Recalculate Memory Layout if push, pop, insert, remove is called.

		// Multi Variable Modifiers
		int push(int VariableCount, const variable* Variable);
		int pop(int VariableCount);
		int insert(int Index, int VariableCount, const variable* Variable);
		int remove(int Index, int VariableCount);
		//int exchange(int I, int J, int VariableCount);

		// Single Variable Modifiers
		int push(type::id TypeSpecifier, const char* IdentifierString);
		int push(type::id TypeSpecifier, const char* IdentifierString, int SubscriptSize);
		int push(type::id TypeSpecifier, const char* IdentifierString, int SubscriptCount, int* SubscriptSize);
		int push(const type& TypeSpecifier, const char* IdentifierString);
		int push(const type& TypeSpecifier, const char* IdentifierString, int SubscriptSize);
		int push(const type& TypeSpecifier, const char* IdentifierString, int SubscriptCount, int* SubscriptSize);
		int push(const variable& Variable);
		int pop();
		int insert(int Index, type::id TypeSpecifier, const char* IdentifierString);
		int insert(int Index, type::id TypeSpecifier, const char* IdentifierString, int SubscriptSize);
		int insert(int Index, type::id TypeSpecifier, const char* IdentifierString, int SubscriptCount, int* SubscriptSize);
		int insert(int Index, const type& TypeSpecifier, const char* IdentifierString);
		int insert(int Index, const type& TypeSpecifier, const char* IdentifierString, int SubscriptSize);
		int insert(int Index, const type& TypeSpecifier, const char* IdentifierString, int SubscriptCount, int* SubscriptSize);
		int insert(int Index, const variable& Variable);
		int remove(int Index);
		//int exchange(int I, int J);

		//int reverse(int Index, int VariableCount);
		//int permute(int Index, int VariableCount, int PermuteCount);

		// ---------- Util ---------- //

		// Set name of type (kind of redundant if required at creation).
		int set_name(const char* TypeName);
		const char* get_name() const;

#ifdef MODE_DEBUG
		std::string get_str();
#endif // MODE_DEBUG

	private:

		static size_t size_of(id TypeSpecifier);
		static size_t size_of(const type& TypeSpecifier);

		static id string_to_token(const char* TypeSpecifier);
		static const char* token_to_string(id TypeSpecifier);
		static id basic_type_id_of(id TypeSpecifier);

		static math::integer element_count_of(id TypeSpecifier);
		static math::integer row_count_of(id TypeSpecifier);
		static math::integer col_count_of(id TypeSpecifier);

		//private:

			// Do not use these unless you know what you are doing. Make private in future.
		int create(id TypeSpecifier);
		int create(id TypeSpecifier, const char* TypeName);
		int annihilate();
		type clone() const;
		int copy(const type& TypeSpecifier);
		int swap(type& TypeSpecifier);

	};

	class variable {
	public:

		// Access to "type" private functions.
		friend class type;

		// Root must be equal to nullptr if actually root.
		variable* Root;				// Reference to the root of the tree.
		variable* Parent;			// Reference to the imediate parent of the tree.
		size_t Offset;				// If child variable, will store offset with respect to *Root.
		size_t Size;				// The full size of the variable.
		type Type;					// The type of the variable, can be composite (like a struct).
		char* Name;					// The identifier of the instance.
		int DimensionCount;			// Number of dimensions, if Dimension = NULL, then 1D array count.
		int* Dimension;				// If multidimensional array, will not be NULL.

		// -------------------- Constructors (Usage) -------------------- //

		// Default constructor (obviously).
		variable();

		/*
		* -------------------- Arguments to Construct With --------------------
		* aContext: Set nullptr if not to be used to create device memory buffer.
		* aVertextCount: Set to 0 if not to be used to allocate memory on either host or device memory.
		* aTypeSpecifier: Either use enum type, or type object to specify the type of the buffer.
		* aIdentifierString: Will be the name of the buffer/variable
		* aSubscriptCount: If an array of subscript sizes is passed, this is the length of that array.
		* aSubscriptSize: Either pass array or single value to specify the size of the array for the buffer/variable.
		*/

		// Constructor group using enums instead of type objects. (Do not use if type already constructed.
		variable(type::id TypeSpecifier, const char* IdentifierString);
		variable(type::id TypeSpecifier, const char* IdentifierString, int SubscriptSize);
		variable(type::id TypeSpecifier, const char* IdentifierString, int SubscriptCount, int* SubscriptSize);

		// Constructor group using type objects. Should 
		variable(const type& TypeSpecifier, const char* IdentifierString);
		variable(const type& TypeSpecifier, const char* IdentifierString, int SubscriptSize);
		variable(const type& TypeSpecifier, const char* IdentifierString, int SubscriptCount, int* SubscriptSize);

		// Copy Constructor: makes hard copies of the argument.
		variable(const variable& Arg);

		// Move Constructor: swap contents or what ever.
		variable(variable&& Arg) noexcept;

		~variable();

		variable& operator=(const variable& Rhs);
		variable& operator=(variable&& Rhs) noexcept;

		variable& operator[](int Index);
		const variable& operator[](int Index) const;

		// ---------- Util ---------- //

		int set_type(const type& VariableType);
		type get_type() const;

		int set_name(const char* VariableName);
		const char* get_name() const;

		int set_array_size(int SubscriptCount, int* SubscriptSize);
		//const int* get_array_size(const int* SubscriptCount) const;

#ifdef MODE_DEBUG
		std::string get_str();
#endif // MODE_DEBUG

		static size_t size_of(const variable& Arg);

	private:

		// Do not use these unless you know what you are doing. Make private in future.
		int create(type::id TypeSpecifier, const char* TypeName, const char* IdentifierString, int SubscriptCount, int* SubscriptSize);
		int create(const type& TypeSpecifier, const char* IdentifierString, int SubscriptCount, int* SubscriptSize);
		int clear();
		int set_root(variable* VarRoot);
		variable clone() const;
		int copy(const variable& Var);
		int swap(variable& Var);
		//int calculate_memory_layout();

	};

#ifdef MODE_DEBUG
	void unit_test_variable();
#endif // MODE_DEBUG

}

#endif // !GEODESUKA_CORE_UTIL_VARIABLE_H

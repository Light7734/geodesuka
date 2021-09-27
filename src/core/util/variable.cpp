#include <geodesuka/core/util/variable.h>

#include <stdio.h>

#ifdef MODE_DEBUG
#include <iostream>
#include <string>
#include <vector>
#endif // MODE_DEBUG

#include <geodesuka/core/math.h>

#define BUILT_IN_TYPE_LIST_SIZE 28

namespace geodesuka {
	namespace core {
		namespace gcl {

			// TODO: Maybe move this to a gconfig.h file so it can be shared with other objects?
			static struct {
				type::id TypeID;
				const char* TypeName;
				type::id DataTypeID;
				math::integer ElementCount;
				math::integer Rows;
				math::integer Columns;
				size_t Size;
			} BuiltInType[BUILT_IN_TYPE_LIST_SIZE] = {
				{	type::id::STRUCT		,		"struct"		,	type::id::STRUCT			,		0		  ,		0		,		0		,	0							},
				{	type::id::UINT8			,		"ubyte"			,	type::id::UINT8				,		1		  ,		1		,		1		,	sizeof(unsigned char)		},
				{	type::id::UINT16		,		"ushort"		,	type::id::UINT16			,		1		  ,		1		,		1		,	sizeof(unsigned short)		},
				{	type::id::UINT32		,		"uint"			,	type::id::UINT32			,		1		  ,		1		,		1		,	sizeof(math::natural)				},
				{	type::id::SINT8			,		"byte"			,	type::id::SINT8				,		1		  ,		1		,		1		,	sizeof(signed char)			},
				{	type::id::SINT16		,		"short"			,	type::id::SINT16			,		1		  ,		1		,		1		,	sizeof(signed short)		},
				{	type::id::SINT32		,		"int"			,	type::id::SINT32			,		1		  ,		1		,		1		,	sizeof(math::integer)				},
				{	type::id::FLOAT16		,		"half"			,	type::id::FLOAT16			,		1		  ,		1		,		1		,	sizeof(unsigned short)		},
				{	type::id::FLOAT32		,		"float"			,	type::id::FLOAT32			,		1		  ,		1		,		1		,	sizeof(math::real)				},
				{	type::id::FLOAT64		,		"double"		,	type::id::FLOAT64			,		1		  ,		1		,		1		,	sizeof(double)				},
				{	type::id::NATURAL2		,		"uvec2"			,	type::id::UINT32			,		2		  ,		2		,		1		,	sizeof(math::natural2)			},
				{	type::id::NATURAL3		,		"uvec3"			,	type::id::UINT32			,		3		  ,		3		,		1		,	sizeof(math::natural3)			},
				{	type::id::NATURAL4		,		"uvec4"			,	type::id::UINT32			,		4		  ,		4		,		1		,	sizeof(math::natural4)			},
				{	type::id::INTEGER2		,		"ivec2"			,	type::id::SINT32			,		2		  ,		2		,		1		,	sizeof(math::integer2)			},
				{	type::id::INTEGER3		,		"ivec3"			,	type::id::SINT32			,		3		  ,		3		,		1		,	sizeof(math::integer3)			},
				{	type::id::INTEGER4		,		"ivec4"			,	type::id::SINT32			,		4		  ,		4		,		1		,	sizeof(math::integer4)			},
				{	type::id::REAL2			,		"vec2"			,	type::id::FLOAT32			,		2		  ,		2		,		1		,	sizeof(math::real2)				},
				{	type::id::REAL3			,		"vec3"			,	type::id::FLOAT32			,		3		  ,		3		,		1		,	sizeof(math::real3)				},
				{	type::id::REAL4			,		"vec4"			,	type::id::FLOAT32			,		4		  ,		4		,		1		,	sizeof(math::real4)				},
				{	type::id::REAL2X2		,		"mat2"			,	type::id::FLOAT32			,		4		  ,		2		,		2		,	sizeof(math::real2x2)				},
				{	type::id::REAL2X3		,		"mat2x3"		,	type::id::FLOAT32			,		6		  ,		3		,		2		,	sizeof(math::real2x3)				},
				{	type::id::REAL2X4		,		"mat2x4"		,	type::id::FLOAT32			,		8		  ,		4		,		2		,	sizeof(math::real2x4)				},
				{	type::id::REAL3X2		,		"mat3x2"		,	type::id::FLOAT32			,		6		  ,		2		,		3		,	sizeof(math::real3x2)				},
				{	type::id::REAL3X3		,		"mat3"			,	type::id::FLOAT32			,		9		  ,		3		,		3		,	sizeof(math::real3x3)				},
				{	type::id::REAL3X4		,		"mat3x4"		,	type::id::FLOAT32			,		12		  ,		4		,		3		,	sizeof(math::real3x4)				},
				{	type::id::REAL4X2		,		"mat4x2"		,	type::id::FLOAT32			,		8		  ,		2		,		4		,	sizeof(math::real4x2)				},
				{	type::id::REAL4X3		,		"mat4x3"		,	type::id::FLOAT32			,		12		  ,		3		,		4		,	sizeof(math::real4x3)				},
				{	type::id::REAL4X4		,		"mat4"			,	type::id::FLOAT32			,		16		  ,		4		,		4		,	sizeof(math::real4x4)				}
			};

			type::type() {
				this->Master = nullptr;
				this->ID = id::UNKNOWN;
				this->Size = 0;
				this->MemberCount = 0;
				this->Member = nullptr;
				this->Name = NULL;
			}

			type::type(id TypeSpecifier, const char* TypeName) {
				this->Master = nullptr;
				const char* Str = type::token_to_string(TypeSpecifier);
				if (Str != NULL) {
					this->ID = TypeSpecifier;
				}
				else {
					this->ID = id::UNKNOWN;
				}
				if ((this->ID != id::UNKNOWN) && (this->ID != id::STRUCT)) {
					this->Size = type::size_of(this->ID);
				}
				else {
					this->Size = 0;
				}
				this->MemberCount = 0;
				this->Member = nullptr;
				this->Name = NULL;
				size_t StrLen = 0;
				if (this->ID == id::STRUCT) {
					// Use TypeName
					if (TypeName != NULL) {
						StrLen = strlen(TypeName);
						this->Name = (char*)malloc((StrLen + 1) * sizeof(char));
						if (this->Name != NULL) {
							memcpy(this->Name, TypeName, StrLen * sizeof(char));
							this->Name[StrLen] = '\0';
						}
					}
				}
				else {
					// Builtin Variable, ignore TypeName
					if (Str != NULL) {
						StrLen = strlen(Str);
						this->Name = (char*)malloc((StrLen + 1) * sizeof(char));
						if (this->Name != NULL) {
							memcpy(this->Name, Str, StrLen * sizeof(char));
							this->Name[StrLen] = '\0';
						}
					}
				}
			}

			type::type(id TypeSpecifier) {
				this->Master = nullptr;
				const char* Str = type::token_to_string(TypeSpecifier);
				if (Str != NULL) {
					this->ID = TypeSpecifier;
				}
				else {
					this->ID = id::UNKNOWN;
				}
				if ((this->ID != id::UNKNOWN) && (this->ID != id::STRUCT)) {
					this->Size = type::size_of(this->ID);
				}
				else {
					this->Size = 0;
				}
				this->MemberCount = 0;
				this->Member = nullptr;
				this->Name = NULL;
				if ((this->ID != id::STRUCT) && (Str != NULL)) {
					size_t StrLen = strlen(Str);
					this->Name = (char*)malloc((StrLen + 1) * sizeof(char));
					if (this->Name != NULL) {
						memcpy(this->Name, Str, StrLen * sizeof(char));
						this->Name[StrLen] = '\0';
					}
				}
			}

			type::type(const type& Arg) {
				this->Master = nullptr;
				this->ID = id::UNKNOWN;
				this->Size = 0;
				this->MemberCount = 0;
				this->Member = nullptr;
				this->Name = NULL;
				this->copy(Arg);
			}

			type::type(type&& Arg) {
				this->Master = nullptr;
				this->ID = Arg.ID;
				this->Size = Arg.Size;
				this->MemberCount = Arg.MemberCount;
				this->Member = Arg.Member;
				this->Name = Arg.Name;

				//Arg.Master = nullptr;
				Arg.ID = id::UNKNOWN;
				Arg.Size = 0;
				Arg.MemberCount = 0;
				Arg.Member = nullptr;
				Arg.Name = NULL;

				if ((this->ID == id::STRUCT) && (this->MemberCount > 0) && (this->Member != nullptr)) {
					for (int i = 0; i < this->MemberCount; i++) {
						this->Member[i].set_root(nullptr);
					}
				}
			}

			type::~type() {
				this->Master = nullptr;
				this->ID = id::UNKNOWN;
				this->Size = 0;
				this->MemberCount = 0;
				if (this->Member != nullptr) {
					delete[] this->Member;
					this->Member = nullptr;
				}
				if (this->Name != NULL) {
					free(this->Name);
					this->Name = NULL;
				}
			}

			type& type::operator=(id Rhs) {
				this->annihilate();
				this->create(Rhs);
				return *this;
			}

			type& type::operator=(const type& Rhs) {
				// Does recursive deep copy for all member variables.
				if (this == &Rhs) return *this;
				this->copy(Rhs);
				// TODO: If master exists, calculate memory Layout.
				//if (this->Master != nullptr) {
				//}
				return *this;
			}

			type& type::operator=(type&& Rhs) {
				// TODO: insert return statement here
				this->ID = Rhs.ID;
				this->Size = Rhs.Size;
				this->MemberCount = Rhs.MemberCount;
				this->Member = Rhs.Member;
				this->Name = Rhs.Name;

				Rhs.ID = id::UNKNOWN;
				Rhs.Size = 0;
				Rhs.MemberCount = 0;
				Rhs.Member = nullptr;
				Rhs.Name = NULL;

				for (int i = 0; i < this->MemberCount; i++) {
					if (this->Master != nullptr) {
						if (this->Master->Root != nullptr) {
							this->Member[i].set_root(this->Master->Root);
						}
						else {
							this->Member[i].set_root(this->Master);
						}
					}
					this->Member[i].Parent = this->Master;
				}

				return *this;
			}

			int type::push(int VariableCount, const variable* Variable) {
				if ((this->ID != id::STRUCT) || (VariableCount <= 0) || (Variable == nullptr)) return -1;
				size_t MemoryOffset, MemorySize;
				int n = this->MemberCount + VariableCount;
				variable* ptr = new variable[n];
				if (this->Master != nullptr) {
					MemoryOffset = this->Master->Offset;
				}
				else {
					MemoryOffset = 0;
				}
				MemorySize = 0;
				if (ptr != nullptr) {
					for (int i = 0; i < n; i++) {
						if (this->Master != nullptr) {
							if (this->Master->Root != nullptr) {
								ptr[i].Root = this->Master->Root;
							}
							else {
								ptr[i].Root = this->Master;
							}
						}
						ptr[i].Parent = this->Master;
						ptr[i].Offset = MemoryOffset + MemorySize;
						if (i < this->MemberCount) {
							ptr[i].swap(this->Member[i]);
						}
						else {
							ptr[i].copy(Variable[i - this->MemberCount]);
						}
						MemorySize += ptr[i].Size;
					}
				}

				if (this->Member != nullptr) {
					delete[] this->Member;
					this->Member = nullptr;
				}

				this->Size = MemorySize;
				this->MemberCount = n;
				this->Member = ptr;

				return 0;
			}

			int type::pop(int VariableCount) {
				if ((this->ID != id::STRUCT) || (VariableCount < -1) || (VariableCount == 0)) return -1;
				if ((this->MemberCount == 0) && (this->Member == nullptr)) return 0;
				if ((VariableCount == -1) || (VariableCount >= this->MemberCount)) {
					this->Size = 0;
					this->MemberCount = 0;
					if (this->Member != nullptr) {
						delete[] this->Member;
						this->Member = nullptr;
					}
				}
				else {
					// VariableCount is between 1 and  (MemberCount - 1)
					int n = this->MemberCount - VariableCount;
					variable* ptr = new variable[n];
					if (ptr == nullptr) return -2;

					size_t MemoryOffset, MemorySize;
					if (this->Master != nullptr) {
						MemoryOffset = this->Master->Offset;
					}
					else {
						MemoryOffset = 0;
					}
					MemorySize = 0;

					for (int i = 0; i < n; i++) {
						if (this->Master != nullptr) {
							if (this->Master->Root != nullptr) {
								ptr[i].Root = this->Master->Root;
							}
							else {
								ptr[i].Root = this->Master;
							}
						}
						ptr[i].Parent = this->Master;
						ptr[i].Offset = MemoryOffset + MemorySize;
						ptr[i].swap(this->Member[i]);
						MemorySize += ptr[i].Size;
					}

					this->Size = MemorySize;
					this->MemberCount = n;
					if (this->Member != nullptr) {
						delete[] this->Member;
					}
					this->Member = ptr;
				}
				return 0;
			}

			int type::insert(int Index, int VariableCount, const variable* Variable) {
				if ((this->ID != id::STRUCT) || (Index >= this->MemberCount) || (Index < 0) || (VariableCount <= 0) || (Variable == nullptr)) return -1;
				//if ((this->ID != id::STRUCT) || (this->MemberCount <= 0) || (this->Member == nullptr)) return -2;
				int n = this->MemberCount + VariableCount;
				variable* ptr = new variable[n];
				if (ptr == nullptr) return -2;

				size_t MemoryOffset, MemorySize;
				if (this->Master != nullptr) {
					MemoryOffset = this->Master->Offset;
				}
				else {
					MemoryOffset = 0;
				}
				MemorySize = 0;

				for (int i = 0; i < n; i++) {
					if (this->Master != nullptr) {
						if (this->Master->Root != nullptr) {
							ptr[i].Root = this->Master->Root;
						}
						else {
							ptr[i].Root = this->Master;
						}
					}
					ptr[i].Parent = this->Master;
					ptr[i].Offset = MemoryOffset + MemorySize;
					if ((i >= 0) && (i < Index)) {
						ptr[i].swap(this->Member[i]);
					}
					else if ((i >= Index) && (i < (Index + VariableCount))) {
						ptr[i].copy(Variable[i - Index]);
					}
					else {
						ptr[i].swap(this->Member[i - VariableCount]);
					}
					MemorySize += ptr[i].Size;
				}

				if (this->Member != nullptr) {
					delete[] this->Member;
				}
				this->Size = MemorySize;
				this->MemberCount = n;
				this->Member = ptr;

				return 0;
			}

			int type::remove(int Index, int VariableCount) {
				if ((Index < 0) || (Index >= this->MemberCount) || (VariableCount <= 0)) return -1;
				if ((this->ID != id::STRUCT) || (this->MemberCount <= 0) || (this->Member == nullptr)) return 0;
				// Index is between 0, and n
				// VariableCount > 0
				//
				int VarCount = 0;
				if ((Index + VariableCount) > this->MemberCount) {
					//VAriableCount - (VariableCount + Index - this->MemberCount)
					VarCount = this->MemberCount - Index;
				}
				else {
					VarCount = VariableCount;
				}

				if (VarCount >= this->MemberCount) {
					this->Size = 0;
					this->MemberCount = 0;
					if (this->Member != nullptr) {
						delete[] this->Member;
						this->Member = nullptr;
					}
					return 0;
				}

				int n = this->MemberCount - VarCount;
				variable* ptr = new variable[n];
				if (ptr == nullptr) return -2;

				size_t MemoryOffset, MemorySize;
				if (this->Master != nullptr) {
					MemoryOffset = this->Master->Offset;
				}
				else {
					MemoryOffset = 0;
				}
				MemorySize = 0;

				for (int i = 0; i < n; i++) {
					if (this->Master != nullptr) {
						if (this->Master->Root != nullptr) {
							ptr[i].Root = this->Master->Root;
						}
						else {
							ptr[i].Root = this->Master;
						}
					}
					ptr[i].Parent = this->Master;
					ptr[i].Offset = MemoryOffset + MemorySize;
					if ((i >= 0) && (i < Index)) {
						ptr[i].swap(this->Member[i]);
					}
					else {
						ptr[i].swap(this->Member[i + VarCount]);
					}
					MemorySize += ptr[i].Size;
				}

				this->Size = MemorySize;
				this->MemberCount = n;
				delete[] this->Member;
				this->Member = ptr;

				return 0;
			}

			//int type::exchange(int I, int J, int VariableCount) {
			//	return 0;
			//}

			int type::push(type::id TypeSpecifier, const char* IdentifierString) {
				return this->push(variable(TypeSpecifier, IdentifierString, 0, NULL));
			}

			int type::push(type::id TypeSpecifier, const char* IdentifierString, int SubscriptSize) {
				return this->push(variable(TypeSpecifier, IdentifierString, SubscriptSize, NULL));
			}

			int type::push(type::id TypeSpecifier, const char* IdentifierString, int SubscriptCount, int* SubscriptSize) {
				return this->push(variable(TypeSpecifier, IdentifierString, SubscriptCount, SubscriptSize));
			}

			int type::push(const type& TypeSpecifier, const char* IdentifierString) {
				return this->push(variable(TypeSpecifier, IdentifierString, 0, NULL));
			}

			int type::push(const type& TypeSpecifier, const char* IdentifierString, int SubscriptSize) {
				return this->push(variable(TypeSpecifier, IdentifierString, SubscriptSize, NULL));
			}

			int type::push(const type& TypeSpecifier, const char* IdentifierString, int SubscriptCount, int* SubscriptSize) {
				return this->push(variable(TypeSpecifier, IdentifierString, SubscriptCount, SubscriptSize));
			}

			int type::push(const variable& Variable) {
				return this->push(1, &Variable);
			}

			int type::pop() {
				return this->pop(1);
			}

			int type::insert(int Index, type::id TypeSpecifier, const char* IdentifierString) {
				return this->insert(Index, variable(TypeSpecifier, IdentifierString, 0, NULL));
			}

			int type::insert(int Index, type::id TypeSpecifier, const char* IdentifierString, int SubscriptSize) {
				return this->insert(Index, variable(TypeSpecifier, IdentifierString, SubscriptSize, NULL));
			}

			int type::insert(int Index, type::id TypeSpecifier, const char* IdentifierString, int SubscriptCount, int* SubscriptSize) {
				return this->insert(Index, variable(TypeSpecifier, IdentifierString, SubscriptCount, SubscriptSize));
			}

			int type::insert(int Index, const type& TypeSpecifier, const char* IdentifierString) {
				return this->insert(Index, variable(TypeSpecifier, IdentifierString, 0, NULL));
			}

			int type::insert(int Index, const type& TypeSpecifier, const char* IdentifierString, int SubscriptSize) {
				return this->insert(Index, variable(TypeSpecifier, IdentifierString, SubscriptSize, NULL));
			}

			int type::insert(int Index, const type& TypeSpecifier, const char* IdentifierString, int SubscriptCount, int* SubscriptSize) {
				return this->insert(Index, variable(TypeSpecifier, IdentifierString, SubscriptCount, SubscriptSize));
			}

			int type::insert(int Index, const variable& Variable) {
				return this->insert(Index, 1, &Variable);
			}

			int type::remove(int Index) {
				return this->remove(Index, 1);
			}

			//int type::exchange(int I, int J) {
			//	return this->exchange(I, J, 1);
			//}

			int type::set_name(const char* TypeName) {
				if (TypeName != NULL) {
					size_t m, n;
					m = strlen(TypeName);
					if (this->Name != NULL) {
						n = strlen(this->Name);
					}
					else {
						n = 0;
					}
					void* nptr = NULL;
					if (this->Name == NULL) {
						nptr = malloc((m + 1) * sizeof(char));
					}
					else if (n != m) {
						nptr = realloc(this->Name, (m + 1) * sizeof(char));
					}
					if (nptr == NULL) return -2;
					if (nptr != (void*)this->Name) this->Name = (char*)nptr;
					nptr = NULL;
					memcpy(this->Name, TypeName, m * sizeof(char));
					this->Name[m] = '\0';
				}
				else {
					if (this->Name != NULL) {
						free(this->Name);
						this->Name = NULL;
					}
				}
				return 0;
			}

			const char* type::get_name() const {
				return this->Name;
			}
#ifdef MODE_DEBUG
			std::string type::get_str() {
				std::string temp = "";
				return temp;
			}
#endif // MODE_DEBUG
			//std::string type::get_str() {
			//	// DONT FUCKING MULTITHREAD
			//	static int Depth = 0;
			//	std::string Str;
			//	Str.append(token_to_string(this->ID));
			//	if (this->ID == id::STRUCT) {
			//		Depth += 1;
			//		Str.push_back(' ');
			//		if (this->Name != NULL) {
			//			Str.append(this->Name);
			//			Str.push_back(' ');
			//		}
			//		Str.push_back('{');
			//		Str.push_back('\n');
			//		for (int i = 0; i < this->MemberCount; i++) {
			//			for (int j = 0; j < Depth; j++) {
			//				Str.append("  ");
			//			}
			//			Str.append(this->Member[i].get_str());
			//			Str.push_back(';');
			//			Str.push_back('\n');
			//		}
			//		Depth -= 1;
			//		for (int j = 0; j < Depth; j++) {
			//			Str.append("  ");
			//		}
			//		Str.push_back('}');
			//	}
			//	return Str;
			//}

			size_t type::size_of(id TypeSpecifier) {
				for (int i = 0; i < BUILT_IN_TYPE_LIST_SIZE; i++) {
					if (TypeSpecifier == BuiltInType[i].TypeID)
						return BuiltInType[i].Size;
				}
				return 0;
			}

			size_t type::size_of(const type& TypeSpecifier) {
				size_t temp = 0;
				if ((TypeSpecifier.ID == type::id::STRUCT) && (TypeSpecifier.MemberCount > 0)) {
					for (int i = 0; i < TypeSpecifier.MemberCount; i++) {
						temp += variable::size_of(TypeSpecifier.Member[i]);
					}
				}
				else {
					temp = type::size_of(TypeSpecifier.ID);
				}
				return temp;
			}

			type::id type::string_to_token(const char* TypeSpecifier) {
				if (TypeSpecifier == NULL) return type::id::UNKNOWN;
				size_t Length = strlen(TypeSpecifier);
				if (Length == 0) return type::id::UNKNOWN;
				for (int i = 0; i < BUILT_IN_TYPE_LIST_SIZE; i++) {
					if (Length == strlen(BuiltInType[i].TypeName)) {
						if (memcmp(TypeSpecifier, BuiltInType[i].TypeName, Length * sizeof(char)) == 0) {
							return BuiltInType[i].TypeID;
						}
					}
				}
				return type::id::UNKNOWN;
			}

			const char* type::token_to_string(id TypeSpecifier) {
				for (int i = 0; i < BUILT_IN_TYPE_LIST_SIZE; i++) {
					if (TypeSpecifier == BuiltInType[i].TypeID)
						return BuiltInType[i].TypeName;
				}
				return NULL;
			}

			type::id type::basic_type_id_of(id TypeSpecifier) {
				for (int i = 0; BUILT_IN_TYPE_LIST_SIZE; i++) {
					if (TypeSpecifier == BuiltInType[i].TypeID)
						return BuiltInType[i].DataTypeID;
				}
				return type::id::UNKNOWN;

			}

			math::integer type::element_count_of(id TypeSpecifier) {
				for (int i = 0; BUILT_IN_TYPE_LIST_SIZE; i++) {
					if (TypeSpecifier == BuiltInType[i].TypeID)
						return BuiltInType[i].ElementCount;
				}
				return 0;
			}

			math::integer type::row_count_of(id TypeSpecifier) {
				for (int i = 0; BUILT_IN_TYPE_LIST_SIZE; i++) {
					if (TypeSpecifier == BuiltInType[i].TypeID)
						return BuiltInType[i].Rows;
				}
				return 0;
			}

			math::integer type::col_count_of(id TypeSpecifier) {
				for (int i = 0; BUILT_IN_TYPE_LIST_SIZE; i++) {
					if (TypeSpecifier == BuiltInType[i].TypeID)
						return BuiltInType[i].Columns;
				}
				return 0;
			}

			int type::create(id TypeSpecifier) {
				return this->create(TypeSpecifier, NULL);
			}

			int type::create(id TypeSpecifier, const char* TypeName) {
				this->ID = TypeSpecifier;
				this->Size = type::size_of(TypeSpecifier);
				this->MemberCount = 0;
				this->Member = nullptr;
				if (this->ID != type::id::STRUCT) {
					return this->set_name(token_to_string(TypeSpecifier));
				}
				else {
					return this->set_name(TypeName);
				}
			}

			int type::annihilate() {
				this->ID = id::UNKNOWN;
				this->Size = 0;
				this->MemberCount = 0;
				if (this->Member != nullptr) {
					delete[] this->Member;
					this->Member = nullptr;
				}
				if (this->Name != NULL) {
					free(this->Name);
					this->Name = NULL;
				}
				return 0;
			}

			type type::clone() const {
				type temp;
				temp.copy(*this);
				return temp;
			}

			int type::copy(const type& TypeSpecifier) {
				// Do not call this unless "this" is already empty.
				if ((TypeSpecifier.ID == id::STRUCT) && (TypeSpecifier.MemberCount > 0) && (TypeSpecifier.Member != nullptr)) {
					this->ID = TypeSpecifier.ID;
					this->Size = 0;
					this->MemberCount = TypeSpecifier.MemberCount;
					this->Member = new variable[this->MemberCount];
					if (this->Member != nullptr) {
						for (int i = 0; i < this->MemberCount; i++) {
							if (this->Master != nullptr) {
								if (this->Master->Root != nullptr) {
									this->Member[i].Root = this->Master->Root;
								}
								else {
									this->Member[i].Root = this->Master;
								}
							}
							else {
								this->Member[i].Root = nullptr;
							}
							this->Member[i].Parent = this->Master;
							if (this->Master != nullptr) {
								this->Member[i].Offset = this->Master->Offset + this->Size;
							}
							else {
								this->Member[i].Offset = this->Size;
							}
							this->Member[i].copy(TypeSpecifier.Member[i]);
							this->Size += this->Member[i].Size;
						}
					}
					else {
						this->MemberCount = 0;
					}
				}
				else {
					this->ID = TypeSpecifier.ID;
					this->Size = type::size_of(TypeSpecifier.ID);
					this->MemberCount = 0;
					this->Member = nullptr;
				}
				this->set_name(TypeSpecifier.get_name());
				return 0;
			}

			int type::swap(type& TypeSpecifier) {
				// This function swaps values and pointers
				type temp;

				temp.ID = this->ID;
				temp.Size = this->Size;
				temp.MemberCount = this->MemberCount;
				temp.Member = this->Member;
				temp.Name = this->Name;

				this->ID = TypeSpecifier.ID;
				this->Size = TypeSpecifier.Size;
				this->MemberCount = TypeSpecifier.MemberCount;
				this->Member = TypeSpecifier.Member;
				this->Name = TypeSpecifier.Name;

				TypeSpecifier.ID = temp.ID;
				TypeSpecifier.Size = temp.Size;
				TypeSpecifier.MemberCount = temp.MemberCount;
				TypeSpecifier.Member = temp.Member;
				TypeSpecifier.Name = temp.Name;

				temp.ID = id::UNKNOWN;
				temp.Size = 0;
				temp.MemberCount = 0;
				temp.Member = nullptr;
				temp.Name = NULL;

				return 0;
			}

			variable::variable() {
				this->Root = nullptr;
				this->Parent = nullptr;
				this->Offset = 0;
				this->Size = 0;
				this->Type.Master = this;
				this->Type.ID = type::id::UNKNOWN;
				this->Type.Size = 0;
				this->Type.MemberCount = 0;
				this->Type.Member = nullptr;
				this->Type.Name = NULL;
				this->Name = NULL;
				this->DimensionCount = 0;
				this->Dimension = NULL;
			}

			variable::variable(type::id TypeSpecifier, const char* IdentifierString) {
				this->Root = nullptr;
				this->Parent = nullptr;
				this->Offset = 0;
				this->Size = 0;
				this->Type.Master = this;
				this->Type.ID = type::id::UNKNOWN;
				this->Type.Size = 0;
				this->Type.MemberCount = 0;
				this->Type.Member = nullptr;
				this->Type.Name = NULL;
				this->Name = NULL;
				this->DimensionCount = 0;
				this->Dimension = NULL;
				this->create(TypeSpecifier, IdentifierString, 0, NULL);
			}

			variable::variable(type::id TypeSpecifier, const char* IdentifierString, int SubscriptSize) {
				this->Root = nullptr;
				this->Parent = nullptr;
				this->Offset = 0;
				this->Size = 0;
				this->Type.Master = this;
				this->Type.ID = type::id::UNKNOWN;
				this->Type.Size = 0;
				this->Type.MemberCount = 0;
				this->Type.Member = nullptr;
				this->Type.Name = NULL;
				this->Name = NULL;
				this->DimensionCount = 0;
				this->Dimension = NULL;
				this->create(TypeSpecifier, IdentifierString, SubscriptSize, NULL);
			}

			variable::variable(type::id TypeSpecifier, const char* IdentifierString, int SubscriptCount, int* SubscriptSize) {
				this->Root = nullptr;
				this->Parent = nullptr;
				this->Offset = 0;
				this->Size = 0;
				this->Type.Master = this;
				this->Type.ID = type::id::UNKNOWN;
				this->Type.Size = 0;
				this->Type.MemberCount = 0;
				this->Type.Member = nullptr;
				this->Type.Name = NULL;
				this->Name = NULL;
				this->DimensionCount = 0;
				this->Dimension = NULL;
				this->create(TypeSpecifier, IdentifierString, SubscriptCount, SubscriptSize);
			}

			variable::variable(const type& TypeSpecifier, const char* IdentifierString) {
				this->Root = nullptr;
				this->Parent = nullptr;
				this->Offset = 0;
				this->Size = 0;
				this->Type.Master = this;
				this->Type.ID = type::id::UNKNOWN;
				this->Type.Size = 0;
				this->Type.MemberCount = 0;
				this->Type.Member = nullptr;
				this->Type.Name = NULL;
				this->Name = NULL;
				this->DimensionCount = 0;
				this->Dimension = NULL;
				this->create(TypeSpecifier, IdentifierString, 0, NULL);
			}

			variable::variable(const type& TypeSpecifier, const char* IdentifierString, int SubscriptSize) {
				this->Root = nullptr;
				this->Parent = nullptr;
				this->Offset = 0;
				this->Size = 0;
				this->Type.Master = this;
				this->Type.ID = type::id::UNKNOWN;
				this->Type.Size = 0;
				this->Type.MemberCount = 0;
				this->Type.Member = nullptr;
				this->Type.Name = NULL;
				this->Name = NULL;
				this->DimensionCount = 0;
				this->Dimension = NULL;
				this->create(TypeSpecifier, IdentifierString, SubscriptSize, NULL);
			}

			variable::variable(const type& TypeSpecifier, const char* IdentifierString, int SubscriptCount, int* SubscriptSize) {
				this->Root = nullptr;
				this->Parent = nullptr;
				this->Offset = 0;
				this->Size = 0;
				this->Type.Master = this;
				this->Type.ID = type::id::UNKNOWN;
				this->Type.Size = 0;
				this->Type.MemberCount = 0;
				this->Type.Member = nullptr;
				this->Type.Name = NULL;
				this->Name = NULL;
				this->DimensionCount = 0;
				this->Dimension = NULL;
				this->create(TypeSpecifier, IdentifierString, SubscriptCount, SubscriptSize);
			}

			variable::variable(const variable& Arg) {
				this->Root = nullptr;
				this->Parent = nullptr;
				this->Offset = 0;
				this->Size = 0;
				this->Type.Master = this;
				this->Type.ID = type::id::UNKNOWN;
				this->Type.Size = 0;
				this->Type.MemberCount = 0;
				this->Type.Member = nullptr;
				this->Type.Name = NULL;
				this->Name = NULL;
				this->DimensionCount = 0;
				this->Dimension = NULL;
				this->copy(Arg);
			}

			variable::variable(variable&& Arg) {
				this->Root = nullptr;
				this->Parent = nullptr;
				this->Offset = 0;
				this->Size = 0;
				this->Type.Master = this;
				this->Type.ID = type::id::UNKNOWN;
				this->Type.Size = 0;
				this->Type.MemberCount = 0;
				this->Type.Member = nullptr;
				this->Type.Name = NULL;
				this->Name = NULL;
				this->DimensionCount = 0;
				this->Dimension = NULL;
				this->swap(Arg);
			}

			variable::~variable() {
				this->Root = nullptr;
				this->Parent = nullptr;
				this->Offset = 0;
				this->Type.Master = nullptr;
				this->Type.ID = type::id::UNKNOWN;
				this->Type.Size = 0;
				this->Type.MemberCount = 0;
				if (this->Type.Member != nullptr) {
					delete[] this->Type.Member;
					this->Type.Member = nullptr;
				}
				if (this->Type.Name != NULL) {
					free(this->Type.Name);
					this->Type.Name = NULL;
				}
				if (this->Name != NULL) {
					free(this->Name);
					this->Name = NULL;
				}
				this->DimensionCount = 0;
				if (this->Dimension != NULL) {
					free(this->Dimension);
					this->Dimension = NULL;
				}
			}

			variable& variable::operator=(const variable& Rhs) {
				// I think this is good, check recursion if works.
				// If left hand side is a child node, user is responsible
				// for generating offsets for the rest of the tree.
				if (this == &Rhs) return *this;
				this->clear();
				this->copy(Rhs);
				//if ((this->Root != nullptr) && (this->Parent != nullptr)) {}
				return *this;
			}

			variable& variable::operator=(variable&& Rhs) {
				this->clear();
				this->swap(Rhs);
				return *this;
			}

			variable& variable::operator[](int Index) {
				return this->Type.Member[Index];
			}

			const variable& variable::operator[](int Index) const {
				return this->Type.Member[Index];
			}

			int variable::set_type(const type& VariableType) {
				this->Type = VariableType;
				return 0;
			}


			type variable::get_type() const {
				return type(this->Type);
			}

			int variable::set_name(const char* VariableName) {
				if (VariableName != NULL) {
					size_t m, n;
					m = strlen(VariableName);
					if (this->Name != NULL) {
						n = strlen(this->Name);
					}
					else {
						n = 0;
					}
					void* nptr = NULL;
					if (this->Name == NULL) {
						nptr = malloc((m + 1) * sizeof(char));
					}
					else if (n != m) {
						nptr = realloc(this->Name, (m + 1) * sizeof(char));
					}
					if (nptr == NULL) return -1;
					if (nptr != (void*)this->Name) this->Name = (char*)nptr;
					nptr = NULL;
					memcpy(this->Name, VariableName, m * sizeof(char));
					this->Name[m] = '\0';
				}
				else {
					if (this->Name != NULL) {
						free(this->Name);
						this->Name = NULL;
					}
				}
				return 0;
			}

			const char* variable::get_name() const {
				return this->Name;
			}

			int variable::set_array_size(int SubscriptCount, int* SubscriptSize) {
				if (SubscriptCount < 0) return -1;
				if (SubscriptCount > 0) {
					void* nptr = NULL;
					// Determine memory allocation.
					if (SubscriptSize != NULL) {
						if (this->Dimension == NULL) {
							nptr = malloc(SubscriptCount * sizeof(int));
						}
						else {
							nptr = realloc(this->Dimension, SubscriptCount * sizeof(int));
						}
					}
					else {
						if (this->Dimension == NULL) {
							nptr = malloc(sizeof(int));
						}
						else {
							nptr = realloc(this->Dimension, sizeof(int));
						}
					}

					// Check if allocation failed.
					if (nptr == NULL) return -2;
					if (nptr != (void*)this->Dimension) this->Dimension = (int*)nptr;
					nptr = NULL;

					// Copy Data.
					if (SubscriptSize != NULL) {
						this->DimensionCount = SubscriptCount;
						memcpy(this->Dimension, SubscriptSize, this->DimensionCount * sizeof(int));
					}
					else {
						this->DimensionCount = 1;
						this->Dimension[0] = SubscriptCount;
					}
				}
				else {
					this->DimensionCount = 0;
					if (this->Dimension != NULL) {
						free(this->Dimension);
						this->Dimension = NULL;
					}
				}
				return 0;
			}
#ifdef MODE_DEBUG
			std::string variable::get_str() {
				static int d = 0;
				static std::string Shift = "                     |";
				static std::string Header = "Size:     Offset:    \n";
				static int HeaderOffsetPosition = 10;
				std::string Indent = "   ";
				std::string Out = "";
				std::string StrSize = std::to_string(this->Size);
				std::string StrOffset = std::to_string(this->Offset);
				const char* t = NULL;
				if (d == 0) {
					Out.append(Header);
				}
				if (this->Type.ID == type::id::STRUCT) {
					Out.append(Shift);
				}
				else {
					for (int i = 0; i < Shift.length(); i++) {
						if ((i >= 0) && (i < StrSize.length())) {
							Out.push_back(StrSize[i]);
						}
						else if ((i >= StrSize.length()) && (i < HeaderOffsetPosition)) {
							Out.push_back(Shift[i]);
						}
						else if ((i >= HeaderOffsetPosition) && (i < (StrOffset.length() + HeaderOffsetPosition))) {
							Out.push_back(StrOffset[i - HeaderOffsetPosition]);
						}
						else {
							Out.push_back(Shift[i]);
						}
					}
				}
				for (int i = 0; i < d; i++) {
					Out.append(Indent);
				}
				if (this->Type.ID == type::id::STRUCT) {
					Out.append("struct ");
					if (this->Type.Name != NULL) {
						Out.append(this->Type.Name);
						Out.push_back(' ');
					}
					Out.push_back('{');
					Out.push_back('\n');
					d += 1;
					if ((this->Type.MemberCount > 0) && (this->Type.Member != nullptr)) {
						for (int i = 0; i < this->Type.MemberCount; i++) {
							Out.append(this->Type.Member[i].get_str());
						}
					}
					d -= 1;
					for (int i = 0; i < Shift.length(); i++) {
						if ((i >= 0) && (i < StrSize.length())) {
							Out.push_back(StrSize[i]);
						}
						else if ((i >= StrSize.length()) && (i < HeaderOffsetPosition)) {
							Out.push_back(Shift[i]);
						}
						else if ((i >= HeaderOffsetPosition) && (i < (StrOffset.length() + HeaderOffsetPosition))) {
							Out.push_back(StrOffset[i - HeaderOffsetPosition]);
						}
						else {
							Out.push_back(Shift[i]);
						}
					}
					for (int i = 0; i < d; i++) {
						Out.append(Indent);
					}
					Out.push_back('}');
					Out.push_back(' ');
					//s.append(this->Name);
					//s.push_back(';');
				}
				else {
					t = type::token_to_string(this->Type.ID);
					if (t != NULL) {
						Out.append(t);
						Out.push_back(' ');
					}
					//s.append(this->Name);
					//s.push_back(';');
				}
				Out.append(this->Name);
				if ((this->DimensionCount > 0) && (this->Dimension != NULL)) {
					for (int i = 0; i < this->DimensionCount; i++) {
						Out.push_back('[');
						Out.append(std::to_string(this->Dimension[i]));
						Out.push_back(']');
					}
				}
				Out.push_back(';');
				Out.push_back('\n');
				return Out;
			}
#endif // MODE_DEBUG
			size_t variable::size_of(const variable& Arg) {
				size_t temp = 0;
				temp = type::size_of(Arg.Type);
				if (Arg.Dimension != NULL) {
					for (int i = 0; i < Arg.DimensionCount; i++) {
						temp *= Arg.Dimension[i];
					}
				}
				return temp;
			}

			int variable::create(type::id TypeSpecifier, const char* TypeName, const char* IdentifierString, int SubscriptCount, int* SubscriptSize) {
				return this->create(type(TypeSpecifier, TypeName), IdentifierString, SubscriptCount, SubscriptSize);
			}

			int variable::create(const type& TypeSpecifier, const char* IdentifierString, int SubscriptCount, int* SubscriptSize) {
				// this function assumes
				int ErrorCode = 0;
				this->Type.Master = this;
				this->Type.copy(TypeSpecifier);
				ErrorCode |= this->set_name(IdentifierString);
				ErrorCode |= this->set_array_size(SubscriptCount, SubscriptSize);
				this->Size = this->Type.Size;
				if ((this->DimensionCount > 0) && (this->Dimension != NULL) && (this->Size > 0)) {
					for (int i = 0; i < this->DimensionCount; i++) {
						this->Size = (this->Size) * ((size_t)(this->Dimension[i]));
					}
				}
				return ErrorCode;
			}

			int variable::clear() {
				this->Size = 0;
				this->Type.annihilate();
				if (this->Name != NULL) {
					free(this->Name);
					this->Name = NULL;
				}
				this->DimensionCount = 0;
				if (this->Dimension != NULL) {
					free(this->Dimension);
					this->Dimension = NULL;
				}
				return 0;
			}

			int variable::set_root(variable* VarRoot) {
				this->Root = VarRoot;
				if (this->Root == nullptr) {
					this->Parent = nullptr;
				}
				if ((this->Type.ID == type::id::STRUCT) && (this->Type.MemberCount > 0)) {
					for (int i = 0; i < this->Type.MemberCount; i++) {
						if (this->Root == nullptr) {
							this->Type.Member[i].set_root(this);
						}
						else {
							this->Type.Member[i].set_root(this->Root);
						}
					}
				}
				return 0;
			}

			variable variable::clone() const {
				variable temp;
				temp.copy(*this);
				return temp;
			}

			int variable::copy(const variable& Var) {
				// Before calling, this must be an empty node.
				// Uses pre existing variables: Root, Parent, Offset.
				//this->Root;
				//this->Parent;
				this->Size = 0;
				//this->Offset;
				this->Type.Master = this;
				if ((Var.Type.ID == type::id::STRUCT) && (Var.Type.MemberCount > 0)) {
					this->Type.ID = Var.Type.ID;
					this->Type.Size = 0;
					this->Type.MemberCount = Var.Type.MemberCount;
					this->Type.Member = new variable[this->Type.MemberCount];
					if (this->Type.Member != nullptr) {
						for (int i = 0; i < this->Type.MemberCount; i++) {
							if (this->Root == nullptr) {
								this->Type.Member[i].Root = this;
							}
							else {
								this->Type.Member[i].Root = this->Root;
							}
							this->Type.Member[i].Parent = this;
							this->Type.Member[i].Offset = this->Offset + this->Type.Size;
							this->Type.Member[i].copy(Var.Type.Member[i]);
							this->Type.Size += this->Type.Member[i].Size;
						}
					}
					else {
						this->Type.MemberCount = 0;
					}
				}
				else {
					this->Type.ID = Var.Type.ID;
					this->Type.Size = type::size_of(Var.Type.ID);
					this->Type.MemberCount = 0;
					this->Type.Member = nullptr;
				}
				this->Type.set_name(Var.Type.get_name());
				this->set_name(Var.get_name());
				this->Size = this->Type.Size;
				this->DimensionCount = Var.DimensionCount;
				if (this->DimensionCount > 0) {
					this->Dimension = (int*)malloc(this->DimensionCount * sizeof(int));
				}
				else {
					this->DimensionCount = 0;
				}
				if ((this->Dimension != NULL) && (Var.Dimension != NULL)) {
					memcpy(this->Dimension, Var.Dimension, this->DimensionCount * sizeof(int));
					for (int i = 0; i < this->DimensionCount; i++) {
						this->Size *= Var.Dimension[i];
					}
				}
				return 0;
			}

			int variable::swap(variable& Var) {
				variable temp;
				//temp.Root = Var.Root;
				//temp.Parent = Var.Parent;
				//temp.Offset = Var.Offset;
				temp.Size = this->Size;
				//temp.Type.Master = Var.Type.Master;
				temp.Type.ID = this->Type.ID;
				temp.Type.Size = this->Type.Size;
				temp.Type.MemberCount = this->Type.MemberCount;
				temp.Type.Member = this->Type.Member;
				temp.Type.Name = this->Type.Name;
				temp.Name = this->Name;
				temp.DimensionCount = this->DimensionCount;
				temp.Dimension = this->Dimension;
				//
				//
				//
				this->Size = Var.Size;
				//
				this->Type.ID = Var.Type.ID;
				this->Type.Size = Var.Type.Size;
				this->Type.MemberCount = Var.Type.MemberCount;
				this->Type.Member = Var.Type.Member;
				this->Type.Name = Var.Type.Name;
				this->Name = Var.Name;
				this->DimensionCount = Var.DimensionCount;
				this->Dimension = Var.Dimension;
				//
				//
				//
				Var.Size = temp.Size;
				//
				Var.Type.ID = temp.Type.ID;
				Var.Type.Size = temp.Type.Size;
				Var.Type.MemberCount = temp.Type.MemberCount;
				Var.Type.Member = temp.Type.Member;
				Var.Type.Name = temp.Type.Name;
				Var.Name = temp.Name;
				Var.DimensionCount = temp.DimensionCount;
				Var.Dimension = temp.Dimension;
				//
				//
				//
				temp.Size = 0;
				//
				temp.Type.ID = type::id::UNKNOWN;
				temp.Type.Size = 0;
				temp.Type.MemberCount = 0;
				temp.Type.Member = nullptr;
				temp.Type.Name = NULL;
				temp.Name = NULL;
				temp.DimensionCount = 0;
				temp.Dimension = NULL;

				this->set_root(this->Root);
				if ((this->Type.ID == type::id::STRUCT) && (this->Type.MemberCount > 0) && (this->Type.Member != nullptr)) {
					for (int i = 0; i < this->Type.MemberCount; i++) {
						this->Type.Member[i].Parent = this->Type.Master;
					}
				}

				Var.set_root(Var.Root);
				if ((Var.Type.ID == type::id::STRUCT) && (Var.Type.MemberCount > 0) && (Var.Type.Member != nullptr)) {
					for (int i = 0; i < Var.Type.MemberCount; i++) {
						Var.Type.Member[i].Parent = Var.Type.Master;
					}
				}

				return 0;
			}

			//int variable::calculate_memory_layout() {
			//	if ((this->Type.ID == type::id::STRUCT) && (this->Type.MemberCount > 0) && (this->Type.Member != nullptr)) {
			//		this->Type.Size = 0;
			//		for (int i = 0; i < this->Type.MemberCount; i++) {
			//
			//		}
			//	}
			//	else {
			//		this->Type.Size = type::size_of(this->Type.ID);
			//	}
			//	if ((this->ArrayDimCount > 0) && (this->ArrayDimSize != NULL)) {
			//		this->Size = this->Type.Size;
			//		for (int i = 0; i < this->ArrayDimCount; i++) {
			//			this->Size *= this->ArrayDimSize[i];
			//		}
			//	}
			//	return 0;
			//}

#ifdef MODE_DEBUG
			void unit_test_variable() {

				type particle(type::id::STRUCT, "particle");
				particle.push(type::id::REAL3, "Position");
				particle.push(type::id::REAL3, "Momentum");
				particle.push(type::id::REAL3, "Force");
				particle.push(type::id::REAL, "Mass");

				type light(type::id::STRUCT, "light");
				light.push(type::id::REAL3, "Position");
				light.push(type::id::REAL4, "Color", 3);
				//int Array[2] = { 2, 3 };
				//light.push(type::id::REAL4, "Color", 2, Array);

				type glow(type::id::STRUCT, "glow");
				glow.push(particle, "Particle");
				glow.push(light, "Light");
				glow.push(type::id::REAL4X4, "Transform");
				glow.push(type::id::REAL3, "Position");
				glow.push(type::id::REAL, "Scale");

				variable Glow(glow, "Glow");
				//variable Glow(glow, "Glow");

				std::cout << Glow.get_str() << std::endl;
				std::cout << "sizeof(Glow) = " << variable::size_of(Glow) << " = " << Glow.Size << std::endl;

				type mega(type::id::STRUCT, "mega");
				mega.push(glow, "Huehue");
				mega.push(particle, "narwhals");
				mega.push(light, "ultra");
				variable Mega(mega, "Tyler");

				std::cout << Mega.get_str() << std::endl;
				std::cout << "sizeof(Tyler) = " << variable::size_of(Mega) << " = " << Mega.Size << std::endl;

				variable Test(type::id::STRUCT, "Test");
				std::cout << Test.get_str() << std::endl;
				Test.Type.push(type::id::REAL3, "Pos");
				std::cout << Test.get_str() << std::endl;
				Test.Type.push(type::id::REAL2, "TexCoord");
				std::cout << Test.get_str() << std::endl;
				Test.Type.push(type::id::REAL4X4, "FakeTransform");
				std::cout << Test.get_str() << std::endl;
				Test.Type.push(type::id::REAL3, "Normal");
				std::cout << Test.get_str() << std::endl;
				Test.Type.push(type::id::REAL4X4, "Transform");
				std::cout << Test.get_str() << std::endl;
				Test.Type.remove(2);
				std::cout << Test.get_str() << std::endl;
				Test.Type.remove(1, 2);
				std::cout << Test.get_str() << std::endl;
				Test.Type.push(type::id::REAL3X2, "Var0");
				std::cout << Test.get_str() << std::endl;
				Test.Type.push(type::id::REAL2X4, "Var1");
				std::cout << Test.get_str() << std::endl;
				Test.Type.push(type::id::NATURAL3, "Var2");
				std::cout << Test.get_str() << std::endl;
				Test.Type.push(type::id::INTEGER2, "Var3");
				std::cout << Test.get_str() << std::endl;
				Test.Type.push(type::id::REAL, "Var4");
				std::cout << Test.get_str() << std::endl;
				Test.Type.push(type::id::INTEGER, "Var5");
				std::cout << Test.get_str() << std::endl;
				//Test.Type.remove(0, 2);
				//std::cout << Test.get_str() << std::endl;
				variable temp(type::id::INTEGER, "Var225");
				Test.Type.insert(5, 1, &temp);
				std::cout << Test.get_str() << std::endl;
				Test.Type.insert(6, type::id::INTEGER, "Var250");
				std::cout << Test.get_str() << std::endl;
				Test.Type.insert(7, type::id::INTEGER, "Var275");
				std::cout << Test.get_str() << std::endl;
				Test.Type.remove(3, 4);
				std::cout << Test.get_str() << std::endl;
				Test.Type.pop(-1);
				std::cout << Test.get_str() << std::endl;

				// Test Constructors
				type ta;
				type tb(type::id::REAL3X4);
				type tc(type::id::STRUCT);
				type td(type::id::STRUCT, "td");
				type te(type::id::REAL3X4, "te");
				//type tf(type::id::TVOID, "tf");

				type tCopyConstructor(glow);
				type tMoveConstructor(glow.clone());
				type tCopyAssign = glow;
				type tMoveAssign = glow.clone();

				variable CopyConstructor(Glow);
				variable MoveConstructor(Glow.clone());
				variable CopyAssign = Glow;
				variable MoveAssign = Glow.clone();

				std::cout << CopyConstructor.get_str() << std::endl;
				std::cout << MoveConstructor.get_str() << std::endl;
				std::cout << CopyAssign.get_str() << std::endl;
				std::cout << MoveAssign.get_str() << std::endl;

				return;
			}
#endif // MODE_DEBUG

		}
	}
}

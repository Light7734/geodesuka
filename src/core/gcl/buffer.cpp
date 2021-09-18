#include <geodesuka/core/gcl/buffer.h>

#include <stdarg.h>

#include <geodesuka/core/math.h>

#include <geodesuka/core/util/variable.h>

namespace geodesuka {
	namespace core {
		namespace gcl {

			buffer::buffer(context* aContext, int aFlags, int aUsage, int aCount, variable aMemoryLayout, void* aBufferData) {
				this->aParentDC = aContext;

				this->CreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
				this->CreateInfo.pNext = NULL;
				this->CreateInfo.flags = (VkBufferCreateFlags)aFlags;
				this->CreateInfo.size = aCount * aMemoryLayout.Type.Size;
				this->CreateInfo.usage = (VkBufferUsageFlags)aUsage;
				this->CreateInfo.sharingMode = VkSharingMode::VK_SHARING_MODE_EXCLUSIVE;
				this->CreateInfo.queueFamilyIndexCount = 0;
				this->CreateInfo.pQueueFamilyIndices = NULL;

				this->Handle = VK_NULL_HANDLE;
				this->MemoryHandle = VK_NULL_HANDLE;

				this->Flags = aFlags;
				this->Usage = aUsage;
				this->Count = aCount;
				this->MemoryLayout = aMemoryLayout;

				VkResult Result = vkCreateBuffer(aContext->handle(), &this->CreateInfo, NULL, &this->Handle);
				if (Result != VK_SUCCESS) {

				}
			}

			buffer::buffer(context* aContext, int aFlags, int aUsage, int aCount, type aTypeSpecifier, const char* aIdentifier, void* aBufferData) {
				this->init_all(aContext, aFlags, aUsage, aCount, variable(aTypeSpecifier, aIdentifier), aBufferData);
			}

			buffer::~buffer() {
				this->clear_all();
			}

			bool buffer::init_all(context* aContext, int aFlags, int aUsage, int aCount, variable aMemoryLayout, void* aBufferData) {
				this->aParentDC = aContext;

				this->CreateInfo.sType						= VkStructureType::VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
				this->CreateInfo.pNext						= NULL;
				this->CreateInfo.flags						= (VkBufferCreateFlags)aFlags;
				this->CreateInfo.size						= aCount * aMemoryLayout.Type.Size;
				this->CreateInfo.usage						= (VkBufferUsageFlags)aUsage;
				this->CreateInfo.sharingMode				= VkSharingMode::VK_SHARING_MODE_EXCLUSIVE;
				this->CreateInfo.queueFamilyIndexCount		= 0;
				this->CreateInfo.pQueueFamilyIndices		= NULL;

				this->Handle = VK_NULL_HANDLE;
				this->MemoryHandle = VK_NULL_HANDLE;

				this->Flags = aFlags;
				this->Usage = aUsage;
				this->Count = aCount;
				this->MemoryLayout = aMemoryLayout;

				VkResult Result = vkCreateBuffer(aContext->handle(), &this->CreateInfo, NULL, &this->Handle);
				if (Result != VK_SUCCESS) {

				}
				return false;
			}

			bool buffer::clear_all() {

				return false;
			}



		}
	}
}

//buffer::buffer() {
//	/* DEFAULT CONSTRUCTOR */
//	this->Root = nullptr;
//	this->Parent = nullptr;
//	this->ChildCount = 0;
//	this->Child = nullptr;
//
//	this->MemorySize = 0;
//	this->MemoryOffset = 0;
//	this->TypeQualifierID = NULL;
//	this->NameStr = NULL;
//	this->ArrayDimCount = 0;
//	this->ArrayDimSize = NULL;
//	this->Count = 0;
//	this->hptr = NULL;
//}
//
//buffer::~buffer() {
//	/* DESTRUCTOR */
//	if (this->hptr != NULL) {
//		if (this->Root == nullptr) {
//			free(this->hptr);
//		}
//		this->hptr = NULL;
//	}
//	this->Count = 0;
//	if (this->ArrayDimSize != NULL) {
//		free(this->ArrayDimSize); this->ArrayDimSize = NULL;
//	}
//	this->ArrayDimCount = 0;
//	if (this->NameStr != NULL) {
//		free(this->NameStr); this->NameStr = NULL;
//	}
//	this->TypeQualifierID = NULL;
//	this->MemoryOffset = 0;
//	this->MemorySize = 0;
//
//	if (this->Child != nullptr) {
//		delete[] this->Child; this->Child = nullptr;
//	}
//	this->ChildCount = 0;
//	//this->Parent = nullptr;
//	//this->Root = nullptr;
//}
//
//buffer::buffer(const buffer & inp) {
//	this->Root = nullptr;
//	this->Parent = nullptr;
//	this->ChildCount = inp.ChildCount;
//	this->Child = nullptr;
//	if (this->ChildCount > 0) {
//		this->Child = new buffer[this->ChildCount];
//		if (this->Child == nullptr) this->ChildCount = 0;
//	}
//	for (integer i = 0; i < this->ChildCount; i++) {
//		this->Child[i].Root = this;
//		this->Child[i].Parent = this;
//		this->Child[i] = inp[i];
//	}
//
//	this->MemorySize = inp.MemorySize;
//	this->MemoryOffset = inp.MemoryOffset;
//	this->TypeQualifierID = inp.TypeQualifierID;
//	if (this->NameStr != NULL) {
//		free(this->NameStr); this->NameStr = NULL;
//	}
//	size_t StrLen = 0;
//	if (inp.NameStr != NULL) {
//		StrLen = strlen(inp.NameStr);
//		if (StrLen > 0) {
//			this->NameStr = (char*)malloc((StrLen + 1) * sizeof(char));
//		}
//		if (this->NameStr != NULL) {
//			memcpy(this->NameStr, inp.NameStr, StrLen * sizeof(char));
//			this->NameStr[StrLen] = '\0';
//		}
//	}
//	if (this->ArrayDimSize != NULL) {
//		free(this->ArrayDimSize); this->ArrayDimSize = NULL;
//	}
//	this->ArrayDimCount = inp.ArrayDimCount;
//	if (this->ArrayDimCount > 0) {
//		this->ArrayDimSize = (integer*)malloc(this->ArrayDimCount * sizeof(integer));
//	}
//	if ((this->ArrayDimSize != NULL) && (inp.ArrayDimSize != NULL)) {
//		memcpy(this->ArrayDimSize, inp.ArrayDimSize, this->ArrayDimCount * sizeof(integer));
//	}
//
//	this->Count = 0;
//	this->hptr = NULL;
//}
//
//buffer::buffer(buffer && inp) {
//	// MOVE CONSTRUCTOR
//	Root = inp.Root;
//	Parent = inp.Parent;
//	ChildCount = inp.ChildCount;
//	Child = inp.Child;
//	MemorySize = inp.MemorySize;
//	MemoryOffset = inp.MemoryOffset;
//	TypeQualifierID = inp.TypeQualifierID;
//	NameStr = inp.NameStr;
//	ArrayDimCount = inp.ArrayDimCount;
//	ArrayDimSize = inp.ArrayDimSize;
//	inp.Root = nullptr;
//	inp.Parent = nullptr;
//	inp.ChildCount = 0;
//	inp.Child = nullptr;
//	inp.MemorySize = 0;
//	inp.MemoryOffset = 0;
//	inp.TypeQualifierID = NULL;
//	inp.NameStr = NULL;
//	inp.ArrayDimCount = 0;
//	inp.ArrayDimSize = NULL;
//}
//
//buffer::buffer(int TypeSpecifier, const char* IdentifierString) {
//
//}
//
//buffer::buffer(int TypeSpecifier, const char* IdentifierString, int SubscriptCount, int* SubscriptSize) {
//	this->Root = nullptr;
//	this->Parent = nullptr;
//	this->ChildCount = 0;
//	this->Child = nullptr;
//
//	if ((this->get_type_name_of(TypeSpecifier) != NULL) /*&& (IdentifierString != NULL)*/) {
//		this->MemorySize = this->get_size_of(TypeSpecifier);
//		this->MemoryOffset = 0;
//		this->TypeQualifierID = TypeSpecifier;
//		if (IdentifierString != NULL) {
//			size_t StrLen = strlen(IdentifierString);
//			if (StrLen > 0) {
//				this->NameStr = (char*)malloc((StrLen + 1) * sizeof(char));
//				if (this->NameStr != NULL) {
//					memcpy(this->NameStr, IdentifierString, StrLen * sizeof(char));
//					this->NameStr[StrLen] = '\0';
//				}
//			}
//		}
//		if (SubscriptCount > 0) {
//			if (SubscriptSize != NULL) {
//				this->ArrayDimCount = SubscriptCount;
//			}
//			else {
//				this->ArrayDimCount = 1;
//			}
//		}
//		else {
//			this->ArrayDimCount = 0;
//		}
//
//		if (this->ArrayDimCount > 0) {
//			this->ArrayDimSize = (int *)malloc(this->ArrayDimCount * sizeof(int));
//		}
//
//		if (this->ArrayDimSize != NULL) {
//			if (SubscriptSize != NULL) {
//				memcpy(this->ArrayDimSize, SubscriptSize, this->ArrayDimCount * sizeof(int));
//			}
//			else {
//				//memcpy(this->ArrayDimSize, &SubscriptCount, this->ArrayDimCount * sizeof(integer));
//				this->ArrayDimSize[0] = SubscriptCount;
//			}
//		}
//
//		if (this->ArrayDimSize != NULL) {
//			int TotalDimensionalSize = 1;
//			for (int i = 0; i < this->ArrayDimCount; i++) {
//				TotalDimensionalSize = this->ArrayDimSize[i];
//			}
//		}
//	}
//	else {
//		this->MemorySize = 0;
//		this->MemoryOffset = 0;
//		this->TypeQualifierID = NULL;
//		this->NameStr = NULL;
//		this->ArrayDimCount = 0;
//		this->ArrayDimSize = NULL;
//	}
//	this->Count = 0;
//	this->hptr = NULL;
//}
//
//buffer& buffer::operator=(const buffer& rhs) {
//	/* COPY ASSIGNMENT */
//	if (this == &rhs) return *this;
//
//	boolean NodeDamage = false;
//
//	this->MemorySize = rhs.MemorySize;
//	//this->MemoryOffset = 0;
//	this->TypeQualifierID = rhs.TypeQualifierID;
//	if (this->NameStr != NULL) {
//		free(this->NameStr); this->NameStr = NULL;
//	}
//	size_t StrLen = 0;
//	if (rhs.NameStr != NULL) {
//		StrLen = strlen(rhs.NameStr);
//		if (StrLen > 0) {
//			this->NameStr = (char*)malloc((StrLen + 1) * sizeof(char));
//			if (this->NameStr == NULL) NodeDamage = true;
//		}
//		if (this->NameStr != NULL) {
//			memcpy(this->NameStr, rhs.NameStr, StrLen * sizeof(char));
//			this->NameStr[StrLen] = '\0';
//		}
//	}
//	if (this->ArrayDimSize != NULL) {
//		free(this->ArrayDimSize); this->ArrayDimSize = NULL;
//	}
//	this->ArrayDimCount = rhs.ArrayDimCount;
//	if (this->ArrayDimCount > 0) {
//		this->ArrayDimSize = (integer *)malloc(this->ArrayDimCount * sizeof(integer));
//		if (this->ArrayDimSize == NULL) NodeDamage = true;
//	}
//	if ((this->ArrayDimSize != NULL) && (rhs.ArrayDimSize != NULL)) {
//		memcpy(this->ArrayDimSize, rhs.ArrayDimSize, this->ArrayDimCount * sizeof(integer));
//	}
//
//	// -------------------- Node Map -------------------- //
//
//	//this->Root = rhs.Root;
//	//this->Parent = rhs.Parent;
//	this->ChildCount = rhs.ChildCount;
//	if (this->Child != nullptr) {
//		delete[] this->Child; this->Child = nullptr;
//	}
//
//	if ((this->TypeQualifierID == buffer::STRUCT) && (this->ChildCount > 0)) {
//		// Composite Structure
//		size_t TotalSize = 0;
//		this->Child = new buffer[this->ChildCount];
//		if (this->Child == nullptr) NodeDamage = true;
//		if ((this->Child != nullptr) && (rhs.Child != nullptr)) {
//			for (integer i = 0; i < this->ChildCount; i++) {
//
//				if (this->Root == nullptr) {
//					this->Child[i].Root = this;
//				}
//				else {
//					this->Child[i].Root = this->Root;
//				}
//				this->Child[i].Parent = this;
//
//				this->Child[i] = rhs[i];
//
//				this->Child[i].MemoryOffset = this->MemoryOffset + TotalSize;
//
//				TotalSize += this->Child[i].MemorySize;
//			}
//
//			if (TotalSize != this->MemorySize) {
//
//			}
//		}
//		else {
//			// Memory Allocation Failure
//			this->ChildCount = 0;
//
//			this->MemorySize = 0;
//			this->MemoryOffset = 0;
//		}
//	}
//
//	return *this;
//}
//
//buffer & buffer::operator=(buffer && rhs) {
//	this->Root = rhs.Root;
//	this->Parent = rhs.Parent;
//	this->ChildCount = rhs.ChildCount;
//	this->Child = rhs.Child;
//	this->MemorySize = rhs.MemorySize;
//	this->MemoryOffset = rhs.MemoryOffset;
//	this->TypeQualifierID = rhs.TypeQualifierID;
//	this->NameStr = rhs.NameStr;
//	this->ArrayDimCount = rhs.ArrayDimCount;
//	this->ArrayDimSize = rhs.ArrayDimSize;
//	rhs.Root = nullptr;
//	rhs.Parent = nullptr;
//	rhs.ChildCount = 0;
//	rhs.Child = nullptr;
//	rhs.MemorySize = 0;
//	rhs.MemoryOffset = 0;
//	rhs.TypeQualifierID = NULL;
//	rhs.NameStr = NULL;
//	rhs.ArrayDimCount = 0;
//	rhs.ArrayDimSize = NULL;
//	return *this;
//}
//
//buffer& buffer::operator[](int Index) {
//	//tex:
//	// $\text{Consider an } n \text{-dimensional array} $
//	// $\text{Declaration:} \quad A[m_{0}][m_{1}]...[m_{n-1}] \rightarrow \text{Access:} \quad A[k_{0}][k_{1}]...[k_{n-1}]$
//	// $ Access = \displaystyle\sum_{i = 0}^{n - 2} k_{i} \displaystyle\prod_{j = i + 1}^{n-1}m_{j} + k_{n-1} $
//	return this->Child[Index];
//}
//
//const buffer& buffer::operator[](int Index) const {
//	return this->Child[Index];
//}
//
//int buffer::create(int TypeSpecifier, const char* IdentifierString) {
//	return this->create(TypeSpecifier, IdentifierString, 0, NULL);
//}
//
//int buffer::create(int TypeSpecifier, const char* IdentifierString, int SubscriptSize) {
//	return this->create(TypeSpecifier, IdentifierString, SubscriptSize, NULL);
//}
//
//int buffer::create(int TypeSpecifier, /*const char *TypeSpecifierString,*/ const char *IdentifierString, int SubscriptCount, int *SubscriptSize) {
//	if (this->get_type_name_of(TypeSpecifier) == NULL) return -1;
//
//	if ((SubscriptCount > 0) && (SubscriptSize != NULL)) {
//		for (int i = 0; i < SubscriptCount; i++) {
//			if (SubscriptSize[i] <= 0) return -1;
//		}
//	}
//
//	this->annihilate();
//
//	this->TypeQualifierID = TypeSpecifier;
//	this->NameStr = NULL;
//	if (IdentifierString != NULL) {
//		size_t CharCount = strlen(IdentifierString);
//		if (CharCount > 0) {
//			this->NameStr = (char *)malloc((CharCount + 1) * sizeof(char));
//			if (this->NameStr != NULL) {
//				memcpy(this->NameStr, IdentifierString, CharCount * sizeof(char));
//				this->NameStr[CharCount] = '\0';
//			}
//		}
//	}
//
//	if ((SubscriptCount > 0) && (SubscriptSize != NULL)) {
//		this->ArrayDimCount = SubscriptCount;
//	}
//	else if (SubscriptCount > 0) {
//		this->ArrayDimCount = 1;
//	}
//	else {
//		this->ArrayDimCount = 0;
//	}
//
//	if (this->ArrayDimCount > 0) {
//		this->ArrayDimSize = (integer*)malloc(this->ArrayDimCount * sizeof(integer));
//		if (this->ArrayDimSize == NULL) this->ArrayDimCount = 0;
//	}
//
//	if (this->ArrayDimSize != NULL) {
//		if ((SubscriptCount > 0) && (SubscriptSize != NULL)) {
//			memcpy(this->ArrayDimSize, SubscriptSize, this->ArrayDimCount*sizeof(integer));
//		}
//		else if (SubscriptCount > 0) {
//			memcpy(this->ArrayDimSize, &SubscriptCount, this->ArrayDimCount * sizeof(integer));
//		}
//	}
//
//	if (this->TypeQualifierID == buffer::STRUCT) {
//		this->MemorySize = 0;
//	}
//	else {
//		this->MemorySize = this->get_size_of(this->TypeQualifierID);
//		for (int i = 0; i < this->ArrayDimCount; i++) {
//			this->MemorySize *= this->ArrayDimSize[i];
//		}
//	}
//
//	return 0;
//}
//
//int buffer::annihilate() {
//	if (this->hptr != NULL) {
//		if (this->Root == nullptr) {
//			free(this->hptr);
//		}
//		this->hptr = NULL;
//	}
//	this->Count = 0;
//	if (this->ArrayDimSize != NULL) {
//		free(this->ArrayDimSize); this->ArrayDimSize = NULL;
//	}
//	this->ArrayDimCount = 0;
//	if (this->NameStr != NULL) {
//		free(this->NameStr); this->NameStr = NULL;
//	}
//	this->TypeQualifierID = NULL;
//	this->MemoryOffset = 0;
//	this->MemorySize = 0;
//
//	if (this->Child != nullptr) {
//		delete[] this->Child; this->Child = nullptr;
//	}
//	this->ChildCount = 0;
//	//this->Parent = nullptr;
//	//this->Root = nullptr;
//	return 0;
//}
//
//int buffer::push(int VariableCount, int* TypeSpecifier, const char** IdentifierString, int* SubscriptCount, int** SubscriptSize) {
//	// Check if proper struct first.
//	if (this->TypeQualifierID != buffer::STRUCT) return -1;
//	// First validate arguments
//	if ((VariableCount <= 0) || (TypeSpecifier == NULL) || (IdentifierString == NULL)/*|| (SubscriptCount == NULL) || (SubscriptSize == NULL)*/) return -1;
//	// Second, check if args are
//	for (int i = 0; i < VariableCount; i++) {
//		if ((this->get_type_name_of(TypeSpecifier[i]) == NULL) || (IdentifierString[i] == NULL)) return -1;
//	}
//
//	integer NewTotalCount = this->ChildCount + VariableCount;
//	buffer* NewTotalChild = new buffer[NewTotalCount];
//	if (NewTotalChild != nullptr) {
//		integer j = 0;
//		for (integer i = 0; i < NewTotalCount; i++) {
//			if ((i >= 0) && (i < this->ChildCount)) {
//				// Swap Data from old.
//			}
//			else {
//				j = i - this->ChildCount;
//				if ((SubscriptCount != NULL) && (SubscriptSize != NULL)) {
//					NewTotalChild[i].create(TypeSpecifier[j], IdentifierString[j], SubscriptCount[j], SubscriptSize[j]);
//				}
//				else if (SubscriptCount != NULL) {
//					NewTotalChild[i].create(TypeSpecifier[j], IdentifierString[j], SubscriptCount[j], NULL);
//				}
//				else {
//					NewTotalChild[i].create(TypeSpecifier[j], IdentifierString[j], 0, NULL);
//				}
//			}
//		}
//	}
//
//	return 0;
//}
//
//buffer buffer::get_hard_copy() {
//	buffer temp;
//
//	if (!this->isHollowNode) {
//		temp = *this;
//	}
//	else {
//		temp.isHollowNode = false;
//
//	}
//
//	temp.Root = this;
//
//	return temp;
//}
//
//buffer buffer::get_hollow_copy() {
//	buffer temp;
//
//	temp.isHollowNode = true;
//	temp.Root = this->Root;
//	if (!this->isHollowNode) {
//		temp.Parent = this;
//	}
//	else {
//		temp.Parent = this->Parent;
//	}
//	temp.ChildCount = this->ChildCount;
//	temp.Child = this->Child;
//
//	temp.MemorySize = this->MemorySize;
//	temp.MemoryOffset = this->MemoryOffset;
//	temp.TypeQualifierID = this->TypeQualifierID;
//	temp.NameStr = this->NameStr;
//	temp.ArrayDimCount = this->ArrayDimCount;
//	temp.ArrayDimSize = this->ArrayDimSize;
//
//	temp.Count = this->Count;
//	temp.hptr = this->hptr;
//
//	//temp.NameStr = NULL;
//	//if (this->NameStr != NULL) {
//	//	size_t CharCount = strlen(this->NameStr);
//	//	if (CharCount > 0) {
//	//		temp.NameStr = (char *)malloc((CharCount + 1) * sizeof(char));
//	//		if (temp.NameStr != NULL) {
//	//			memcpy(temp.NameStr, this->NameStr, CharCount * sizeof(char));
//	//			temp.NameStr[CharCount] = '\0';
//	//		}
//	//	}
//	//}
//
//	return temp;
//}
//
//int buffer::reserve_memory(int VertexCount) {
//	/* If this is the root node, memory operations are allowed */
//	if (this != Root) { return -1; }
//
//	
//
//
//	return 0;
//}
//
//int buffer::resize_memory(int VertexCount) {
//
//
//
//
//	return 0;
//}
//
//int buffer::release_memory() {
//	
//
//	if (hptr == NULL) { return 0; }
//	free(hptr); hptr = NULL;
//	return 0;
//}
//
//int buffer::set(int VertexIndex, const void * Arg, size_t ArgMemSize) {
//	/* Actually it's your fault if you go out of bounds dipshit. */
//	uintptr_t BaseAddress = (uintptr_t)Root->hptr;
//	uintptr_t MemoryShift = ((uintptr_t)VertexIndex)*((uintptr_t)Root->MemorySize) + ((uintptr_t)this->MemoryOffset);
//	uintptr_t TargetAddress = BaseAddress + MemoryShift;
//	memcpy((void *)TargetAddress, Arg, ArgMemSize);
//	return 0;
//}

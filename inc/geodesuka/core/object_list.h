#pragma once
#ifndef GEODESUKA_CORE_OBJECT_LIST_H
#define GEODESUKA_CORE_OBJECT_LIST_H

#include "object_t.h"

namespace geodesuka::core {

	class object_list {
	public:

		object_list();
		object_list(int aObjectCount);
		object_list(int aObjectCount, object_t** aObjectList);
		object_list(const object_list& aInp);
		object_list(object_list&& aInp);
		~object_list();

		object_list& operator=(const object_list& aRhs);
		object_list& operator=(object_list&& aRhs);

		object_t* operator[](int aIndex) const;
		object_t*& operator[](int aIndex);

		object_list operator+(const object_list& aRhs) const;
		object_list operator-(const object_list& aRhs) const;

		object_list& operator+=(const object_list& aRhs);
		object_list& operator-=(const object_list& aRhs);

		object_list operator&(const object_list& aRhs) const;
		object_list operator|(const object_list& aRhs) const;


		object_list& operator=(const object_t* aRhs);
		object_list& operator+=(const object_t* aRhs);
		object_list& operator-=(const object_t* aRhs);
		
		// Purify List by Stage. Returns removed objects.
		object_list purify_by(stage_t* aStage);

		int count();
		object_t** ptr();

	private:
		int Count;
		object_t** Handle;
	};

}

#endif // !GEODESUKA_CORE_OBJECT_LIST_H

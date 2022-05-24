#pragma once
#ifndef GEODESUKA_CORE_UTIL_STR_H
#define GEODESUKA_CORE_UTIL_STR_H
//#define TEXT_DEBUG

/// <summary>
/// text.h is simply a class to replace char * arrays for memory
/// management. will be extended for graphical rendering. Essentially 
/// boiler plate code, was not satisfied with the functionality of <string>
/// </summary>

#include <cstddef>

namespace geodesuka::core::util {

	class str {
	public:

		size_t n;
		char* hptr;

		// Default Constructor.
		str();

		//text(const char* Format, ...);

		str(const char* Arg);
		str(const str& Arg);
		//text(text&& Arg);

		// Destructor.
		~str();

		str& operator=(const char* Rhs);
		str& operator=(const str& Rhs);
		//text& operator=(text&& Rhs);

		str operator+(const char* Rhs);
		str operator+(const str& Rhs);

		str& operator+=(const char* Rhs);
		str& operator+=(const str& Rhs);

		bool operator==(const char* Rhs) const;
		bool operator==(const str& Rhs) const;

		//bool operator!=(const char* Rhs) const;
		//bool operator!=(const text& Rhs) const;

		char& operator[](int Index);
		char operator[](int Index) const;

		// Multi Character Modifiers
		bool push(const char* Str);
		bool pop(int Count);
		bool insert(int Index, const char* Str);
		bool remove(int Index, int Count);
		bool exchange(int I, int J, int Count);
		bool permute(int Count);
		bool reverse(int Index, int Count);
		bool reverse();

		bool push(str& Str);
		bool insert(int Index, str& Str);

		// Single Character Modifiers
		bool push(char Character);
		bool pop();
		bool insert(int Index, char Character);
		bool remove(int Index);
		bool exchange(int I, int J);

		str split_at(char Character);
		str split_at(const char* Pattern);

		const char* ptr() const;
		size_t size() const;
		bool clear();

		//bool set_font();

		// String number manip

		static float to_float(const char* Arg);
		//static float to_float(const text& Arg);
		static double to_double(const char* Arg);
		//static double to_double(const text& Arg);

	};

#ifdef TEXT_DEBUG
	void text_unit_test();
#endif // TEXT_DEBUG

}

#endif // !GEODESUKA_CORE_UTIL_STR_H

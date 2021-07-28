#ifndef TEXT_H
#define TEXT_H

//#include <stdlib.h>
//#include <stdarg.h>

//#define TEXT_DEBUG
// Essentially boiler plate code, was not satisfied with the functionality of <string>

class text {
public:

	int n;
	char* hptr;

	// Default Constructor.
	text();

	//text(char Arg);
	//text(short Arg);
	//text(int Arg);
	//text(unsigned char Arg);
	//text(unsigned short Arg);
	//text(unsigned int Arg);
	//text(float Arg);
	//text(double Arg);

	//text(const char* Format, ...);

	text(const char* Arg);
	text(const text& Arg);
	//text(text&& Arg);

	// Destructor.
	~text();

	text& operator=(const char* Rhs);
	text& operator=(const text& Rhs);
	//text& operator=(text&& Rhs);

	text operator+(const char* Rhs);
	text operator+(const text& Rhs);

	text& operator+=(const char* Rhs);
	text& operator+=(const text& Rhs);

	bool operator==(const char* Rhs) const;
	bool operator==(const text& Rhs) const;

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

	bool push(text& Str);
	bool insert(int Index, text& Str);

	// Single Character Modifiers
	bool push(char Character);
	bool pop();
	bool insert(int Index, char Character);
	bool remove(int Index);
	bool exchange(int I, int J);

	text split_at(char Character);
	text split_at(const char *Pattern);

	const char* str() const;
	int size() const;
	bool clear();

	//bool set_font();

	// String number manip

	static float to_float(const char *Arg);
	//static float to_float(const text& Arg);
	static double to_double(const char *Arg);
	//static double to_double(const text& Arg);

};

#ifdef TEXT_DEBUG
void text_unit_test();
#endif // TEXT_DEBUG

#endif // !TEXT_H

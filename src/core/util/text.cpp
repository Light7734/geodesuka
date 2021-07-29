#include <geodesuka/core/util/text.h>

// Standard C Library.
//#include <limits.h>
//#include <stdint.h>
//#include <float.h>
//#include <stdio.h>
#include <stdlib.h>
//#include <stdarg.h>
#include <string.h>
//#include <ctype.h>
//#include <math.h>

#ifdef TEXT_DEBUG
#include <iostream>
#endif // TEXT_DEBUG

namespace geodesuka {
	namespace core {
		namespace util {

			text::text() {
				this->n = 0;
				this->hptr = NULL;
			}
			/*
			text::text(const char* Format, ...) {
				va_list ArgList;
				va_start(ArgList, Format);
				this->n = vsnprintf(NULL, 0, Format, ArgList);
				this->hptr = (char*)malloc((this->n + 1)*sizeof(char));
				if (this->hptr != NULL) {
					this->n = vsnprintf(this->hptr, (this->n + 1) * sizeof(char), Format, ArgList);
				}
				va_end(ArgList);
			}
			*/
			text::text(const char* Str) {
				this->n = 0;
				this->hptr = NULL;
				if (Str != NULL) {
					size_t StrLength = strlen(Str);
					this->hptr = (char*)malloc((StrLength + 1) * sizeof(char));
					if (this->hptr != NULL) {
						this->n = StrLength;
						memcpy(this->hptr, Str, this->n * sizeof(char));
						this->hptr[this->n] = '\0';
					}
				}
			}

			text::text(const text& Arg) {
				this->n = 0;
				this->hptr = NULL;
				if (Arg.hptr != NULL) {
					size_t StrLength = strlen(Arg.hptr);
					this->hptr = (char*)malloc((StrLength + 1) * sizeof(char));
					if (this->hptr != NULL) {
						this->n = StrLength;
						memcpy(this->hptr, Arg.hptr, this->n * sizeof(char));
						this->hptr[this->n] = '\0';
					}
				}
			}
			/*
			text::text(text&& Arg) {
				this->n = Arg.n;
				this->hptr = Arg.hptr;
				Arg.n = 0;
				Arg.hptr = NULL;
			}
			*/
			text::~text() {
				if (this->hptr == NULL) {
					free(this->hptr);
					this->hptr = NULL;
				}
				this->n = 0;
			}
			text& text::operator=(const char* Rhs) {
				if (this->hptr == Rhs) return *this;
				if (Rhs == NULL) {
					this->clear();
					return *this;
				}
				size_t StrLength = strlen(Rhs);
				if (this->n != StrLength) {
					void* nptr = NULL;
					if (this->hptr == NULL) {
						nptr = malloc((StrLength + 1) * sizeof(char));
					}
					else {
						nptr = realloc(this->hptr, (StrLength + 1) * sizeof(char));
					}
					if (nptr == NULL) return *this;
					if (nptr != (void*)this->hptr) this->hptr = (char*)nptr;
					nptr = NULL;
					this->n = StrLength;
					this->hptr[this->n] = '\0';
				}
				if (this->n > 0) {
					memcpy(this->hptr, Rhs, this->n * sizeof(char));
				}
				return *this;
			}

			text& text::operator=(const text& Rhs) {
				return (*this = Rhs.hptr);
			}
			/*
			text& text::operator=(text&& Rhs) {
				this->clear();
				this->n = Rhs.n;
				this->hptr = Rhs.hptr;
				Rhs.n = 0;
				Rhs.hptr = NULL;
				return *this;
			}
			*/
			text text::operator+(const char* Rhs) {
				text temp;
				if (Rhs == NULL) return *this;
				size_t StrLength = strlen(Rhs);
				temp.n = this->n + StrLength;
				temp.hptr = (char*)malloc((temp.n + 1) * sizeof(char));
				if (temp.hptr == NULL) {
					temp.n = 0;
					return temp;
				}
				// After successful allocation.
				if (this->n > 0) {
					memcpy(temp.hptr, this->hptr, this->n * sizeof(char));
				}
				if (StrLength > 0) {
					memcpy(temp.hptr + this->n * sizeof(char), Rhs, StrLength * sizeof(char));
				}
				temp.hptr[temp.n] = '\0';
				return temp;
			}

			text text::operator+(const text& Rhs) {
				return (*this + Rhs.hptr);
			}

			text& text::operator+=(const char* Rhs) {
				this->push(Rhs);
				return *this;
			}

			text& text::operator+=(const text& Rhs) {
				this->push(Rhs.hptr);
				return *this;
			}

			bool text::operator==(const char* Rhs) const {
				if (Rhs == NULL) return this->n == 0;
				if (this->n != strlen(Rhs)) return false;
				return (memcmp(this->hptr, Rhs, this->n * sizeof(char)) == 0);
			}

			bool text::operator==(const text& Rhs) const {
				return *this == Rhs.hptr;
			}

			char& text::operator[](int Index) {
				return this->hptr[Index];
			}

			char text::operator[](int Index) const {
				if ((Index >= 0) && (Index < this->n)) {
					return this->hptr[Index];
				}
				else {
					return '\0';
				}
			}

			bool text::push(const char* Str) {
				if (Str == NULL) return false;
				size_t StrLength = strlen(Str);
				if (StrLength == 0) return false;
				size_t NewLength = this->n + StrLength;
				void* nptr = NULL;
				if (this->hptr == NULL) {
					nptr = malloc((NewLength + 1) * sizeof(char));
				}
				else {
					nptr = realloc(this->hptr, (NewLength + 1) * sizeof(char));
				}
				if (nptr == NULL) return true; // Memory Allocation Failure
				if (nptr != (void*)this->hptr) this->hptr = (char*)nptr;
				nptr = NULL;
				memcpy(this->hptr + this->n * sizeof(char), Str, StrLength * sizeof(char));
				this->hptr[NewLength] = '\0';
				this->n = NewLength;
				return false;
			}

			bool text::pop(int Count) {
				if (Count <= 0) return false;
				if (Count > this->n) {
					this->clear();
					return false;
				}
				size_t NewLength = this->n - (size_t)Count;
				void* nptr = realloc(this->hptr, (NewLength + 1) * sizeof(char));
				if (nptr == NULL) return true;
				if (nptr != (void*)this->hptr) this->hptr = (char*)nptr;
				nptr = NULL;
				this->hptr[NewLength] = '\0';
				this->n = NewLength;
				return false;
			}

			bool text::insert(int Index, const char* Str) {
				if (Str == NULL) return false;
				size_t StrLength = strlen(Str);
				if (StrLength == 0) return false;
				size_t NewLength = this->n + StrLength;
				void* nptr = NULL;
				if (this->hptr == NULL) {
					nptr = malloc((NewLength + 1) * sizeof(char));
				}
				else {
					nptr = realloc(this->hptr, (NewLength + 1) * sizeof(char));
				}
				if (nptr == NULL) return true;
				if (nptr != (void*)this->hptr) this->hptr = (char*)nptr;
				nptr = NULL;
				// Move old contents up.
				memcpy(this->hptr + (Index + StrLength) * sizeof(char), this->hptr + Index * sizeof(char), (this->n - Index) * sizeof(char));
				memcpy(this->hptr + Index * sizeof(char), Str, StrLength * sizeof(char));
				this->hptr[NewLength] = '\0';
				this->n = NewLength;
				return false;
			}

			bool text::remove(int Index, int Count) {
				if (Count <= 0) return false;
				size_t TruncatedCount = 0;
				if (Count <= (this->n - Index)) {
					TruncatedCount = Count;
				}
				else {
					TruncatedCount = this->n - Index;
				}
				size_t NewLength = this->n - TruncatedCount;
				if (Count < (this->n - Index)) {
					memcpy(this->hptr + Index * sizeof(char), this->hptr + (Index + Count) * sizeof(char), (this->n - Index - Count) * sizeof(char));
				}
				memset(this->hptr + (this->n - Count) * sizeof(char), '\0', Count * sizeof(char));
				void* nptr = realloc(this->hptr, (NewLength + 1) * sizeof(char));
				if (nptr == NULL) return true;
				if (nptr != (void*)this->hptr) this->hptr = (char*)nptr;
				nptr = NULL;
				this->n = NewLength;
				this->hptr[this->n] = '\0';
				return false;
			}

			bool text::exchange(int I, int J, int Count) {
				for (int i = 0; i < Count; i++) {
					char temp = this->hptr[I + i];
					this->hptr[I + i] = this->hptr[J + i];
					this->hptr[J + i] = temp;
				}
				return false;
			}

			bool text::permute(int Count) {
				if ((hptr == NULL) || (n == 0)) { return true; }
				void* nptr = NULL;
				int a = abs(Count);
				int b = n;
				if (a >= n) { a = a % n; }
				if ((Count != 0) && (a != 0)) {
					nptr = malloc(b * sizeof(char));
					if (nptr == NULL) { return true; }
					if (Count > 0) {
						// Positive Integers
						memcpy(nptr, hptr + a * sizeof(char), (b - a) * sizeof(char));
						memcpy((char*)nptr + (b - a) * sizeof(char), hptr, a * sizeof(char));
					}
					else {
						// Negative Integers
						memcpy(nptr, hptr + (b - a) * sizeof(char), a * sizeof(char));
						memcpy((char*)nptr + a * sizeof(char), hptr, (b - a) * sizeof(char));
					}
					memcpy(hptr, nptr, b * sizeof(char));
					free(nptr); nptr = NULL;
				}
				return false;
			}

			bool text::reverse(int Index, int Count) {
				int HalfCount = (Count - Count % 2) / 2;
				for (int i = 0; i < HalfCount; i++) {
					char temp = this->hptr[i + Index];
					this->hptr[i + Index] = this->hptr[Count + Index - i - 1];
					this->hptr[Count + Index - i - 1] = temp;
				}
				return false;
			}

			bool text::reverse() {
				return this->reverse(0, this->n);
			}

			bool text::push(text& Str) {
				return this->push(Str.hptr);
			}

			bool text::insert(int Index, text& Str) {
				return this->insert(Index, Str.hptr);
			}

			bool text::push(char Character) {
				char temp[2];
				temp[0] = Character;
				temp[1] = '\0';
				return this->push(temp);
			}

			bool text::pop() {
				return this->pop(1);
			}

			bool text::insert(int Index, char Character) {
				char temp[2];
				temp[0] = Character;
				temp[1] = '\0';
				return this->insert(Index, temp);
			}

			bool text::remove(int Index) {
				return this->remove(Index, 1);
			}

			bool text::exchange(int I, int J) {
				return this->exchange(I, J, 1);
			}

			text text::split_at(char Character) {
				char S[2];
				S[0] = Character;
				S[1] = '\0';
				return this->split_at(S);
			}

			text text::split_at(const char* Pattern) {
				text temp;
				int Location = -1;
				int MatchCount = 0;
				int StrLength = strlen(Pattern);
				for (int i = 0; i < this->n; i++) {
					if (this->hptr[i] == Pattern[MatchCount]) {
						if (MatchCount == 0) {
							Location = i;
						}
						MatchCount += 1;
					}
					else {
						Location = -1;
						MatchCount = 0;
					}
					if (MatchCount == StrLength) break;
				}
				if (Location > 0) {
					temp.hptr = (char*)malloc((Location + 1) * sizeof(char));
					if (temp.hptr == NULL) return temp;
					temp.n = Location;
					memcpy(temp.hptr, this->hptr, temp.n * sizeof(char));
					temp.hptr[temp.n] = '\0';
					//this->remove(0, Location);
					this->remove(0, Location + StrLength);
				}
				return temp;
			}

			const char* text::str() const {
				if (this->hptr != NULL) {
					return this->hptr;
				}
				else {
					return "";
				}
			}

			int text::size() const {
				return this->n;
			}

			bool text::clear() {
				if (this->hptr != NULL) {
					free(this->hptr);
					this->hptr = NULL;
				}
				this->n = 0;
				return false;
			}

			float text::to_float(const char* Arg) {
				return (float)atof(Arg);
			}

			double text::to_double(const char* Arg) {
				return atof(Arg);
			}

#ifdef TEXT_DEBUG
			void text_unit_test() {
				text Str1("hello");
				text Str2 = "World";
				text Str = "The quick brown fox chased the little rabbit!";
				std::cout << "Str1 = " << Str1.hptr << std::endl;
				std::cout << "Str2 = " << Str2.hptr << std::endl;

				Str1.clear();
				Str1.push("Hel");
				Str1.push("lo");
				std::cout << "Str1 = " << Str1.hptr << std::endl;
				Str1.pop(3);
				std::cout << "Str1 = " << Str1.hptr << std::endl;
				Str1.insert(2, " is dumb");
				std::cout << "Str1 = " << Str1.hptr << std::endl;
				Str1.remove(3, 10);
				std::cout << "Str1 = " << Str1.hptr << std::endl;

				std::cout << "Str = " << Str.hptr << std::endl;
				Str.exchange(4, 10, 5);
				std::cout << "Str = " << Str.hptr << std::endl;
				Str.remove(4, 6);
				std::cout << "Str = " << Str.hptr << std::endl;
				Str.insert(10, "brown ");
				std::cout << "Str = " << Str.hptr << std::endl;
				Str.pop(8);
				std::cout << "Str = " << Str.hptr << std::endl;
				Str.push(" wabbit!");
				std::cout << "Str = " << Str.hptr << std::endl;
				text StrTemp = Str.split_at("brown");
				std::cout << "StrTemp = " << StrTemp.hptr << std::endl;
				std::cout << "Str = " << Str.hptr << std::endl;
				Str.permute(-4);
				std::cout << "Str = " << Str.hptr << std::endl;

				text Str3 = "";
				Str3.push('a');
				Str3.push('b');
				std::cout << "Str3 = " << Str3.hptr << std::endl;
				Str3.pop();
				Str3.push('\a'); // Angery computer noises
				std::cout << "Str3 = " << Str3.hptr << std::endl;
				Str3.insert(1, 'f');
				std::cout << "Str3 = " << Str3.hptr << std::endl;
				Str3.remove(0);
				std::cout << "Str3 = " << Str3.hptr << std::endl;
				Str3.push("hello");
				std::cout << "Str3 = " << Str3.hptr << std::endl;
				Str3.exchange(2, 3);
				std::cout << "Str3 = " << Str3.hptr << std::endl;

				float Simple = FLT_MAX;
				printf("Original Float:   %f\n", Simple);
				text Txt = text("%f", Simple);
				printf("String Float:    \"%s\"\n", Txt.str());
				float NewSimple = (float)atof(Txt.str());
				printf("Converted Float:  %f\n", NewSimple);

				float LeftMotor = 3.14;
				const char* Name = "Left Motor";
				text Send = text("%s|%+4.3e", Name, LeftMotor);
				printf("Send Message: \"%s\"\n", Send.str());
				text RecvName = Send.split_at('|');
				printf("\"%s\"\t\"%s\"\n", RecvName.str(), Send.str());
				printf("%s Value: %f\n", RecvName.str(), (float)atof(Send.str()));

			}
#endif // TEXT_DEBUG

		}
	}
}

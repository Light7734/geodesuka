CXX = g++
OPT = 
INC = '-I/Program Files (x86)/IntelSWTools/system_studio_2020/OpenCL/sdk/include' -Iinc -Idep/glfw/inc -Idep/glad/inc
LIB = 
SRC = src

all:
	$(CXX) $(OPT) $(INC) $(LIB) %(SRC) main.cpp -o main.exe
CXX = g++
OPT = -std=c++17 -pthread -c
INC = -I./inc -Idep/glfw/inc -Idep/glad/inc
LIB = 
SRC = src/

geodesuka:
	$(CXX) $(OPT) $(INC) $(LIB) %(SRC) main.cpp -o main.exe
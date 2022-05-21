cd obj
g++ -std=c++17 -pthread -c ../src/*.cpp -I./../inc/ -lglslang -lvulkan -lglfw -lGL -lXrandr -lX11 -lrt -ldl

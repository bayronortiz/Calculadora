
# Compilador y flags
CXX=	g++
CXXFLAGS=	-W	-Wall	-std=c++11

#Directorios
INCLUDE= include
SRC=	src/

all:
	$(CXX) $(CXXFLAGS) -I$(SRC)	main.cpp -o Calculadora

CXX = g++
CXXFLAGS = -Wall -g
LIBS = -lncurses

main: main.o
	$(CXX) $(CXXFLAGS) -o app main.o $(LIBS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm main *.o
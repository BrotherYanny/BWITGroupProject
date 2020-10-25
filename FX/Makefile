run: build
	./engi
	
build: FX.o Test.o
	g++ -std=c++17 -o engi Test.o FX.o

Test.o: Test.cpp
	g++ -std=c++17 -c Test.cpp

FX.o: FX.cpp
	g++ -std=c++17 -c FX.cpp

clean:
	rm engi *.o
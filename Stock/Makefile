run: build
	./engi
	
build: Stock.o Test.o
	g++ -std=c++17 -o engi Test.o Stock.o

Test.o: Test.cpp
	g++ -std=c++17 -c Test.cpp

Stock.o: Stock.cpp
	g++ -std=c++17 -c Stock.cpp

clean:
	rm engi *.o
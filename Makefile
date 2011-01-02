CXXFLAGS=-g -O0

debug: wakeit

release: CXXFLAGS=-O3
release: wakeit 

wakeit: main.o Wake.o ConfigFile.o
	g++ $(CXXFLAGS) -o wakeit $^

clean:
	rm -f *.o wakeit

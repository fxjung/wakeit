CXXFLAGS=-g -O0

debug: wakeit

release: CXXFLAGS=-O3
release:
	$(MAKE) clean
	$(MAKE) wakeit

wakeit: main.o Wake.o ConfigFile.o
	g++ $(CXXFLAGS) -o wakeit $^

install: release
	install -Ds -m 755 -o root -g root wakeit $(DESTDIR)/bin/wakeit

clean:
	rm -f *.o wakeit

# vim:noexpandtab:

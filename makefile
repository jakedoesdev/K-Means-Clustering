output: main.o config.o kmeans.o hierarchical.o dunindex.o
	g++ main.o config.o kmeans.o hierarchical.o dunindex.o -o output

main.o: main.cpp
	g++ -c main.cpp

config.o: config.cpp config.h
	g++ -c config.cpp

kmeans.o: kmeans.cpp kmeans.h
	g++ -c kmeans.cpp

hierarchical.o: hierarchical.cpp hierarchical.h
	g++ -c hierarchical.cpp

dunindex.o: dunindex.cpp dunindex.h
	g++ -c dunindex.cpp

clean:
	rm *.o output

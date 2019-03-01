
.PHONY: clean

.PHONY: all


all: main.o Node.o
	g++ main.o Node.o

clean:
	rm -vf main.o Node.o a.exe

main.o: main.cpp Node.h Adapter.h NodeMgr.h
	g++ -c main.cpp

Node.o: Node.cpp Node.h
	g++ -c Node.cpp
	
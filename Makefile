
.PHONY: clean

.PHONY: all


all: main.o Node.o NodeMgr.o
	g++ main.o NodeMgr.o Node.o

clean:
	rm -vf main.o NodeMgr.o Node.o a.exe

main.o: main.cpp Node.h Adapter.h NodeMgr.cpp NodeMgr.h
	g++ -c main.cpp

Node.o: Node.cpp Node.h
	g++ -c Node.cpp

NodeMgr.o: NodeMgr.cpp NodeMgr.h
	g++ -c NodeMgr.cpp
	
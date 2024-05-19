CC=g++
DEV=-Wall -g -std=c++14
OPT=-O3 -std=c++14
FLAGS=$(DEV)
JSON=json.hpp

all: buildheap.exe createteams.exe createteamdata.exe createheapoperationdata.exe

priorityqueue.o: priorityqueue.cpp priorityqueue.h
	$(CC) $(FLAGS) -c priorityqueue.cpp

teamdata.o: teamdata.cpp teamdata.h $(JSON)
	$(CC) $(FLAGS) -c teamdata.cpp

buildheap.exe: buildheap.cxx priorityqueue.o $(JSON)
	$(CC) $(FLAGS) buildheap.cxx priorityqueue.o -o buildheap.exe

createheapoperationdata.exe: createheapoperationdata.cxx priorityqueue.o $(JSON)
	$(CC) $(FLAGS) createheapoperationdata.cxx priorityqueue.o -o createheapoperationdata.exe

createteamdata.exe: createteamdata.cxx $(JSON)
	$(CC) $(FLAGS) createteamdata.cxx -o createteamdata.exe

createteams.exe: createteams.cxx priorityqueue.o teamdata.o $(JSON)
	$(CC) $(FLAGS) createteams.cxx priorityqueue.o teamdata.o -o createteams.exe

clean:
	rm -f *.o
	rm -f *.o3
	rm -f *.exe
	rm -rf *.exe.dSYM

update:
	make clean
	make all

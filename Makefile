CC = g++

CFLAGS = -Wall -std=c++11

RM = del

all: Builder.exe Factory.exe Singleton.exe Observer.exe CoR.exe iike.exe

Builder.exe: Builder.cpp
	$(CC) $(CFLAGS) Builder.cpp -o Builder.exe

Factory.exe: Factory.cpp
	$(CC) $(CFLAGS) Factory.cpp -o Factory.exe

Singleton.exe: Singleton.cpp
	$(CC) $(CFLAGS) Singleton.cpp -o Singleton.exe

Observer.exe: Observer.cpp
	$(CC) $(CFLAGS) Observer.cpp -o Observer.exe
	
CoR.exe: CoR.cpp
	$(CC) $(CFLAGS) CoR.cpp -o CoR.exe

iike.exe: iike.cpp
	$(CC) $(CFLAGS) iike.cpp -o iike.exe

clean: 
	$(RM) Builder.exe 
	$(RM) Factory.exe 
	$(RM) Singleton.exe 
	$(RM) Observer.exe
	$(RM) CoR.exe
	$(RM) iike.exe
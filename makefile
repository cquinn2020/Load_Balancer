# Makefile

CC = g++
CFLAGS = -std=c++17 -Wall -Wpedantic -g

all: simulation

simulation: simulation.o LoadBalancer.o WebServer.o Request.o
	$(CC) $(CFLAGS) -o simulation simulation.o LoadBalancer.o WebServer.o Request.o

simulation.o: simulation.cpp
	$(CC) $(CFLAGS) -c simulation.cpp

LoadBalancer.o: LoadBalancer.cpp
	$(CC) $(CFLAGS) -c LoadBalancer.cpp

WebServer.o: WebServer.cpp
	$(CC) $(CFLAGS) -c WebServer.cpp

Request.o: Request.cpp
	$(CC) $(CFLAGS) -c Request.cpp

clean:
	rm *.o simulation

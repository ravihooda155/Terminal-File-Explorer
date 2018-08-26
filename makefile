CC = g++
CFLAGS = -Wall -std=c++1z
DEPS = DirListing.h keyMovement.h
OBJ = DirListing.o keyMovement.o Project.o
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

Project: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^


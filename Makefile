SRC=src/p1.cpp src/Util.cpp src/MazeProblem.cpp src/CornersProblem.cpp src/AllFoodsMazeProblem.cpp src/Agent.cpp

INCLUDES=include/Util.h include/Problems.h include/MazeProblem.h include/CornersProblem.h include/AllFoodsMazeProblem.h include/Agent.h

CC=g++

CFLAGS=-g -Iinclude

p1: $(SRC) $(INCLUDES)
ifeq ($(NO_COLOR),1)
	$(CC) -D NO_COLORED_OUTPUT $(CFLAGS) -o p1 $(SRC)
else
	$(CC) $(CFLAGS) -o p1 $(SRC)
endif 

clean:
	rm p1

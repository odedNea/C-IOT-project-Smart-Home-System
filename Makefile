TARGET=tests

INC_PATH=../inc/

CC=gcc
CXXFLAGS=-g -pedantic -Wall -Wconversion -ldl -std=c++03
LDFLAGS=-lm -ldl  -pthread

CFLAGS += -I$(INC_PATH)

SRCS=$(wildcard *.cpp) $(wildcard *.c)
OBJS=$(SRCS:.cpp=.o) 

$(TARGET): depends $(OBJS)
	g++ $(OBJS) -o $(TARGET) $(LDFLAGS)

include depends

depends:
	$(CC) -MM -I$(INC_PATH) $(SRCS) > depends

clean:
	rm *.o $(TARGET) depends

run: $(TARGET)
	./$(TARGET)


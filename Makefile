CC = g++
CFLAGS = -c
TARGET = dasm

all: $(TARGET)

$(TARGET): main.o Dasm.o OpCode.o
	$(CC) main.o Dasm.o OpCode.o -o $(TARGET)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

Dasm.o: Dasm.cpp
	$(CC) $(CFLAGS) Dasm.cpp

OpCode.o: OpCode.cpp
	$(CC) $(CFLAGS) OpCode.cpp

clean:
	rm -f core *.o $(TARGET)

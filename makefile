CC = g++
CFLAGS = -o2 -Wall -g

all : Choi_Jaehyuk_assn5.o
	$(CC) $(CFLAGS) -o run $+
%.o : %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

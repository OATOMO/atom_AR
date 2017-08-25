#CC=g++
#CXXFLAGS += pkg-config opencv --cflags
#LDFLAGS += pdk-config opencv --libs

#SOURCE += test1.cpp

#all:
	#$(CC) '$(CXXFLAGS) $(LDFLAGS)' $(SOURCE) -o test.bin 
	


CC=g++
#CFLAGS+=-g
CFLAGS+=`pkg-config --cflags opencv` -I./
LDFLAGS+=`pkg-config --libs opencv` -lglut -lGL

PROG=bin
OBJS=main.o grab_info.o

.PHONY:	all clean
$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS) $(LDFLAGS)
	#$(CC) -g -o $(PROG).gdb $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CC) -c $(CFLAGS) $<

all: $(PROG)

clean:
	rm -f $(OBJS) $(PROG) *.o

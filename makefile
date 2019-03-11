CXX=g++
LD=g++
CFLAGS=-g -std=c++17
LFLAGS=-lsfml-system -lsfml-window -lsfml-graphics
OBJS=main.o camera.o edge.o
EXE=rend

all: $(OBJS)
	$(LD) $^ -o $(EXE) $(LFLAGS)

clean:
	rm -f $(OBJS)

%.o : %.cpp
	$(CXX) -c $< $(CFLAGS) -o $@

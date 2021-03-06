CXX=g++
LD=g++
CFLAGS=-std=c++17 -O2
LFLAGS=-lsfml-system -lsfml-window -lsfml-graphics
OBJS=main.o camera.o edge.o model.o face.o
EXE=rend

all: $(OBJS)
	$(LD) $^ -o $(EXE) $(LFLAGS)

clean:
	rm -f $(OBJS)

%.o : %.cpp
	$(CXX) -c $< $(CFLAGS) -o $@

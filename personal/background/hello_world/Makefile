CXX = g++
CXXFLAGS += `pkg-config --cflags gtkmm-4.0`
LDLIBS += `pkg-config --libs gtkmm-4.0`

BINS = program
OBJS = helloworld.o main.o

all: $(BINS)

program: $(OBJS)
	$(CXX) $^ $(LDLIBS) -o $@

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean :
	-rm *.out
	-rm *.o $(BINS)
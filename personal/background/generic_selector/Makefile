CXX = g++
CXXFLAGS += `pkg-config --cflags gtkmm-4.0`
LDLIBS += `pkg-config --libs gtkmm-4.0`

OUTFILE = generic_selector.out
OBJS = generic_selector.o main.o

all: $(OUTFILE)

$(OUTFILE): $(OBJS)
	$(CXX) $^ $(LDLIBS) -o $@

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean :
	-rm *.out
	-rm *.o

CXX = g++
CXXFLAGS += `pkg-config --cflags gtkmm-4.0`
LDLIBS += `pkg-config --libs gtkmm-4.0`

OUTFILE = demo_builder.out
OBJS = main.o

all: $(OUTFILE)

$(OUTFILE): $(OBJS)
	$(CXX) $^ $(LDLIBS) -o $@

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean :
	-rm *.out
	-rm *.o
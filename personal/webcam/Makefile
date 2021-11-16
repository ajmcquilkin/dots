CXX = g++
CXXFLAGS += `pkg-config --cflags libfreenect gl glu glut opencv4`
LDLIBS += `pkg-config --libs libfreenect gl glu glut opencv4`

OUTFILE = main.out
OBJS = mutex.o scoped_lock.o freenect_webcam.o main.o

all: $(OUTFILE)

$(OUTFILE): $(OBJS)
	$(CXX) $^ $(LDLIBS) -o $@ -pthread

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean :
	-rm *.out
	-rm *.o
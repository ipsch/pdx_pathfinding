CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		main.o

LIBS =

TARGET =	pdx_pathfinding.exe

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all: clean $(TARGET)

run : $(TARGET)
	./$(TARGET)

.PHONY : clean
clean:
	rm -f $(OBJS) $(TARGET)
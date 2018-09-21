CXXFLAGS =	-O2 -std=c++11 -g -Wall -fmessage-length=0

SRC := $(shell find src -type f -name \*.cpp)

OBJS := $(patsubst src/%,build/%,$(SRC:.cpp=.o))

LIBS =

#TARGET = pdx_pathfinding.exe

ifeq ($(OS),Windows_NT)
	TARGET = pdx_pathfinding.exe
endif

ifeq ($(shell uname), Linux)
	TARGET = pdx_pathfinding
endif






build/%.o: src/%.cpp
	@mkdir -p build
	$(CXX) -std=c++11 -g $(CXX_FLAGS) $(DEF_FLAGS) -I./include -c -o $@ $< 



all: clean $(TARGET)

status :
	@echo Version Git-repository : $(VERSION_STRING)
	@echo 
	@echo $(SRC)
	@echo $(OBJS)

$(TARGET): $(OBJS)
	$(CXX) -g -o $(TARGET) -I./include  $(OBJS) $(LIBS)

run : $(TARGET)
	./$(TARGET)

debug : $(TARGET)
	gdb $(TARGET)


./PHONY : plot
plot :
	./plot.sh



./PHONY : mem-check
mem-check : all
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --log-file="valgrind.log" -v --track-origins=yes ./$(TARGET)
	cat valgrind.log

.PHONY : clean
clean:
	rm -f $(OBJS) $(TARGET)
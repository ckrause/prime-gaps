CXXFLAGS=-O2 -g -Wall -fmessage-length=0 -std=c++14

OBJS=gaps.o

TARGET=gaps

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

run: $(TARGET)
	./$(TARGET)

all: run

clean:
	rm -f $(OBJS) $(TARGET)

CXX = g++
CXXFLAGS = -std=c++11 -I./include
SOURCES = src/main.cpp src/book.cpp src/data_handler.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = library_app

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

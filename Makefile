# Variables
CXX = g++
OBJS = Requester.o Change.o ChangeRequest.o Product.o Release.o UI.o StartUp.o ScenarioControl.o main.o
TARGET = program

# Default target
all: $(TARGET)

# Linking the final executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# Compiling source files to object files
Requester.o: Requester.cpp Requester.h
	$(CXX) -c Requester.cpp

Change.o: Change.cpp Change.h
	$(CXX) -c Change.cpp

ChangeRequest.o: ChangeRequest.cpp ChangeRequest.h
	$(CXX) -c ChangeRequest.cpp

Product.o: Product.cpp Product.h
	$(CXX) -c Product.cpp

Release.o: Release.cpp Release.h
	$(CXX) -c Release.cpp

UI.o: UI.cpp UI.h
	$(CXX) -c UI.cpp

StartUp.o: StartUp.cpp StartUp.h
	$(CXX) -c StartUp.cpp

ScenarioControl.o: ScenarioControl.cpp ScenarioControl.h
	$(CXX) -c ScenarioControl.cpp

main.o: main.cpp
	$(CXX) -c main.cpp

# Clean target to remove generated files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean

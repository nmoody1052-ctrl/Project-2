CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iinclude
campus: src/*.cpp include/*.h
	$(CXX) $(CXXFLAGS) src/*.cpp -o campus
clean:
	rm -f campus
CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall

SRC = $(wildcard src/*.cpp)
OUT = build/engine

all: $(OUT)

$(OUT): $(SRC)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)
CXX = g++
BUILD_DIR = build
SRC_DIR = src

TARGETS = dijkstra dial radix_heap

all: $(TARGETS)

dijkstra: $(SRC_DIR)/dijkstra.cpp
	$(CXX) $< -o $(BUILD_DIR)/$@

dial: $(SRC_DIR)/dial.cpp
	$(CXX) $^ -o $(BUILD_DIR)/$@

radix_heap: $(SRC_DIR)/radix_heap.cpp
	$(CXX) $< -o $(BUILD_DIR)/$@

.PHONY: clean
clean:
	rm -f $(BUILD_DIR)/*
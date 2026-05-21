CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -O2 -I./src

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = .

SOURCES = $(wildcard $(SRC_DIR)/*.cpp) \
          $(wildcard $(SRC_DIR)/components/*.cpp) \
          $(wildcard $(SRC_DIR)/factories/*.cpp) \
          $(wildcard $(SRC_DIR)/builder/*.cpp) \
          $(wildcard $(SRC_DIR)/core/*.cpp) \
          $(wildcard $(SRC_DIR)/storage/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))
TARGET = $(BIN_DIR)/computer_config

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean
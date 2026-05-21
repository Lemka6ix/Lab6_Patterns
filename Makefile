CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -O2 -I./src
LDFLAGS = -mconsole

OBJ_DIR = obj
TARGET = computer_config.exe

SOURCES = main.cpp \
          src/components/CPU.cpp \
          src/components/Cooling.cpp \
          src/components/GPU.cpp \
          src/components/Motherboard.cpp \
          src/components/PowerSupply.cpp \
          src/components/RAM.cpp \
          src/components/Storage.cpp \
          src/factories/DesktopFactory.cpp \
          src/factories/ServerFactory.cpp \
          src/factories/WorkstationFactory.cpp \
          src/builder/ComputerBuilder.cpp \
          src/builder/Director.cpp \
          src/core/PriceCatalog.cpp \
          src/storage/PresetStorage.cpp

# Для каждого исходника создаём .o в obj/ с сохранением подпапок
OBJECTS = $(addprefix $(OBJ_DIR)/, \
          main.o \
          components/CPU.o \
          components/Cooling.o \
          components/GPU.o \
          components/Motherboard.o \
          components/PowerSupply.o \
          components/RAM.o \
          components/Storage.o \
          factories/DesktopFactory.o \
          factories/ServerFactory.o \
          factories/WorkstationFactory.o \
          builder/ComputerBuilder.o \
          builder/Director.o \
          core/PriceCatalog.o \
          storage/PresetStorage.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/main.o: main.cpp
	@if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: src/%.cpp
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@if exist $(TARGET) del /Q $(TARGET)
	@if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)

.PHONY: all clean
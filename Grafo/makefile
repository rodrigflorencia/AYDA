CXX       ?= g++           
CXXFLAGS  := -std=c++17 -Wall -Wextra -O2
INCLUDES  := -IGrafo -IGrafo/Puntero -IGrafo/STL -I"Grafo/STL - mapa de mapa"

SRC_DIR   := Grafo
BUILD_DIR := build
BIN_DIR   := bin
TARGET    := $(BIN_DIR)/main

# Todos los .cpp dentro de Grafo/ (subcarpetas incluidas) — ignora STL/ y "STL - mapa de mapa/"
SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
OBJS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

# Compila cada .cpp preservando la estructura de carpetas dentro de build/
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all run clean

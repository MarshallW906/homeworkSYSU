CC := g++-4.8
FLAGS := -std=c++11 -Wall
INC_DIR := ./include/
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
INCLUDE := -I$(INC_DIR)

$(BIN_DIR)/main: $(BUILD_DIR)/AgendaUI.o $(BUILD_DIR)/AgendaService.o $(BUILD_DIR)/Storage.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Meeting.o $(BUILD_DIR)/Date.o
	@mkdir -p bin
	$(CC) $(FLAGS) $(INCLUDE) $^ ./$(SRC_DIR)/Agenda.cpp  -o $@ 

ggmain:
	$(CC) $(FLAGS) $(INCLUDE) -o ./fgmain ./src/main.cpp ./build/*.o

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp include/%.hpp
	@mkdir -p build
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

clean:
	@rm -rf ./bin
	@rm -rf ./build

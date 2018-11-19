CC		:= g++
C_FLAGS := -std=c++17 -Wall

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:= -l sqlite3

ifeq ($(OS),Windows_NT)
EXECUTABLE	:= matchMaker.exe
else
EXECUTABLE	:= matchMaker
endif

all: $(BIN)/$(EXECUTABLE)

clean:
	$(RM) $(BIN)/$(EXECUTABLE)

run: all
	./$(BIN)/$(EXECUTABLE)

install:
	install ./$(BIN)/$(EXECUTABLE) /usr/local/bin

uninstall:
	rm -rf /usr/local/bin/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*
	$(CC) $(C_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)
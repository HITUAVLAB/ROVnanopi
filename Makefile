#Set up directories

OBJ_DIR = obj
SRC_DIR = src
INC_DIR = inc
BIN_DIR = bin

# Define compilation flags  

CC = g++

.PHONY: clean

ROVnanopi : $(OBJ_DIR)/main.o\
	    $(OBJ_DIR)/serial.o\
	    $(OBJ_DIR)/timeout.o\
	    $(OBJ_DIR)/repeater.o\
	    $(OBJ_DIR)/pthread.o\
	    $(OBJ_DIR)/init.o\
	    $(OBJ_DIR)/help.o

	    $(CC) $(OBJ_DIR)/main.o $(OBJ_DIR)/serial.o $(OBJ_DIR)/init.o $(OBJ_DIR)/timeout.o $(OBJ_DIR)/repeater.o $(OBJ_DIR)/pthread.o $(OBJ_DIR)/help.o -o ROVnanopi -lpthread

$(OBJ_DIR)/repeater.o :$(SRC_DIR)/repeater.cpp $(INC_DIR)/repeater.h
	$(CC) -g -c $(SRC_DIR)/repeater.cpp -o $(OBJ_DIR)/repeater.o

$(OBJ_DIR)/pthread.o :$(SRC_DIR)/pthread.cpp $(INC_DIR)/pthread.h
	$(CC) -g -c $(SRC_DIR)/pthread.cpp -o $(OBJ_DIR)/pthread.o

$(OBJ_DIR)/timeout.o : $(SRC_DIR)/timeout.cpp $(INC_DIR)/timeout.h 
	$(CC) -g -c $(SRC_DIR)/timeout.cpp -o $(OBJ_DIR)/timeout.o  

$(OBJ_DIR)/serial.o : $(SRC_DIR)/serial.cpp $(INC_DIR)/serial.h $(OBJ_DIR)/timeout.o
	$(CC) -g -c $(SRC_DIR)/serial.cpp -o $(OBJ_DIR)/serial.o  

$(OBJ_DIR)/main.o : $(SRC_DIR)/main.cpp $(OBJ_DIR)/serial.o  $(OBJ_DIR)/init.o 
	$(CC) -g -c $(SRC_DIR)/main.cpp -o $(OBJ_DIR)/main.o

$(OBJ_DIR)/init.o :$(SRC_DIR)/init.cpp $(INC_DIR)/init.h
	$(CC) -g -c $(SRC_DIR)/init.cpp -o $(OBJ_DIR)/init.o

$(OBJ_DIR)/help.o :$(SRC_DIR)/help.cpp 
	$(CC) -g -c $(SRC_DIR)/help.cpp -o $(OBJ_DIR)/help.o

clean:
	rm ROVnanopi obj/*

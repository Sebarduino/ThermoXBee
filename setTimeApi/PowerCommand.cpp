#include "Arduino.h"
#include "PowerCommand.h"

PowerCommand::PowerCommand() {
	this->index = 0;
	this->iLine = 0;
}

void PowerCommand::add(char *command, typeFunc function) {
	this->commands = this->increaseArray(this->commands, this->index, command);
	this->functions = this->increaseArray(this->functions, this->index, function);
	this->index ++;
}

template<class T>
T* PowerCommand::increaseArray(T *array, int size, T cell) {
	T *arrayNew;
	T *arrayDelete;
	arrayNew = new T[size+1];
	for(int i=0;i<size;i++) {
		arrayNew[i] = array[i];
	}
	arrayNew[size] = cell;
	arrayDelete = array;
	if(size > 0) {
		delete arrayDelete;
	}
	return arrayNew;
}

char* PowerCommand::extractParam(char *line, int lastChar) {
	char *args = NULL;
	if(line[lastChar] == ' ') {
		int paramBegin = lastChar + 1;
		int paramLength = 0;
		while(line[paramBegin + paramLength] != '\0') {
			paramLength++;
		}
		paramLength++;
		args = new char[paramLength];
		for(int k=paramBegin;k<paramBegin+paramLength;k++) {
			args[k-paramBegin] = line[k];
		}
	}
	return args;
}

void PowerCommand::call(char *line) {
	bool found = false;
	int i,j;
	for(i=0;i<this->index;i++) {
		char *command = this->commands[i];
		j = 0;
		while(command[j] != '\0' && line[j] != ' ' && line[j] != '\0') {
			if(command[j] != line[j]) break;
			j++;
			if(command[j] == '\0' && (line[j] == ' ' || line[j] == '\0')) {
				found = true;
			}
		}
		if(found) break;
	}
	if(found) {
		functions[i](this->extractParam(line,j));
	}
}

void PowerCommand::listen() {
	if (Serial.available() > 0) {
		int inByte = Serial.read();
		if(inByte != -1 && this->iLine < MAX_SIZE_COMMAND) {
			this->line[this->iLine] = inByte;
			this->iLine ++;
		}
	} else if(this->iLine > 0) {
		this->line[this->iLine] = '\0';
		this->call(this->line);
		this->iLine = 0;
	}
	delay(20);
}

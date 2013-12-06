#ifndef POWERCOMMAND_H
#define POWERCOMMAND_H

#include "Arduino.h"

#define MAX_SIZE_COMMAND	80

typedef void (*typeFunc)(char*);

class PowerCommand {

public:
				PowerCommand();
	void		add(char *command, typeFunc function);
	void		listen();

private:
	int   		index;
	char 		**commands;
	typeFunc	*functions;
	int			iLine;
	char		line[MAX_SIZE_COMMAND+1];
	void		call(char *command);
	char* 		extractParam(char *line, int lastChar);
	
	template<class T>
		T* increaseArray(T *array, int size, T cell);
};


#endif

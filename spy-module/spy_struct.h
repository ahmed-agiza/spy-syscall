#ifndef SPY_STRUCT
#define SPY_STRUCT

#define MAX_PROCESS_NAME 64

struct spy_struct{
	int pid;
	char process_name[MAX_PROCESS_NAME];
	int number_of_ports;
};


#endif
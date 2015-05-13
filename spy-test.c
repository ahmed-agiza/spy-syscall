#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

#define MAX_PROCESS_NAME 64

struct spy_struct{
	long pid;
	long number_of_ports;
	char process_name[MAX_PROCESS_NAME];
};

int main(int argc, char **argv){
	struct spy_struct buf[10];
	long proc_spyed = syscall(314, buf, 10);
	int i = 0;
	if(proc_spyed>= 0){
		printf("Found %ld processes\n", proc_spyed);
		for(i = 0; i < proc_spyed; i++)
			printf("Process %s(%ld) is listening to %ld communication(s) ports.\n", buf[i].process_name, buf[i].pid, buf[i].number_of_ports);
	}else{
		printf("Error with code %ld\n", proc_spyed);
	}
	return 0;
}

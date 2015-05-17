#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/sched.h>
#include <linux/fdtable.h>
#include <linux/linkage.h>   
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/dcache.h>
#include <linux/net.h>
#include <asm/uaccess.h>

#define MAX_PROCESS_NAME 64

struct spy_struct{
	long pid;
	long number_of_ports;
	char process_name[MAX_PROCESS_NAME];
};

asmlinkage long sys_spy(struct spy_struct __user *spy_buf, long num_proc){
	struct task_struct *task;
	struct socket *sock;
	long i, num_sockets, p_count = 0;
	int socket_error = 0;
	struct spy_struct *spys = (struct spy_struct *) kmalloc(num_proc * sizeof(struct spy_struct), GFP_KERNEL);

	printk("Spy start!\n");
	if (num_proc > 0)
		for_each_process(task){

			if(p_count >= num_proc){
				printk(KERN_ALERT "Reached maximum number of queries.\n");
				break;
			}

			if(task != NULL){
				num_sockets = 0;
				i = 0;
				socket_error = 0;

				while(task->files->fd_array[i] != NULL) {
					if(S_ISSOCK(task->files->fd_array[i]->f_inode->i_mode)){
						sock = sock_from_file(task->files->fd_array[i], &socket_error);
						if(!socket_error && sock->type == SOCK_STREAM){
							num_sockets++;
						}
					}				
					i++;
				}

				if(num_sockets > 0 && p_count < num_proc){
					spys[p_count].pid = task->pid;
					strcpy(spys[p_count].process_name, task->comm);
					spys[p_count].number_of_ports = num_sockets;
					p_count++;
				}
			}
			
		}


	for(i = 0; i < p_count; i++){
		printk(KERN_ALERT "Process %s(%ld) is listening to %ld communication port(s).\n", spys[i].process_name, spys[i].pid, spys[i].number_of_ports);
	}

	printk(KERN_ALERT "Stated %ld listening processes.\n", p_count);

	if(access_ok(VERIFY_WRITE, spy_buf, num_proc * sizeof(struct spy_struct))){
		if(!copy_to_user(spy_buf, spys, num_proc * sizeof(struct spy_struct))){
			printk(KERN_ALERT "Copy success!\n");
		}else{
			kfree(spys);
			printk(KERN_ALERT "Cannot copy to user memory.\n");
			return -2;
		}
	}else{
		kfree(spys);
		printk(KERN_ALERT "Cannot access user memory.\n");
		return -1;
	}

	kfree(spys);
	return p_count;
}


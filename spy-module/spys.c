#include <linux/module.h>    
#include <linux/kernel.h>    
#include <linux/init.h>      
#include <linux/printk.h>
#include <linux/sched.h>
#include <linux/fdtable.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/dcache.h>
#include <linux/stat.h>
#include <linux/net.h>
#include <net/sock.h>

#include "spy_struct.h"


static int in_pid = 0;
module_param(in_pid, int,  S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(in_pid, "Input process ID");

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ahmed Agiza & Mohammed R. Anany");
MODULE_DESCRIPTION("Prototype module for spy syscall");

static int __init spys_init(void){

	struct files_struct *task_files;
	struct fdtable *files_table;
	struct task_struct *task;
	struct socket *sock;
	int i, socket_error, num_sockets;
	struct path files_path;
	char *cwd;
	char *buf = (char *)kmalloc(100 * sizeof(char), GFP_KERNEL);
	struct spy_struct result;
	

	printk("Spy!");

	if(in_pid > 0){

		task = pid_task(find_vpid(in_pid), PIDTYPE_PID);
		if(task != NULL){
			task_files = task->files;
			files_table = files_fdtable(task_files);
			num_sockets = 0;
			i = 0;
			socket_error = 0;
			result.pid = task->pid;
			strcpy(result.process_name, task->comm);
			while(files_table->fd[i] != NULL) {
				files_path = files_table->fd[i]->f_path;
				cwd = d_path(&files_path, buf, 100 * sizeof(char));
				if(S_ISSOCK(files_table->fd[i]->f_path.dentry->d_inode->i_mode)){
					sock = sock_from_file(files_table->fd[i], &socket_error);
					if(!socket_error){
						num_sockets++;
					}
				}				
				i++;
			}
			result.number_of_ports = num_sockets;
			if(num_sockets > 0){
				printk(KERN_ALERT "Process %s(%d) is listening to %d communication port(s)\n", task->comm, task->pid, num_sockets);
			}else
				printk(KERN_ALERT "Process %s(%d) is not listening to any communication ports\n", task->comm, task->pid);

		}

		return 0;
	}
	
	return -1;
}

static void __exit spys_cleanup(void){
    printk(KERN_INFO "Cleaning up spy module.\n");
}

module_init(spys_init);
module_exit(spys_cleanup);

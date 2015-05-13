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
#include <linux/string.h>
#include <net/sock.h>
#include <asm/uaccess.h>

#define MAX_PROCESS_NAME 64

struct spy_struct{
	long pid;
	char process_name[MAX_PROCESS_NAME];
	long number_of_ports;
};


static long num_proc = 0;
module_param(num_proc, long,  S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(num_proc, "Number of processes to query");


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ahmed Agiza & Mohammed R. Anany");
MODULE_DESCRIPTION("Prototype module for spy syscall");

static int __init spy_init(void){

	struct files_struct *task_files;
	struct fdtable *files_table;
	struct task_struct *task;
	struct socket *sock;
	int socket_error;
	long i, num_sockets;
	struct path files_path;
	char *cwd;
	struct spy_struct *spys = (struct spy_struct *) kmalloc(num_proc * sizeof(struct spy_struct), GFP_KERNEL);
	char *buf = (char *)kmalloc(100 * sizeof(char), GFP_KERNEL);
	long p_count = 0;

	printk("Spy start!");
	if (num_proc > 0)
		for_each_process(task){

			if(p_count >= num_proc){
				printk(KERN_ALERT "Reached maximum number of queries.");
				break;
			}

			if(task != NULL){
				task_files = task->files;
				files_table = files_fdtable(task_files);
				num_sockets = 0;
				i = 0;
				socket_error = 0;

				while(files_table->fd[i] != NULL) {
					files_path = files_table->fd[i]->f_path;
					cwd = d_path(&files_path, buf, 100 * sizeof(char));
					if(S_ISSOCK(files_table->fd[i]->f_path.dentry->d_inode->i_mode)){
						sock = sock_from_file(files_table->fd[i], &socket_error);
						if(!socket_error){
							if(sock->type == SOCK_STREAM)
								num_sockets++;
							else
								printk("%s S: %d\n", task->comm, sock->type);
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
		printk(KERN_ALERT "Process %s(%ld) is listening to %ld communication port(s)\n", spys[i].process_name, spys[i].pid, spys[i].number_of_ports);
	}

	printk(KERN_ALERT "Stated %ld listening processes", p_count);

	kfree(spys);

	return 0;
}

static void __exit spy_cleanup(void){
    printk(KERN_INFO "Cleaning up spy module.\n");
}

module_init(spy_init);
module_exit(spy_cleanup);
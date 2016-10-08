#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/sched.h>

void __attribute__((weak)) arch_report_meminfo(struct seq_file *m) {}

static int wfvm_proc_show(struct seq_file *m, void *v)
{
	seq_printf(m, 
		"---------------------------------------------------\n"
		"Universidad de San Carlos de Guatemala\n"
		"Facultad de Ingenieria\n"
		"Sistemas Operativos 1\n"
		"Segundo Semestre 2016\n"
		"Seccion B\n"
		"Proyecto Fase 1\n"
		"\t< William Fernando Valladares Muñoz >\n"
		"\t\t    < 201314510 >\n"
		"---------------------------------------------------\n"
		"Sistema Operativo:\t< Manjaro 16.08 64-bits >\n"	
		"---------------------------------------------------\n"
		"PID 	Nombre			Estado\n"
		"---------------------------------------------------\n",
		(long unsigned int)0
	);

	struct task_struct *task;

	for_each_process(task)
	{
		int e = -1;
		char *estado;

		switch(task->state){
			case 0:

				if(task->comm)
				estado = "Running";
				break;
			case 1:
				estado = "Interruptible";
				break;
			case 2:
				estado = "Uninterruptible";
				break;
			case 3:
				estado = "Zombie";
				break;
			case 4:
				estado = "Stopped";
				break;
			case 5:
				break;
		}

		//Para imprimirlos en parejo
		int size_nombre = strlen(task->comm);

		if(size_nombre < 6){
			seq_printf(m,
				"%d \t %s \t\t\t %s\n", task->pid, task->comm, estado
			);			
		}else if(size_nombre < 14){
			seq_printf(m,
				"%d \t %s \t\t %s\n", task->pid, task->comm, estado
			);	
		}else{
			seq_printf(m,
				"%d \t %s \t %s\n", task->pid, task->comm, estado
			);
		}
	}

	seq_printf(m, 
		"---------------------------------------------------\n",
		(long unsigned int)0
	);

	return 0;
}

static int 
wfvm_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, wfvm_proc_show, NULL);
}

static const struct file_operations wfvm_proc_fops = {
	.owner		= THIS_MODULE,
	.open		= wfvm_proc_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int __init 
wfvm_proc_init(void)
{
	printk(KERN_INFO "WFVM_Procesos loaded successfully!\n\n");
	proc_create("WFVM_Procesos", 0, NULL, &wfvm_proc_fops);
	return 0;
}

static void __exit 
wfvm_proc_exit(void)
{
	printk(KERN_INFO "WFVM_Procesos unloaded successfully!\n\n");
	remove_proc_entry("WFVM_Procesos", NULL);
}

module_init(wfvm_proc_init);
module_exit(wfvm_proc_exit);

MODULE_AUTHOR("201314510 William Fernando Valladares Muñoz");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Modulito de SOPES1");
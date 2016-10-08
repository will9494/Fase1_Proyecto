#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#include <linux/mman.h>
#include <linux/mmzone.h>
#include <linux/quicklist.h>
#include <linux/swap.h>
#include <linux/vmstat.h>
#include <linux/atomic.h>
#include <linux/vmalloc.h>

void __attribute__((weak)) arch_report_meminfo(struct seq_file *m)
{
}

static int wfvm_proc_show(struct seq_file *m, void *v)
{
	#define K(x) ((x) << (PAGE_SHIFT - 10))
		struct sysinfo i;
		si_meminfo(&i);
		seq_printf(m, 
			"----------------------------------------------\n"
			"Universidad de San Carlos de Guatemala\n"
			"Facultad de Ingenieria\n"
			"Sistemas Operativos 1\n"
			"Segundo Semestre 2016\n"
			"Seccion B\n"
			"Proyecto Fase 1\n"
			"\t< William Fernando Valladares Muñoz >\n"
			"\t\t    < 201314510 >\n"
			"----------------------------------------------\n"
			"Sistema Operativo:\t< Manjaro 16.08 64-bits >\n"	
			"MemTotal:\t\t< %8lu kB >\n"
			"MemFree:\t\t< %8lu kBZ >\n"
			"----------------------------------------------\n",
			K(i.totalram),
			K(i.freeram)
		);

		return 0;
	#undef K
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
	printk(KERN_INFO "WFVM_Memoria loaded successfully!\n\n");
	proc_create("WFVM_Memoria", 0, NULL, &wfvm_proc_fops);
	return 0;
}

static void __exit 
wfvm_proc_exit(void)
{
	printk(KERN_INFO "WFVM_Memoria unloaded successfully!\n\n");
	remove_proc_entry("WFVM_Memoria", NULL);
}

module_init(wfvm_proc_init);
module_exit(wfvm_proc_exit);

MODULE_AUTHOR("201314510 William Fernando Valladares Muñoz");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Modulito de SOPES1");
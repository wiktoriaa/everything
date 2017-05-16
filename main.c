#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>

static struct task_struct *tp;
static struct task_struct *ptp;

static void print_state(struct task_struct *tp)
{
	if (tp->state == 0)
		printk(KERN_INFO "RUNNABLE\n");
	else if (tp->state > 0)
		printk(KERN_INFO "STOPPED\n");
	else if (tp->state < 0)
		printk(KERN_INFO "UNRUNNABLE\n");
}

static int __init startmod(void)
{
	printk(KERN_INFO "Current process pid: %d", current->pid);
	printk(KERN_INFO "State: %ld\n", current->state);
	print_state(current);
	tp = current;
	ptp = current;
	while(tp->pid >1){
		tp = tp->real_parent;
		printk(KERN_INFO "Parent of %d is: %d\n", ptp->pid, tp->pid);
		printk(KERN_INFO "State of %d is: %ld\n", tp->pid, tp->state);
		print_state(tp);
		ptp = tp;
	}	
	return 0;
}

static void __exit exitmod(void)
{
	
}

module_init(startmod);
module_exit(exitmod);
MODULE_LICENSE("GPL");

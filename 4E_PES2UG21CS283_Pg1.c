#include <linux/sched/signal.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
MODULE_LICENSE("GPL");
void tree(struct task_struct *task, int indent) 
{
    struct task_struct *child;
    struct list_head *list;
    int i;
    for (i = 0; i < indent; i++) 
    {
        printk(KERN_CONT "\t");
    }
    printk(KERN_CONT "|--Name: %s Process ID: %d State: %u\n", task->comm, task->pid, task->state);
    list_for_each(list, &task->children) 
    {
        child = list_entry(list, struct task_struct, sibling);
        tree(child, indent + 1);
    }
}
static int tree_init(void) 
{
	printk(KERN_INFO "Listing all processes in tree structure:\n");
	tree(&init_task, 0);
	return 0;
}
static void tree_exit(void) 
{
	printk(KERN_INFO "Finished listing all processes in tree structure!");	
}
module_init(tree_init);
module_exit(tree_exit);


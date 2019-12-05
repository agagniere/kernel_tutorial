#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>

MODULE_DESCRIPTION("Lists processes, their PID and executable name.");
MODULE_AUTHOR("Antoine GAGNIERE");
MODULE_LICENSE("MIT");

static int __init agagniere_init(void)
{
	struct task_struct* task;
	struct list_head*   tasks;
	struct list_head*   ptr;

	tasks = current->tasks.prev;
	list_for_each(ptr, tasks)
	{
		task = list_entry(ptr, struct task_struct, tasks);
		pr_info("Process #%i \"%s\"", task->pid, task->comm);
	}
	pr_info("Loading module \"%s\"\n", THIS_MODULE->name);
	return 0;
}

static void rec_print_parent(struct task_struct* task)
{
	if (task->pid)
		rec_print_parent(task->parent);
	pr_info("Process #%i \"%s\"", task->pid, task->comm);
}

static void __exit agagniere_exit(void)
{
	rec_print_parent(current);
	pr_info("Unloading module \"%s\"\n", THIS_MODULE->name);
}

module_init(agagniere_init);
module_exit(agagniere_exit);

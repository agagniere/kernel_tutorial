#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>

MODULE_DESCRIPTION("Displays the list of modules, and various informations when available");
MODULE_AUTHOR("Antoine GAGNIERE");
MODULE_LICENSE("MIT");

static const char* states_str[] = {"Alive", "Coming", "Going", "Unformed"};

static int __init agagniere_init(void)
{
	struct list_head* ptr;
	struct list_head* head;
	struct module*    mod;

	pr_info("Loading module \"%s\"", THIS_MODULE->name);
	head = THIS_MODULE->list.prev;
	list_for_each(ptr, head)
	{
		mod = list_entry(ptr, struct module, list);
		pr_info("\tFound module \"%s\", state: %s, exports %u symbols, has %u kernel parameters.",
			mod->name, states_str[mod->state], mod->num_syms, mod->num_kp);
		if (mod->version)
			pr_info("\t\tversion: %s", mod->version);
		if (mod->srcversion)
			pr_info("\t\tsrcversion: %s", mod->srcversion);
		if (mod->exit)
			pr_info("\t\trefcnt: %i", mod->refcnt.counter);
	}
	return 0;
}

static void __exit agagniere_exit(void)
{
	pr_info("Unloading module \"%s\"", THIS_MODULE->name);
}

module_init(agagniere_init);
module_exit(agagniere_exit);

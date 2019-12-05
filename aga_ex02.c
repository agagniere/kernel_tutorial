#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>

void agagniere_foo(void);

typedef struct aga_env t_aga_env;
struct aga_env
{
	struct list_head super;
	int              data;
};

t_aga_env* toto;

static int __init agagniere_init(void)
{
	t_aga_env* tmp;

	pr_info("Loading module \"%s\"", THIS_MODULE->name);
	agagniere_foo();

	toto = kmalloc(sizeof(struct aga_env), GFP_KERNEL);
	toto->super = (struct list_head){&toto->super, &toto->super};
	toto->data = 7;

	tmp = toto;
	while (tmp->data)
	{
		tmp->super.next = kmalloc(sizeof(t_aga_env), GFP_KERNEL);
		((t_aga_env*)tmp->super.next)->data = tmp->data - 1;
		tmp->super.next->prev = (void*)tmp;
		tmp = (t_aga_env*)tmp->super.next;
		tmp->super.next = (void*)toto;
		toto->super.prev = (void*)tmp;
	}
	return 0;
}

static void __exit agagniere_exit(void)
{
	struct list_head* tmp;
	struct list_head* ptr;
	t_aga_env*        aga_ptr;

	pr_info("Unloading module \"%s\"", THIS_MODULE->name);
	list_for_each_safe(ptr, tmp, ((struct list_head*)toto))
	{
		aga_ptr = (t_aga_env*)ptr;
		pr_info("Removing %i", aga_ptr->data);
		kfree(ptr);
	}
	pr_info("Removing %i", toto->data);
	kfree(toto);
}

module_init(agagniere_init);
module_exit(agagniere_exit);

MODULE_DESCRIPTION("Tests kernel lists");
MODULE_AUTHOR("Antoine GAGNIERE");
MODULE_LICENSE("MIT");

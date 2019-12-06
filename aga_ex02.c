#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/list.h>

void agagniere_foo(void);

typedef struct aga_env t_aga_env;
struct aga_env
{
	struct list_head super;
	int              data;
};

static t_aga_env my_list;

static int __init agagniere_init(void)
{
	t_aga_env* tmp;
	int        i;

	pr_info("Loading module \"%s\"", THIS_MODULE->name);
	agagniere_foo();

	my_list = (t_aga_env){
		.super = LIST_HEAD_INIT(my_list.super),
		.data = 7
	};
	i = 0;
	while (i < my_list.data)
	{
		tmp = kmalloc(sizeof(t_aga_env), GFP_KERNEL);
		tmp->data = i++;
		list_add(&tmp->super, &my_list.super);
	}
	return 0;
}

static void __exit agagniere_exit(void)
{
	struct list_head* tmp;
	struct list_head* ptr;
	t_aga_env*        aga_ptr;

	pr_info("Unloading module \"%s\"", THIS_MODULE->name);
	list_for_each_safe(ptr, tmp, &my_list.super)
	{
		aga_ptr = (t_aga_env*)ptr;
		pr_info("Removing %i", aga_ptr->data);
		kfree(ptr);
	}
}

module_init(agagniere_init);
module_exit(agagniere_exit);

MODULE_DESCRIPTION("Tests kernel lists");
MODULE_AUTHOR("Antoine GAGNIERE");
MODULE_LICENSE("MIT");

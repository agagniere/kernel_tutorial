#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>

char* parameter;
module_param(parameter, charp, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(parameter, " A string that will be displayed on load.");

static int __init agagniere_init(void)
{
	pr_info("Loading module \"%s\" with parameter \"%s\"", THIS_MODULE->name, parameter);
	return 0;
}

void agagniere_foo(void)
{
	pr_info("Calling %s in module %s", __FUNCTION__, THIS_MODULE->name);
}

static void __exit agagniere_exit(void)
{
	pr_info("Unloading module \"%s\"", THIS_MODULE->name);
}

module_init(agagniere_init);
module_exit(agagniere_exit);

EXPORT_SYMBOL(agagniere_foo);

MODULE_DESCRIPTION("Prints the module name");
MODULE_AUTHOR("Antoine GAGNIERE");
MODULE_LICENSE("MIT");

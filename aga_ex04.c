#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/moduleparam.h>


MODULE_DESCRIPTION("Tests kernel oops and debug");
MODULE_AUTHOR("Antoine GAGNIERE");
MODULE_LICENSE("MIT");
MODULE_PARM_DESC(parameter, " String telling the module what to do.");

char* parameter = NULL;
module_param(parameter, charp, S_IRUGO | S_IWUSR);

static int ft_strncmp(const char *s1, const char *s2, unsigned n)
{
	while (n-- > 0)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		else if (*s1 == '\0')
			return (0);
		s1++;
		s2++;
	}
	return (0);
}

static int __init agagniere_init(void)
{
	pr_info("Loading module \"%s\" with parameter \"%s\"", THIS_MODULE->name, parameter);
	if (!parameter)
		return -1;
	if (ft_strncmp(parameter, "WARN_ONCE", 9) == 0)
	{
		int n = 3;
		while (n --> 0)
			WARN_ONCE(42 == 21 * 2, "Will be displayed once");
	}
	else if (ft_strncmp(parameter, "WARN_ON", 8) == 0)
		WARN_ON(2 == 1 + 1);
	else if (ft_strncmp(parameter, "WARN", 5) == 0)
		WARN(1, "Brian is in the kitchen");
	else if (ft_strncmp(parameter, "BUG_ON", 6) == 0)
		BUG_ON(6 == 3 * 2);
	else if (ft_strncmp(parameter, "BUG", 4) == 0)
		BUG();
	else if (parameter[0] == '-')
		return (0 - (parameter[1] - '0'));
	return 0;
}

static void __exit agagniere_exit(void)
{
	pr_info("Unloading module \"%s\"", THIS_MODULE->name);
}

module_init(agagniere_init);
module_exit(agagniere_exit);

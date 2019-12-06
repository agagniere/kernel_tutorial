#include <linux/module.h>
#include <linux/init.h>
#include <linux/mmzone.h>

MODULE_DESCRIPTION("Display information about the memory");
MODULE_AUTHOR("Antoine GAGNIERE");
MODULE_LICENSE("MIT");

static void print_zone(struct zone* zone)
{
	pr_info("\tZone \"%s\"\n\t{", zone->name);
	pr_info("\t\tSpanned pages: %lu", zone->spanned_pages);
	pr_info("\t\tPresent pages: %lu", zone->present_pages);
	pr_info("\t\tManaged pages: %lu", zone_managed_pages(zone));
	pr_info("\t\tIs initialized? %s", zone_is_initialized(zone) ? "yes" : "no");
	pr_info("\t}\n");
}

static void print_pagelistdata(pg_data_t* pagelist)
{
	int zone;

	pr_info("Page list #%i\n{", pagelist->node_id);
	pr_info("\tReserved pages: %li", pagelist->totalreserve_pages);
	pr_info("\tNR zones: %i\n", pagelist->nr_zones);
	zone = 0;
	while (zone < pagelist->nr_zones)
	{
		print_zone(pagelist->node_zones + zone);
		zone++;
	}
	pr_info("}\n");
}

static int __init agagniere_init(void)
{
	pr_info("Loading module \"%s\"\n", THIS_MODULE->name);
	print_pagelistdata(*node_data);
	return 0;
}

static void __exit agagniere_exit(void)
{
	pr_info("Unloading module \"%s\"\n", THIS_MODULE->name);
}

module_init(agagniere_init);
module_exit(agagniere_exit);

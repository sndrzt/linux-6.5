#include <linux/init.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>

struct item {
	int id;
	struct list_head list;
};

static int __init test_list_init(void)
{
	printk(KERN_ALERT "test_list_init.\n");

	struct list_head itm_lst = {&itm_lst, &itm_lst}; /* INIT_LIST_HEAD */

	struct item a = { .id = 1 }; INIT_LIST_HEAD(&a.list); list_add(&a.list, &itm_lst);
	struct item b = { .id = 2 }; INIT_LIST_HEAD(&b.list); list_add(&b.list, &itm_lst);
	struct item c = { .id = 3 }; INIT_LIST_HEAD(&c.list); list_add(&c.list, &itm_lst);

	struct item *p;
	list_for_each_entry(p, &itm_lst, list) {
		printk(KERN_ALERT "id: %d\n", p->id);
	}

	list_del(&b.list);

	list_for_each_entry(p, &itm_lst, list) {
		printk(KERN_ALERT "id: %d\n", p->id);
	}
	
	list_for_each_entry_reverse(p, &itm_lst, list) {
		printk(KERN_ALERT "id: %d\n", p->id);
	}
	
	p = container_of(&c.list, struct item, list);
	printk(KERN_ALERT "ID: %d\n", p->id);

	return 0;
}

static void __exit test_list_exit(void)
{
	printk("test_list_exit.\n");
}

module_init(test_list_init);
module_exit(test_list_exit);

MODULE_LICENSE("GPL v2");


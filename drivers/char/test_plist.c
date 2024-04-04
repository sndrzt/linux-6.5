#include <linux/init.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/plist.h>

//static struct plist_head *swap_avail_heads;

struct swap_info_struct {
	int id;
	struct plist_node avail_lists;
};

static int __init test_llist_init(void)
{
	printk("test_llist_init.\n");

	struct plist_head swap_active_head = PLIST_HEAD_INIT(swap_active_head);

	if (plist_head_empty(&swap_active_head))
		printk("plist empty.\n");

	struct swap_info_struct *a;
	a = kmalloc(sizeof(struct swap_info_struct), GFP_KERNEL);
	a->id = 1; a->avail_lists.prio = 5; plist_node_init(&a->avail_lists, 0);
	plist_add(&a->avail_lists, &swap_active_head);

	struct swap_info_struct *b;
	b = kmalloc(sizeof(struct swap_info_struct), GFP_KERNEL);
	b->id = 2; b->avail_lists.prio = 5; plist_node_init(&b->avail_lists, 0);
	plist_add(&b->avail_lists, &swap_active_head);

	struct swap_info_struct *c;
	c = kmalloc(sizeof(struct swap_info_struct), GFP_KERNEL);
	c->id = 3; c->avail_lists.prio = 7; plist_node_init(&c->avail_lists, 0);
	plist_add(&c->avail_lists, &swap_active_head);

	plist_del(&a->avail_lists, &swap_active_head);

	struct swap_info_struct *p = NULL;
	plist_for_each_entry(p, &swap_active_head, avail_lists) {
		printk("id: %d.\n", p->id);
	}

	return 0;
}

static void __exit test_llist_exit(void)
{
	printk("test_llist_exit.\n");
}

module_init(test_llist_init);
module_exit(test_llist_exit);

MODULE_LICENSE("GPL v2");


#include <linux/init.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>

struct i915_gem_mm {
	struct llist_head free_list;
};

struct drm_i915_gem_object {
	int id;
	struct llist_node freed;
};

static int __init test_llist_init(void)
{
	printk("test_llist_init.\n");

	struct i915_gem_mm mm;

	init_llist_head(&mm.free_list);

	struct drm_i915_gem_object a; a.id = 1; llist_add(&a.freed, &mm.free_list);
	struct drm_i915_gem_object b; b.id = 2; llist_add(&b.freed, &mm.free_list);
	struct drm_i915_gem_object c; c.id = 3; llist_add(&c.freed, &mm.free_list);

	struct drm_i915_gem_object *obj;

	llist_for_each_entry(obj, mm.free_list.first, freed) {
		printk("id: %d\n", obj->id);
	}

	struct llist_node *freed = llist_del_first(&mm.free_list);
	struct drm_i915_gem_object *p = container_of(freed, struct drm_i915_gem_object, freed);
	
	printk("ID: %d\n", p->id);

	return 0;
}

static void __exit test_llist_exit(void)
{
	printk("test_llist_exit.\n");
}

module_init(test_llist_init);
module_exit(test_llist_exit);

MODULE_LICENSE("GPL v2");


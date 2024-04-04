//#include "kn_common.h"
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/kernel.h>
//#include <linux/list.h>
#include <linux/idr.h>

struct student 
{
	int id;
	char *name;
};

static int print_student(int,void*,void*);

static int testidr_init(void)
{
	DEFINE_IDR(idp);
	struct student *stu[4];

	int id,ret,i;
	
	for(i=0;i<4;i++)
	{
		stu[i] = kmalloc(sizeof(struct student),GFP_KERNEL);
		stu[i]->id = i;
		stu[i]->name = "laoyl";
	}
	
	//print_current_time(1);
	for(i=0;i<4;i++)
	{
		do{
			if(!idr_pre_get(&idp,GFP_KERNEL))
				return -ENOSPC;
			ret = idr_get_new(&idp,stu[i],&id);
			printk("id=%d\n",id);
		}while(ret == -EAGAIN);
	}
	/* delete */
	idr_remove(&idp,1);
	/* find */
	print_student(0,idr_find(&idp,2),NULL);
	
	/* each */
	idr_for_each(&idp,print_student,(void *)"hello");
	
	idr_remove_all(&idp);
	idr_destroy(&idp);
	for(i=0;i<4;i++)
	{
		kfree(stu[i]);
	}
	return 0;
}

static int print_student(int id,void *p,void *data)
{
	struct student *stu = p;

	printk("====================\n");
	printk("idr-id = %d\n",id);
	printk("idr-data = %s\n",(char*)data);
	print_current_time(1);
	printk("id = %d\n",stu->id);
	printk("name = %s\n",stu->name);
	printk("====================\n");
	return 0;
}

static void testidr_exit(void)
{
	printk("***************************\n");
	print_current_time(1);
	printk("testidr is exited!\n");
	printk("***************************\n");
}

module_init(testidr_init);
module_exit(testidr_exit);

MODULE_LICENSE("GPL v2");

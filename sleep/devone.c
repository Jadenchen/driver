#include <linux/sched.h>
#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("BSD");
static wait_queue_head_t wait;

static int sample_init(void)
{
	init_waitqueue_head(&wait);
	sleep_on(&wait);
	printk ("sample_init\n");

	return 0;
}

static void sample_exit(void)
{

	printk("sample_exit \n");
}

module_init(sample_init);
module_exit(sample_exit);

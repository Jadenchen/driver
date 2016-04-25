#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>

MODULE_LICENSE ("BSD");

extern wait_queue_head_t sample_wait;

static int wakeup_init(void)
{

	wait_queue_head_t *wq = &sample_wait;
	printk ("wakeup_init \n");

	wake_up(wq);
	return 0;

}

static void wakeup_exit (void)
{
	printk("wakeup_exit \n");
}

module_init(wakeup_init);
module_exit(wakeup_exit);
#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>

MODULE_LICENSE("BSD");

#define SLEEP_TIMEOUT (6*HZ)
#define WAKEUP_TIMEOUT (5*HZ)

static struct timer_list time;
static wait_queue_head_t wait;
static int condition = 0;

static void main_timeout (unsigned long arg)
{
	wait_queue_head_t *wq = (wait_queue_head_t *) arg;
	
	printk ("wq %p %s\n", wq, __func__);
	condition = 1;
	wake_up(wq);

}


static int main_init (void)
{
	long val;
	printk ("main init \n");
	init_waitqueue_head (&wait);
	init_timer(&time);
	time.function = main_timeout;
	time.data = (unsigned long) &wait;
	time.expires = jiffies+WAKEUP_TIMEOUT;
	add_timer(&time);

	condition = 0;
	val = wait_event_timeout (wait, condition, SLEEP_TIMEOUT);
	if (val == 0)
		printk ("timeour occured \n");
	printk ("main init finish \n");
	return 0;
}

static void main_exit (void)
{
	del_timer_sync(&time);
	printk ("main exit \n");
}

module_init(main_init);
module_exit(main_exit);
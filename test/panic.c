#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("BSD");

// void sub (int n)
// {
// 	char buf[8192];
// 	printk("%s n = %d \n", __func__, n);
// 	memset (buf, 0, sizeof (buf));
// }

int g __attribute__ ((unused));
const int g_2 __attribute__ ((unused));
static int g_3 __attribute__ ((unused));
int g_4 __attribute__ ((unused));
EXPORT_SYMBOL(g_4);


static int panic_init (void)
{
	printk ("panic init \n");

	return 0;
}



static void panic_exit(void)
{
	printk ("panic exit \n");
}


module_init(panic_init);
module_exit(panic_exit);
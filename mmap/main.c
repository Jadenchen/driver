#include <linux/init.h>
#include <linux/module.h>
#include <asm/io.h>

MODULE_LICENSE ("BSD");

static int sample_init(void)
{
	char *reg;
	printk("sample driver installed \n");

	reg = ioremap_nocache(0xFEC00000,4);
	if (reg != NULL){
		printk("%x\n", reg);
		iounmap(reg); // cancel ioremap
	}
	return 0;
}

static void sample_exit(void)
{
	printk("sample driver removed \n");
}

module_init(sample_init);
module_exit(sample_exit);
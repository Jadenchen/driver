#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/cdev.h>
#include <linux/err.h>
#include <linux/fs.h>


MODULE_LICENSE ("BSD");
static int devone_devs = 1;
static int devone_major = 0;
static struct cdev devone_cdev;

wait_queue_head_t sample_wait;
EXPORT_SYMBOL(sample_wait);


ssize_t devone_read (struct file *filp, char __user *buf, size_t count,
					loff_t *f_ops)
{
	int i;
	unsigned char val = 0xff;
	int retval;
	//initail wait queue
	init_waitqueue_head(&sample_wait);
	sleep_on(&sample_wait);

	printk("wake up %s \n", __func__);
	printk ("count %d \n", count);

	for (i = 0; i< count;i++){
		if (copy_to_user (&buf[i], &val, 1)){
			retval = -EFAULT;
			goto out;
		}
	}
	retval = count;

	out:
		return retval;
}

struct file_operations devone_ops = {
	.read = devone_read,
};

static int devone_init (void)
{
	dev_t dev = MKDEV (devone_major, 0);
	int ret;
	int major, err;

	ret = alloc_chrdev_region(&dev, 0, devone_devs, "devone");
	if (ret < 0){
		printk("alloc cdev failed \n");
		return -1;
	}

	devone_major = major = MAJOR(dev);

	cdev_init(&devone_cdev, &devone_ops);
	devone_cdev.owner = THIS_MODULE;
	devone_cdev.ops = &devone_ops;
	err = cdev_add (&devone_cdev, MKDEV(devone_major, 0), 1);
	if(err)
		return -1;

	printk ("devone init %s major %d\n", "devone", major);
	return 0;
}


static void devone_exit(void)
{
	dev_t dev = MKDEV(devone_major, 0);
	//delete cdev 
	cdev_del (&devone_cdev);
	unregister_chrdev_region (dev, devone_devs);

	printk ("devone exit\n");
}

module_init(devone_init);
module_exit(devone_exit);




#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/poll.h>
#include <asm/uaccess.h>
#include "devone_ioctl.h"
#include <linux/slab.h>

MODULE_LICENSE("Dual BSD/GPL");

static int devone_devs = 1;  //device count
static int devone_major = 0; //major number
static int devone_minor = 0;	//minor number
module_param(devone_major, uint, 0);
static struct cdev devone_cdev;
static struct class *devone_class = NULL;
static dev_t devone_dev;

struct devone_data {
    unsigned char val;
    rwlock_t lock;
};


static long devone_ioctl (struct file *filp, unsigned int cmd, unsigned long arg)
{
    struct devone_data *dev = filp->private_data;
    unsigned char val;
    int retval = 0;
    struct ioctl_cmd data;

    memset (&data, 0, sizeof(data));

    printk ("arg %ld \n", arg);

    switch (cmd) {

        case IOCTL_VALSET :

            if (!capable(CAP_SYS_ADMIN)) {
                retval = -EPERM;
                goto done;
            }

            if (!access_ok(VERIFY_READ, (void __user *)arg, _IOC_SIZE(cmd))) {
                retval = -EFAULT;
                goto done;
            }

            if (copy_from_user(&data, (int __user *)arg, sizeof(data))) {
                retval = -EFAULT;
                goto done;
            }

            printk ("IOCTL val %u (%s)\n", data.val, __func__);

            write_lock (&dev->lock);
            dev->val = data.val;
            write_unlock(&dev->lock);

            break;
        case IOCTL_VALGET :
   
            printk ("2\n");
            if (!access_ok (VERIFY_WRITE, (void __user *)arg, _IOC_SIZE(cmd))) {
                retval = -EFAULT;
                goto done;
            }
            read_lock(&dev->lock);
            val = dev->val;
            read_unlock(&dev->lock);

            data.val = val;
            if (copy_to_user ((int __user *)arg, &data, sizeof(data))) {
                retval = -EFAULT;
                goto done;
            }
            break;

        default:
            retval = -EFAULT;
            break;
    }

done:
            printk ("we are at done\n");
            return retval;

}

ssize_t devone_read (struct file *filp, char __user *buf, size_t count, loff_t *f_pos) {

        struct devone_data *p = filp->private_data;
        int i;
        unsigned char val;
        int retval;

        read_lock(&p->lock);
        val = p->val;
        read_unlock (&p->lock);

        printk ("%s, count %d pos %lld\n", __func__, count, *f_pos);
        for (i = 0; i < count; i++) {
            if (copy_to_user(&buf[i], &val, 1)) {
                retval = -EFAULT;
                goto out;
            }

        }
        retval = count;
out:
        return retval;

}

int devone_open (struct inode *inode, struct file *file) {

        struct devone_data *p;


        p = kmalloc(sizeof(struct devone_data), GFP_KERNEL);
        if (p == NULL) {
            printk("failed to allocate\n");
            return -ENOMEM;
        }

        p->val = 0xff;
        rwlock_init(&p->lock);
        file->private_data = p;
        printk("devone_open\n");
        return 0;
}

int devone_close (struct inode *inode, struct file *file) {
        struct devone_data *dev = file->private_data;
        if (dev)
            kfree(dev);
        printk("devone_close \n");
        return 0;

}


static struct file_operations devone_fops = {
        .open = devone_open,
        .release = devone_close,
        .read = devone_read,
//        .ioctl = devone_ioctl,
        .unlocked_ioctl = devone_ioctl,
};


static int devone_init(void) {

        dev_t dev = MKDEV(devone_major, 0); //dev_t device type

     
        int alloc_ret = 0;
        int major;
        int cdev_err = 0;
        //this is changed 
        //struct class_device *class_dev = NULL;
        struct device *device;
        printk ("devone init\n");

        alloc_ret = alloc_chrdev_region(&dev, 0, devone_devs, "devone");
        if (alloc_ret)
            goto error;

        devone_major = major = MAJOR(dev);

        cdev_init (&devone_cdev, &devone_fops);

        devone_cdev.owner = THIS_MODULE;
        devone_cdev.ops = &devone_fops;

        cdev_err= cdev_add(&devone_cdev, MKDEV(devone_major, devone_minor), devone_devs);

        if (cdev_err)
            goto error;

        //register class
        devone_class = class_create (THIS_MODULE, "devone");
        if (IS_ERR(devone_class))
            printk ("class create failed \n");

        devone_dev = MKDEV(devone_major, devone_minor);

        // class_dev = class_device_create (devone_class,
        //                           NULL, devone_dev, NULL,
        //                           "devone%d", devone_minor);

        device = device_create (devone_class,
                                  NULL, devone_dev, NULL,
                                  "devone%d", devone_minor);

        printk ("driver nanme %s major number  %d", "devone", devone_major);

        return 0;
error:
        if (cdev_err == 0)
            cdev_del(&devone_cdev);
        if (alloc_ret == 0)
            unregister_chrdev_region(dev, devone_devs);
        return -1;
}


static void devone_exit (void) {
        dev_t dev = MKDEV (devone_major, 0);
        //unregister class
        class_destroy(devone_class);
        //unregister device 
        device_destroy(devone_class, devone_dev);
        cdev_del(&devone_cdev);
        unregister_chrdev_region(dev, devone_dev);
        printk ("devone_exit %s\n", "devone");

}

module_init(devone_init);
module_exit(devone_exit);























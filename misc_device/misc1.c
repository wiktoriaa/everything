#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#define MY_DEV_NAME "new_misc_dev"

ssize_t n_misc_write (struct file *, const char __user *, size_t, loff_t *);
int n_misc_open (struct inode *, struct file *);

struct miscdevice n_device;
struct file_operations mfops = {
  .open = n_misc_open,
};
int err;

static int __init create_device(void)
{
  n_device.minor = MISC_DYNAMIC_MINOR;
  n_device.name = MY_DEV_NAME;
  n_device.fops = &mfops;
  n_device.mode = 0777;
  err = misc_register(&n_device);
  if (err) {
    printk ("%d", err);
    return err;
  }
  return 0;
}

static void __exit destroy_device(void)
{
  if(!err)
    misc_deregister(&n_device);
}

int n_misc_open(struct inode *node, struct file *file)
{
  printk(KERN_INFO "Device opened successfully");
  return 0;
}

module_init(create_device);
module_exit(destroy_device);

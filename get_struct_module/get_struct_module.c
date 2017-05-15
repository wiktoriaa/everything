#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/string.h>
#define MY_DEV_NAME "new_misc_device"

ssize_t n_misc_write (struct file *, const char __user *, size_t, loff_t *);
int n_misc_open (struct inode *, struct file *);

struct miscdevice n_device;
struct file_operations mfops = {
  .open = n_misc_open,
  .write = n_misc_write,
};
int errdev;
struct module *modp;
char c_name_mod[20];

void print_all_states(void)
{
  printk("MODULE_STATE_LIVE: %d", MODULE_STATE_LIVE);
  printk("MODULE_STATE_COMING: %d", MODULE_STATE_COMING);
  printk("MODULE_STATE_GOING: %d", MODULE_STATE_GOING);
  printk("MODULE_STATE_UNFORMED: %d", MODULE_STATE_UNFORMED);
}

static int __init create_device(void)
{
  print_all_states();
  n_device.minor = MISC_DYNAMIC_MINOR;
  n_device.name = MY_DEV_NAME;
  n_device.fops = &mfops;
  n_device.mode = 0777;
  errdev = misc_register(&n_device);
  if (errdev) {
    printk ("%d", errdev);
    return errdev;
  }
  return 0;
}

static void __exit destroy_device(void)
{
  if(!errdev)
    misc_deregister(&n_device);
}

ssize_t n_misc_write(struct file *file, const char __user *name_mod, size_t size, loff_t *loff)
{
  printk(KERN_DEBUG "MYDEL: module_name !<%9s>!", name_mod);
  printk(KERN_DEBUG "MYDEL: size %lu bytes", size);

  strncpy(c_name_mod, name_mod, size-1);
  modp = find_module(c_name_mod);
  if(modp != NULL)
    printk(KERN_DEBUG "MYDEL: OK module found %s", modp->mkobj.kobj.name);
  else {
    printk(KERN_WARNING "MYDEL: Error name module '%s'", c_name_mod);
    return size;
  }
  printk(KERN_DEBUG "Changing module state");

  return size;
}

int n_misc_open(struct inode *node, struct file *file)
{
  printk(KERN_DEBUG "MYDEL: Device opened successfully");
  return 0;
}

module_init(create_device);
module_exit(destroy_device);
MODULE_LICENSE("GPL");

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/unistd.h>
#include <linux/init.h>
#include <asm/uaccess.h>
#include <linux/delay.h>
#define F_NAME "lenny"
#define S_NAME "second_mdev"
#define LENNY "( ͡° ͜ʖ ͡°)"

struct miscdevice lenny_dev;
int err;

int open_devs(struct inode *inode, struct file *file)
{
  return 0;
}

int release_devs(struct inode *inode, struct file *file)
{
  return 0;
}

ssize_t read_devs(struct file *file, char __user *buff, size_t size, loff_t *loft){
  copy_to_user(buff, LENNY, sizeof(LENNY));
  msleep(100);
  return size;
}

ssize_t write_devs(struct file *file, char __user *buff, size_t size, loff_t *loft)
{
  return size;
}

struct file_operations fops = {
  .open = open_devs,
  .read = read_devs,
  /*.write = write_devs,*/
  .release = release_devs,
};

static int __init reg_device(void)
{
  lenny_dev.name = F_NAME;
  lenny_dev.fops = &fops;
  lenny_dev.mode = 0777;

  err = misc_register(&lenny_dev);
  if(err) {
    printk(KERN_ERR "LENNY: Register lenny dev failed %d", err);
    return 0;
  }

  printk("LENNY: Device registered successfully");
  return 0;
}

static void __exit free_dev(void)
{
  if(!err){
    misc_deregister(&lenny_dev);
    printk("LENNY: Unregistered 1st dev successfully");
  }

  printk("LENNY: Module unloaded");
}
module_init(reg_device);
module_exit(free_dev);
MODULE_LICENSE("GPL");

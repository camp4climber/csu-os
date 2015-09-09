#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/seq_file.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>
#include <linux/mm.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tim Whitaker");
MODULE_DESCRIPTION("Page Fault Module");

static int pagefaults_proc_show(struct seq_file *m, void *v)
{
    unsigned long pagefaults = (unsigned long) this_cpu_read(vm_event_states.event[PGFAULT]);
    seq_printf(m, "%lu\n", pagefaults);
    return 0;
}

static int pagefaults_proc_open(struct inode *inode, struct file *file)
{
    return single_open(file, pagefaults_proc_show, NULL);
}

static const struct file_operations pagefaults_proc_fops = {
    .owner = THIS_MODULE,
    .open = pagefaults_proc_open,
    .read = seq_read,
    .llseek = seq_lseek,
    .release = single_release
};

static int __init proc_pagefaults_init(void)
{
    proc_create("num_pagefaults", 0, NULL, &pagefaults_proc_fops);
    return 0;
}

static void __exit proc_pagefaults_exit(void)
{
    remove_proc_entry("num_pagefaults", NULL);
}

module_init(proc_pagefaults_init);
module_exit(proc_pagefaults_exit);

MODULE_LICENSE("GPL");

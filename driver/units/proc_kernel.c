#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/fs.h>

static int proc_open(struct inode *inode, struct file *file);

static struct proc_dir_entry *kprobelabs_entry;
static struct proc_ops proc_ops = {
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_open = proc_open,
    .proc_release = single_release,
};


int proc_init(void)
{
    if (kprobelabs_entry != NULL)
    {
        return 0;
    }
    kprobelabs_entry = proc_create("kprobelabs", 644, NULL, &proc_ops);
    if (kprobelabs_entry == NULL)
    {
        return -1;
    }

    return 0;
}

int proc_deinit(void)
{
    if (kprobelabs_entry != NULL)
    {
        proc_remove(kprobelabs_entry);
        return 0;
    }
    return -1;
}

static int proc_show(struct seq_file *m, void *v)
{
    seq_printf(m, "Hello, This is kprobelabs proc\n");
    return 0;
}

static int proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, proc_show, NULL);
}
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/fs.h>

static int kprobelabsProcOpen(struct inode *inode, struct file *file);

static struct proc_dir_entry *pKprobelabsProc;
static struct proc_ops proc_ops = {
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_open = kprobelabsProcOpen,
    .proc_release = single_release,
};

static int ProcInit(void)
{
    if (pKprobelabsProc != NULL)
    {
        return 0;
    }
    pKprobelabsProc = proc_create("kprobelabs", 644, NULL, &proc_ops);
    if (pKprobelabsProc == NULL)
    {
        return -1;
    }

    return 0;
}

static int ProcExit(void)
{
    if (pKprobelabsProc != NULL)
    {
        proc_remove(pKprobelabsProc);
        return 0;
    }
    return -1;
}


int ProcUnit(void *arg)
{
    int bInit = *(int *)arg;

    if (bInit)
    {
        return ProcInit();
    }
    else
    {
        return ProcExit();
    }

}

static int kprobelabsProcShow(struct seq_file *m, void *v)
{
    seq_printf(m, "Hello, This is kprobelabs proc\n");
    return 0;
}

static int kprobelabsProcOpen(struct inode *inode, struct file *file)
{
	return single_open(file, kprobelabsProcShow, NULL);
}
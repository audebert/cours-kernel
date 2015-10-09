/*
 * version
 *
 * Copyright (c) - 2015 Rémi Audebert <halfr@lse.epita.fr>
 *
 * Licensed under the GPL-2 or later.
 *
 */

#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/uaccess.h>
#include <linux/utsname.h>

#include "version.h"

#define DEVICE_NAME	"version"

#define BUF_SIZE	64

#define sizeof_member(type, member) sizeof(((type *)0)->member)
#define UTS_SIZE sizeof_member(struct new_utsname, version)

static char buffer[UTS_SIZE];
static unsigned modified;

/**
 *	Returns the kernel version string.
 */
static ssize_t version_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
	size_t min_count;

	pr_debug("%s(): ppos: %lld\n", __func__, *ppos);
	
	if (*ppos >= UTS_SIZE)
		return 0;
	if (count >= UTS_SIZE)
		*ppos = count;

	min_count = min(strlen(utsname()->version), count);

	if (copy_to_user(buf, utsname()->version, min_count))
		return -EFAULT;

	pr_debug("%s(): returned %zu chars\n", __func__, min_count);

	return min_count;
}

/**
 *	Sets the kernel version string.
 */
static ssize_t version_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
	size_t min_count;
	
	min_count = min((size_t)UTS_SIZE-1, count);

	if (!modified)
	{
		modified = 1;
		memcpy(buffer, utsname()->version, UTS_SIZE);
	}

	// FIXME(halfr): fix locking issues, if possible
	if (min_count && copy_from_user(utsname()->version, buf, min_count))
		return -EFAULT;

	pr_debug("%s(): wrote %zu chars\n", __func__, min_count);

	return min_count;
}

static int version_open(struct inode *inode, struct file *file)
{
	pr_info("open()\n");

	return 0;
}

static int version_release(struct inode *inode, struct file *file)
{
	pr_info("release()\n");

	return 0;
}

static void version_reset(void)
{
	if (modified)
	{
		pr_debug("reset() to %s\n", buffer);
		memcpy(utsname()->version, buffer, UTS_SIZE);
		modified = 0;
	}
}

static long version_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	pr_debug("ioctl: cmd: 0x%x\n", cmd);

	switch (cmd) {
	case VERSION_MODIFIED:
		return put_user(modified, (unsigned __user*)arg);
	case VERSION_RESET:
		version_reset();
		return 0;
	default:
		return -ENOTTY;
	}
}

static struct file_operations version_fops = {
	.owner		= THIS_MODULE,
	.read		= version_read,
	.write		= version_write,
	.open		= version_open,
	.release	= version_release,
	.unlocked_ioctl	= version_ioctl,
};

static struct miscdevice version = {
	.minor = MISC_DYNAMIC_MINOR,
	.name  = DEVICE_NAME,
	.fops  = &version_fops,
};

static int __init version_init(void)
{
	int ret;

	ret = misc_register(&version);
	if (ret < 0) {
		pr_warn("misc_register() failed: %d\n", ret);
		return ret;
	}

	return 0;
}

static void __exit version_exit(void)
{
	version_reset();
	misc_deregister(&version);
	pr_info("exit()\n");
}

module_init(version_init);
module_exit(version_exit);

MODULE_DESCRIPTION("version");
MODULE_AUTHOR("Rémi Audebert <halfr@lse.epita.fr>");
MODULE_LICENSE("GPL");

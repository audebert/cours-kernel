/*
 * Copyright (C) 2015 Rémi Audebert <halfr@lse.epita.fr>
 *
 * Sample filesystem module
 */
#define pr_fmt(fmt)    KBUILD_MODNAME ": " fmt
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/pagemap.h>

#include "fs.h"

struct inode *fs_inode_get(struct super_block *sb, const struct inode *dir,
			   umode_t mode)
{
	/* For cache usage: iget_locked(sb, inode_id) */
	struct inode *inode = new_inode(sb);
	
	if (!inode)
		return ERR_PTR(-ENOMEM);

	inode->i_ino = get_next_ino();
	inode_init_owner(inode, dir, S_IFDIR);
	/* No address space mapping operations. */
	inode->i_mapping->a_ops = &empty_aops;
	inode->i_atime = inode->i_ctime = inode->i_mtime = CURRENT_TIME;
	
	switch (mode)
	{
	default:
		init_special_inode(inode, mode,  0);
		break;
	case S_IFDIR:
		inode->i_op = &simple_dir_inode_operations;
		inode->i_fop = &simple_dir_operations;
		/* directory inodes start off with i_nlink == 2 (for "." entry) */
		set_nlink(inode, 2);
		break;
	case S_IFREG:
	case S_IFLNK:
		/* ... */
		break;
	}

	return inode;
}

static const struct super_operations super_operations = {
	.statfs = simple_statfs,
};

int fs_super_fill(struct super_block *sb, void *data, int silent)
{
	struct inode *inode;

	sb->s_blocksize = PAGE_CACHE_SIZE;
	sb->s_blocksize_bits = PAGE_CACHE_SHIFT;
	sb->s_magic = FS_SUPER_MAGIC;
	sb->s_op = &super_operations;

	inode = fs_inode_get(sb, NULL, S_IFDIR);
	sb->s_root = d_make_root(inode);
	if (!sb->s_root)
	    return -ENOMEM;

	return 0;
}

static struct dentry *fs_super_mount(struct file_system_type *fs_type,
				     int flags, const char *dev_name,
				     void *data)
{
	return mount_nodev(fs_type, flags, data, fs_super_fill);
}

static void fs_super_kill(struct super_block *sb)
{
	kill_anon_super(sb);
}


static struct file_system_type fstype = {
	.name		= KBUILD_MODNAME "fs",
	.owner		= THIS_MODULE,
	.mount		= fs_super_mount,
	.kill_sb	= fs_super_kill,
	.fs_flags	= FS_USERNS_MOUNT,
};

static int __init mod_init(void)
{
	return register_filesystem(&fstype);
}

static void __exit mod_exit(void)
{
	unregister_filesystem(&fstype);
}

module_init(mod_init);
module_exit(mod_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("FS");
MODULE_ALIAS_FS(KBUILD_MODNAME "fs");
MODULE_AUTHOR("LSE");

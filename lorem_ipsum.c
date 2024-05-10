#include <linux/init.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/printk.h>
#include <linux/minmax.h>

#define LIPSUM_MODULE_NAME "lorem_ipsum"
#define LIPSUM_DEVICE_NAME "lorem-ipsum"

MODULE_AUTHOR("Niklas Elsbrock");
MODULE_DESCRIPTION("Device driver for the " LIPSUM_DEVICE_NAME " device");
MODULE_LICENSE("GPL");

static const char LOREM_IPSUM[] =
		"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do "
		"eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim "
		"ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut "
		"aliquip ex ea commodo consequat. Duis aute irure dolor in "
		"reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla "
		"pariatur. Excepteur sint occaecat cupidatat non proident, sunt in "
		"culpa qui officia deserunt mollit anim id est laborum. ";

static ssize_t lipsum_read(
		struct file* file,
		char __user* buf,
		size_t count,
		loff_t* ppos)
{
	size_t lipsum_pos;
	size_t buf_pos;
	size_t len;

	lipsum_pos = *ppos % sizeof(LOREM_IPSUM);
	buf_pos = 0;

	while (buf_pos < count) {
		len = min(count - buf_pos, sizeof(LOREM_IPSUM) - lipsum_pos);

		if (copy_to_user(buf + buf_pos, LOREM_IPSUM + lipsum_pos, len)) {
			pr_err(LIPSUM_MODULE_NAME ": copy_to_user failed");
			return -EFAULT;
		}

		lipsum_pos = 0;
		buf_pos += len;
	}

	*ppos += buf_pos;
	return buf_pos;
}

static const struct file_operations lipsum_fops = {
	.owner = THIS_MODULE,
	.read = lipsum_read,
};

static struct miscdevice lipsum_dev = {
	MISC_DYNAMIC_MINOR,
	LIPSUM_DEVICE_NAME,
	&lipsum_fops
};

static int __init lipsum_init(void) {
	int ret;
	ret = misc_register(&lipsum_dev);
	if (ret)
		pr_err(LIPSUM_MODULE_NAME ": Unable to register "
				LIPSUM_DEVICE_NAME " device\n");
	return ret;
}

static void __exit lipsum_exit(void) {
	misc_deregister(&lipsum_dev);
}

module_init(lipsum_init);
module_exit(lipsum_exit);

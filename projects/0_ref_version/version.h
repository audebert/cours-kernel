#ifndef __VERSION_H__
#define __VERSION_H__

#include <asm/ioctl.h>

#define VERSION_IOCTL_NUM	'V'

#define VERSION_MODIFIED	_IOW(VERSION_IOCTL_NUM, 1, unsigned)
#define VERSION_RESET		_IO(VERSION_IOCTL_NUM, 2)

#endif

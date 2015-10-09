Kernel Programming II - Linux
=============================

Introduction
------------

Here are the 2 assignments for **Kernel Programming II - Linux**.

General remarks:

- All the code you give us must be formatted for the Linux coding style.
- Theses projects targets the `x86_64` version of Linux.
- You are advised to use the `qemu` emulator to debug and test your projects.
- You are free to send as many as emails as you want for each project, only the
  last counts.
- Each email should have the following format:

```
To: halfr@lse.epita.fr, surply@lse.epita.fr
Subject: [KERNEL] LOGIN_X LOGIN_Y - PROJECT NAME
```

Part 1 - tty driver
-------------------

The goal of this project is to create a kernel driver for the 8250 serial
controller.

You must:

- Deactivate the 8250 support in your kernel.
- Create and out-of-tree module.
- For each serial port your handle, create one misc-device.
- Handle line discipline configuration using ioctl.
- Handle the hardware interrupts.
- Handle the hardware FIFO.
- Create a test program.
- Send us a tarball of the sources of your module, with content as such:

```
8250-login_x
├── Makefile
├── test.c
├── 8250.c
└── 8250.h
```

You will learn:

- How-to perform I/O operations.
- How-to register and handle interrupts.

Grading:

- Your module must compile and run with the latest Linux stable Linux release.
- Your module must work according to the requirements.

Reference:

- [Serial Programming: 8250 UART](https://en.wikibooks.org/wiki/Serial_Programming/8250_UART_Programming)

Bonus:

- Integrate your driver with the `tty` subsystem.

Part 2 - chiffrefs
------------------

The aim of this project is to create a new file system for the Linux kernel.

You must:

- Create a new file system.
- Send us a tarball of your module by email.

Your filesystem must work as an overlay where each byte wrote to a file is
rotated by a number given on the option string, when the filesystem is mounted.

Usage:

```bash
$ insmod chiffrefs.ko
$ mkdir chiffred clear
$ mount chiffred clear -t chiffrefs -o n=13
$ echo -n foobar >clear/test
$ cat clear/test
foobar
$ cat chiffred/test
sbbone
```

You will learn:

- How to create as new file system.
- How to use files in kernel space.

Grading:

- Did you send us your module?
- Does your file system:

    - work as expected?
    - support directories?
    - support basic file operations such as read and write?
    - support size information?

Conclusion
----------

Corrections will take place on your computers.

<!---
vim: spl=en spell:
-->

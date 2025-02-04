Kernel Programming I - Linux
============================

Introduction
------------

Here are the 3 assignments for **Kernel Programming I - Linux**.

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

Part 1 - syscall
----------------

The aim of this project is to add a new syscall to the Linux kernel.

You must:

- Clone the latest stable Linux release.
- Edit the sources and add the `uptime()` syscall.
- Configure, compile, and run your kernel.
- Create a patch of your modifications.
- Send us a patch of your modifications by email.

Here is the specification of the `uptime()` syscall:

    NAME
           uptime - get uptime in seconds

    SYNOPSIS
           time_t uptime(time_t *t);

    DESCRIPTION
           uptime() returns the uptime of the machine as a number of seconds.

           If t is non-NULL, the return value is also stored in the memory pointed
           to by t.

    RETURN VALUE
           On  success, the uptime in seconds.
           On error, ((time_t) -1) is returned.

You will learn:

- How-to clone, configure, build and run a Linux kernel.
- How-to add a new syscall to Linux.
- How-to use your syscall from the userland.
- How-to format, check and send a patch.
- How-to pass value from the kernel to the userspace.

Grading:

- Is the patch correctly formatted?
- Does your code use the latest APIs?
- Does your syscall conform to the specification?
- Is your code safe to use?

Bonus:

- Make your syscall opt-in using kconfig.

Part 2 - lkm
------------

The goal of this project is to create a simple loadable kernel module.

You must:

- Create and out-of-tree module.
- Create a test program.
- Send us a tarball of the sources of your module, with content as such:

```
version-login_x
├── Makefile
├── test.c
├── version.c
└── version.h
```

The module must do the following:

- Register a new `misc` device: `version`.
- Reading on the device returns the current version of the kernel, as read in
  `/proc/sys/kernel/version`
- Writing on the device changes the current version of the kernel.
- The device will allow two IOCTL:

    - `VERSION_MODIFIED`: returns whether version is not the original.
    - `VERSION_RESET`: reset the original version of the kernel.

You will learn:

- How-to build an out-of-tree loadable Linux module.
- How-to load a module.
- How-to register a misc device.
- How-to set the `read`, `write` and `ioctl` operations on a device.

Grading:

- Your module must compile and run with the latest Linux stable Linux release.
- Your module must work according to the requirements.

Part 3 - rootkit
----------------

Now that you are good at adding syscalls and creating modules, you have to
create a module that modifies the syscall table, and hooks (*replaces*) the
`open()` syscall. This means that when the `open()` syscall is used, it is your
code that will be called. You are advised to use a virtual machine in order to test
this part or you might crash your system.

You are free to choose what to do with your hooked `open()`, for example:

- Display the opened files.
- Redirect one filename to another.
- ...

You must:

- Create an out-of-tree module hooking the `open()` syscall.
- Send us a tarball of your module by email.

You will learn:

- What horrors your can do in kernel land.

Grading:

- Does your module work?

Conclusion
----------

Corrections will take place on your computers.

<!---
vim: spl=en spell:
-->

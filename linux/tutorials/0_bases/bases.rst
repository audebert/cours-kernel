Epitech Kernel I - TP 1
=======================

The goal of this tutorial is to:

- Setup a dev environnemnt using qemu and Linux's nfsroot
- Start working with Linux's code

Getting started
===============

Build a busybox
```````````````

http://www.busybox.net/

.. code-block:: bash

    $ git clone git://git.busybox.net/busybox
    $ make defconfig # All features, no debug
    make menuconfig # Setup static linking
    make // Compile
    make install

Build a rootfs
``````````````

::

    dd if=/dev/zero of=disk.img bs=1M count=16
    mkfs.ext4 disk.img -L root
    mkdir mnt
    mount disk.img mnt
    cp -r busybox/_install/* mnt
    # Setup mounts
    cd mnt
    mkdir -p etc/init.d proc sys dev
    echo 'proc    /proc   proc    defaults' >> etc/fstab
    echo 'sysfs   /sys    sysfs   defaults' >> etc/fstab
    echo 'mount -a' >> etc/init.d/rcS
    chmod +x etc/init.d/rcS

Build Linux
```````````
::

    git clone --depth 1 git://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git
    make defconfig
    make

.. image:: http://imgs.xkcd.com/comics/compiling.png

Using Qemu
``````````
::

    qemu-system-x86_64 -kernel /path/to/linux/arch/x86/boot/bzImage -hda /path/to/rootfs/disk.img -append "root=/dev/sda console=ttyS0" -nographic

Debugging with Qemu
```````````````````

- Compile linux with debug info.
- Run QEMU with a gdb server: ``-s -S``
- Run gdb with your kernel binary: ``gdb vmlinux``
- Once in gdb, connect to QEMU: ``target remote localhost:1234``
- Add some breakpoints: ``b my_symbol``
- Run the simulation in gdb: ``continue``

RootNFS
=======

- Create a rootfs
- Setup a NFS server
- Edit /etc/exports to export /path/to/rootfs
- ``exportfs -av``
- Command line: ``root=/dev/nfs nfsroot=10.0.2.2:/path/to/rootfs rw ip=10.0.2.15::10.0.2.1:255.255.255.0``

myInit
======

Init, or PID1, is the first program started by the kernel.

- Search inside the Linux sources what are the paths the kernel will look for the init program.
- Code and compile your own init program. Put it where the kernel expects it and boot your kernel.

Note:

- The init program must never exit.

sys_hello
=========

Write a syscall which, when called, prints "hello, world!" on the console.

Test your syscall in your init.

See also:

- `Anatomy of a system call <http://lwn.net/Articles/604287/>`_
- `syscall(2) <http://man7.org/linux/man-pages/man2/syscall.2.html>`_

myModuleHello
=============

Specifications:

- When the module is loaded, it prints "Hello, world!"
- When the module is removed, it prints "Goodbye, cruel world!"
- It exports the ``hello`` symbol that prints "Hello from myModuleHello"

Steps:

- Add your module to the Kbuild, you can add a configure option in a KConfig file
- Compile your module
- Dynamically load your module

myModuleHello2
==============

- Build a second module which uses ``hello`` symbol defined in myModuleHello.
- Use module parameters to customize your module.

myCrashModule
=============

Write 3 kernel modules. When loaded, each one should crash the kernel in a different way.

Contact
=======

- halfr@lse.epita.fr
- surply@lse.epita.fr

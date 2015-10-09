# Kernel Programming I - Kernel From Scratch

## Introduction

Here is the assigments for *Kernel Programming I - Kernel From Scratch*.

    To: halfr@lse.epita.fr, surply@lse.epita.fr`
    Subject: [KERNEL] LOGIN_X LOGIN_Y - KFS

## Hello World !

The aim of this project is to get a basic build system for your own kernel.

You must:

- Write a Makefile with the following rules:
    - `all`: compile the kernel and the generate the ELF file.
    - `boot`: boot the kernel using Qemu or Bochs.
    - `debug`: boot the kernel and attach a gdb on it.
- Write a function `void printk(const char *msg)` which prints on the
        framebuffer and on the serial port with the following line protocol:
    - 38400 bauds
    - 8 bits per word
    - No parity check
    - 1 stop bit
- Send us a tarball of the sources of your kernel:

```
    kfs-login_x
    ├── Makefile
    ├── kfs.ld
    └── src/
        ├── crt0.S
        └── main.c
```

You will learn:

- How VGA text-mode works
- How 16550 UART chip works

## Conclusion

Corrections will take place in your computers.

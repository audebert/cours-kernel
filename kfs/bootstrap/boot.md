# Introduction

## Assignment

- A booting kernel on an `i386` emulator that prints `Hello World!` on screen
  and serial port.

- It must:
    - check multiboot magic number
    - have a print function: `void printk(const char *str);`
    - have a build system

## Tools

- GCC
- GNU Binutils
- GDB
- Qemu

## Kernel Binary

- A kernel is a program
- It is loaded directly at a specific address in physical memory
- An other program is in charge of placing kernel in memory: the bootloader

# Boot

## Master Boot Record

![](res/MBR.png)

## Multiboot

- Multiboot is a GNU standard
- Its aim is to provide critical information to kernel
- These information are provided by the bootloader

## Multiboot and entry point

- Multiboot standard provides information to your kernel entry point:
    - `eax` register contains the multiboot magic number
    - `ebx` register contains the address of the multiboot main structure

# Compiling

## Kernel Compilation

- A kernel is compiled like a regular program
- But linking stage of compilation is different

## No libc

- Kernel cannot be linked with libc
- Why ?
    - No dynamic linking
    - Libc uses kernel to work...

## Kernel Compilation flag

```
CFLAGS += -nostdinc -fno-builtin -m32
CFLAGS += -fno-stack-protector

LDFLAGS += -nostdlib -m32 -Wl,--build-id=none
```

# Binary formats

## Binary Formats

- A binary format is the format of an executable
- Operating systems uses their own binary format :
    - Most UNIX OSes use the Elf Standard
    - Microsoft uses Portable Executable (PE)
    - Apple uses Mach-O

## Binary Formats

- Kernel are not standard programs
- As it is one of the first binary loaded, it should be binary format free
- But bootloaders require a specific binary format
- Easier to use because all tools are made for this

## ELF

- Easy to use
- ELF is a multi architecture standard
- A lot of tools exists for ELF
- GRUB loads ELF and emulators know well this format

## ELF

![](res/elf.png)

## ELF

![](res/elf_loader.png)

## ELF Section

- ELF is based upon sections
- Sections are determined areas of your binary
- Most used elf sections are:
    - `.text`: CPU executable instructions
    - `.rodata`: read only program data
    - `.data`: read/write program data
    - `.bss`: zeroed program data

## ELF Program Header

- Program headers are binary areas loaded in memory
- Elf loaders do not care about sections
- Elf loaders only handle Program headers

## `crt0.S`

    #define	MAGIC		0x1badb002
    #define FLAGS		0x7

    .section .multiboot
        .align		4
        .long		MAGIC
        .long		FLAGS
        .long		-(MAGIC + FLAGS)

    .section .text
    .global _start
    _start:
        push %ebx	/* multiboot info */
        push %eax	/* magic */
        call main	/* kernel entry point */
        hlt

# Linking

## Linker Scripting

- Permits to reorganize section at a specific physical address
- Permits to create variable that contains section address

## ld script example

    OUTPUT_FORMAT("elf32-i386")
    OUTPUT_ARCH("i386")
    ENTRY(_start)

    SECTIONS
    {
        . = 0x100000 + SIZEOF_HEADERS;

        PROVIDE(begin_text = .);
        .text :
        {
            *(.multiboot) *(.text)
        }
    }

## Kernel linking tips

- man readelf
- man objcopy
- Load kernel above 0x100000
- Specify your own entry point

# Testing

## Testing

- Testing on real hardware is really hard and painful
- Testing on an emulator is really easier
- 2 main emulators exists on UNIX based systems:
    - Qemu
    - Bochs

## Qemu

- `-kernel`:  directly specify kernel image, no need to put it in file
   system (multiboot compatible)
- `-append`: set kernel command line
- `-hda`: first disk image
- `-m`: RAM memory size
- `-s`: activate gdb stub on port 1234
- `-S`: stop cpu on startup
- `-monitor stdio`: display qemu monitor on stdio

## Kernel Debugging

How to:

### Have QEMU wait for your debugger to hook:

- Add "`-s -S`" to QEMU options


### Launch gdb and hook to QEMU

- `$> gdb kernel.elf`
- `$(gdb)> target remote localhost:1234`

## Debugging tips

- `si`: instruction step
- `disass`: disassembling current frame
- `x ` *options* *address*: printing memory
- `i r`: printing registers
- Don't forget to put debug sections in your kernel binary

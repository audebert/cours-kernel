# Kernel Programming II - Kernel From Scratch

## Introduction

Here is the assigments for *Kernel Programming II - Kernel From Scratch*.

    To: halfr@lse.epita.fr, surply@lse.epita.fr`
    Subject: [KERNEL] LOGIN_X LOGIN_Y - KFS

The specifications described below should be be considered as guidelines.
This is not mandantory to perfectly fit this API but is highly recommended.

## Frame allocator

### Types

- `typedef unsigned int phys_t;`
    - *Description*: describes a physical address. Since paging is enabled, it
    is not possible to dereference this address.

- `struct frame;`
    - *Description*: A structure which describes a frame. It should contain:
        - a reference counter
        - a virtual address where is the frame is mapped

### Functions

- `void init_frame_alloc(multiboot_info_t *multiboot);`
    - *Description*: Initialize frame allocator. It should use memory map
        structure included in multiboot info in order to get RAM size.
    - *Arguments*:
        - `multiboot`: a pointer to the multiboot struture provided by the
            bootloader.

- `struct frame* alloc_frame(void);`
    - *Description*: Allocate a new frame and return a pointer the structure
        which describes it.

- `int alloc_frames(int n, struct frame **frames);`
    - *Description*: Allocate `n` physically contiguous frames.
    - *Arguments*:
        - `n`: number of frames to allocate.
        - `frames`: pointer to allocated frames

- `void free_frame(struct frame *frame);`
    - *Description*: Decrement reference counter of a frame.

- `phys_t frame_to_phys(struct frame *frame);`
    - *Description*: Get physical address of a frame.

- `struct frame* phys_to_frame(phys_t addr);`
    - *Description*: Get frame data from physical address.

## Page allocator

### Functions

- `void* alloc_pages(struct frame* pdbr, size_t n);`
    - *Description*: find n consecutive free virtual pages and return their
        address.
    - *Arguments*:
        - `pdbr`: frame which contains page directory
        - `n`: number of pages needed

- `int map_pages(struct frame* pdbr, void* vaddr, struct frame *frames, size_t n, int flags);`
    - *Description*: Map `n` physical pages to virtual pages.
    - *Arguments*:
        - `pdbr`: frame which contains page directory
        - `vaddr`: address of virtual pages
        - `frames`: frames to map
        - `n`: number of frames to map
        - `flags`: access right associated to pages

- `void *map_io(struct frame* pdbr, phys_t ioadddr, size_t len);`
    - *Description*: Map an IO memory range. Be careful with `ioaddr`
    -                alignment.
    - *Arguments*:
        - `pdbr`: frame which contains page directory
        - `ioaddr`: base address of IO memory range
        - `len`: size of IO memory range
    - *Example*: Map VGA text buffer to virtual address space
        - `void *video_mem = map_io(pdbr, 0xB8000, 80 * 25 * 2);`

- `void unmap_pages(struct frame *pdbr, void *vaddr, int n);`
    - *Description*: Unmap pages.
    - *Arguments*:
        - `pbdr`: frame which contains page directory
        - `vaddr`: address of pages to unmap
        - `n`: number of pages to unmap

## Binary loader

### Functions

- `void load_binary(struct frame *pdbr, Elf32_Ehdr *elf);`
    - *Description*: Load an ELF in a specific address space.
    - *Arguments*:
        - `pdbr`: frame which contains page directory
        - `elf`: ELF to load

### Hint

Since your kernel does not supports any file system, you can include
application ELF file into the Kernel ELF (ie on a dedicated section) or append
it in a multiboot module.

## Tasks

### Types

- `struct task;`
    - *Description*: A structure which describes a frame. It should contain:
        - a page directory base address register

### Functions

- `struct task *create_task(struct frame *pdbr, uint32_t entry_point);`
    - *Description*: Create a new task with a specific address space.
    - *Arguments*:
        - `pdbr`: frame which contains page directory
        - `entry_point`: task entry point

- `struct task *clone_task(struct task *parent, int flags);`
    - *Description*: Clone a child task.

- `void enqueue_task(struct *task);`
    - *Description*: Add a task to the scheduler process queue.

- `void kill_task(struct *task);`
    - *Description*: Remove task from the scheduler process queue.

- `void schedule(void);`
    - *Description*: Switch to the next process.
    - *Hint*: Do not forget to call this function in the *PIT* events handler
        (`IRQ0`).

## Userland

### Functions

- `void start_userland(void);`
    - *Description*: Load userland application (ie *init* process) and run it.
    This function should not return.

### Syscalls

Your kernel should implement a syscall mechanism. The application must be able
to trigger syscalls using `int $0x80` instruction. Here is a list of syscalls
that can be implemented:

- `int read(const char *buf, size_t len);`
    - *Description*: Read characters from keyboard.

- `int write(const char *buf, size_t len);`
    - *Description*: Write characters using `printk`.

- `void _exit(int status);`
    - *Description*: Terminate the calling process.

- `pid_t fork(void);`
    - *Description*: Create child process.

- `void *mmap(void *addr, size_t length, int prot, int flags);`

## Conclusion

Corrections will take place in your computers.
Have fun :)

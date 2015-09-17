# Binary loading

## Executable and Linkable Format

![](res/elf.png)

## Sections

- `.text`: program code
- `.rodata`: readonly data (ex: Constant strings)
- `.data`: global data
- `.bss`: unitialized data
- `.symtab`: symbols table
- `.init`: executable code for the initialization of the program
- `.fini`: executable code for the program termination

## Segments and Sections

![](res/segments_and_sections.png)

## Binary Loader

![](res/elf_loader.png)

## Getting Elf program headers

- Program headers can be found directly from Elf header 
with these fields:
    - `e_phoff`: offset to program header structure array
    - `e_phentsize`: program header structure size in array
    - `e_phnum`: number of program header structures in array

## Elf program headers information

- Program header structure then contains the following informations:
    - `p_type`: program header type
    - `p_flags`: memory flags associated with program header
    - `p_vaddr`: expected virtual memory address of program header
    - `p_off`: program header offset in Elf
    - `p_memsz`: in memory size of program header
    - `p_filesz`: in file size of program header. It can differ from 
      `p_memsz`, then the remaining part must be filled with 0

# Syscall

## Syscall

![](res/syscall.png)

## Syscall Gate

- A unique syscall gate (0x80)
    - `int 0x80`
- `eax`: Syscall number
- `ebx`, `ecx`, `edx`: Syscall parameters

# TSS

## Events in userland

![](res/context_saving.eps)

## TSS

![](res/tss.eps)

## TSS Descriptor

![](res/tsse.eps)

## Load TSS

    movw $0x10, %ax
    ltr %ax /* The second GDT entry describe the TSS */

## GDT requirements

- GDT should then contain:
    - Null descriptor
    - Kernel code segment
    - Kernel data segment
    - Userland code segment
    - Userland data segment
    - TSS

# Jump to userland

## Register setting to go to Userland

- To jump to Userland, register values must be:
    - `cs`, `ds`, `ss`
    - `esp` must be set to a task stack address
    - `eip` must be set to program entry point

## Events in userland

![](res/context_saving.eps)

# Conclusion

## Binary loading

- `void load_binary(struct frame *pdbr, Elf32_Ehdr *elf);`

## Tasks

- `struct task *create_task(struct frame *pdbr, uint32_t entry_point);`
- `struct task *clone_task(struct task *parent, int flags);`
- `void enqueue_task(struct task *task);`
- `void kill_task(struct task *task);`
- `void switch_to(struct task *task);`
- `void schedule(void);`

## Userland

- `void start_userland(void);`

## Syscalls

- `int write(const char *buf, size_t len);`
- `int read(const char *buf, size_t len);`
- `void _exit(int status);`
- `pid_t fork(void);`
- `void *mmap(void *addr, size_t length, int prot, int flags);`

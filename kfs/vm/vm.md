# x86 paging

## Address translation

![](res/addr_transl.png)

## Paging and segmentation

![](res/paging_seg.png)

## Vocabulary

- Memory Management Unit
- Page
- Frame
- Address space
- Logical address
- Linear address
- Physical address

## x86 paging

![x86 (32 bit) paging - 4KB](res/x86paging.eps)

## x86 paging

![x86 (32 bit) paging - 4MB](res/x86paging_4MB.eps)

## x86 paging

![](res/paging_records.eps)

## x86 paging

![](res/cr.eps)

## Page Fault Handling

![Page fault error code](res/page_fault.eps)

- CR2: faulty address

## Translation Lookaside Buffer

- Looked automatically prior to any walk in page directories
- Filled in and maintained automatically by MMU
- Flushed automatically (except global pages) when address space is changed
  (CR3 is changed)
- MMU must be informed with `invlpg` instruction when:
    - Page rights are changed
    - A page is unmapped

## `invlpg`

       asm volatile("invlpg (%0)"
                    :
                    : "r" (addr)
                    : "memory");

# Paging initialization

## Paging initialization

![](res/kernel_remap.eps)

# Frame allocator

## Multiboot mmap

```
typedef struct multiboot_info
{
  ...

  unsigned long mmap_length;
  unsigned long mmap_addr;
} multiboot_info_t;
```

## Multiboot mmap

```
typedef struct memory_map
{
  unsigned long size;
  unsigned long base_addr_low;
  unsigned long base_addr_high;
  unsigned long length_low;
  unsigned long length_high;
  unsigned long type;
} memory_map_t;
```

## Frame allocator

- `void init_frame_alloc(multiboot_info_t *multiboot);`
- `struct frame* alloc_frame(void);`
- `int alloc_frames(int n, struct frame **frames);`
- `void free_frame(struct frame *frame);`
- `phys_t frame_to_phys(struct frame *f);`
- `phys_t phys_to_frame(struct frame *f);`

# Page allocator

## Page allocator

- `void* alloc_pages(struct frame* pdbr, size_t n);`
- `int map_pages(struct frame* pdbr, void* vaddr, struct frame* frames[], size_t n, int flags);`
- `void *map_io(phys_t ioadddr, size_t len);`
- `void unmap_pages(struct pdir *pdbr, void *vaddr, int n);`

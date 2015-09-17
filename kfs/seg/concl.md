# Assignments

## Assignments

- `int set_gdt_entry(int n, uint32_t base, uint32_t limit, uint8_t access.
    uint8_t granularity);`
    - `n`: entry index
    - `base`: segment base address
    - `limit`: segment limit
    - `access`: segment access attributes
    - `granularity`: segment limit granularity

## Assignments

- `void init_flat_gdt(void);`

1) Null segment
2) Kernel code segment
3) Kernel data segment

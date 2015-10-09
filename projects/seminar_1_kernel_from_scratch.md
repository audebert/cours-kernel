# Kernel Programming II - Kernel From Scratch

## Introduction

Here is the assigments for *Kernel Programming II - Kernel From Scratch*.

    To: halfr@lse.epita.fr, surply@lse.epita.fr`
    Subject: [KERNEL] LOGIN_X LOGIN_Y - KFS

The specifications described below should be be considered as guidelines.
This is not mandantory to perfectly fit this API but is highly recommended.

### Summary

- Segmentation
- Interrupts handling
- Keyboard driver
- Timer driver

## Segmentation

### Brief

Firstly, you have to configure segmentation in order to get a flat memory model.

- *Reference*: Intel Manual 3A Chapter 3
- *File*: src/segmentation.c
- *Header*: inc/segmentation.h

### Functions

- `int set_gdt_entry(int n, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity);`
    - *Description*: Set a GDT entry.
    - *Arguments*:
        - `n`: entry index
        - `base`: segment base address
        - `limit`: segment limit
        - `access`: segment access attributes
        - `granularity`: segment limit granularity

- `void init_flat_gdt(void)`
    - *Description*: This function sets a GDT in order to get a flat memory
        model. It must reloads the segment selectors according to the new GDT.
        A minimal GDT will be:
        1) Null segment
        2) Kernel code segment
        3) Kernel data segment

## Interrupts

### Brief

In protected mode, interrupts are handled thanks to an Interrupt Descriptor
Table. These functions allow the initialization of this structure.

- *File*: src/interrupts.c
- *Header*: inc/interrupts.h

### Types

- `struct regs;`
    - *Description*: A struct which hold a context
    (registers, segment selectors, flags, ...).
- `int (*irq_handler)(struct regs* regs);`
    - *Description*: A pointer to an IRQ handler
    - *Arguments*:
        - `regs`: saved context

### Functions

- `void interrupts_init(void);`
    - *Description*: Initialize an IDT and fill it with interrupt gates.
        The first 32 entries must point to a default ISR handler which
        prints the cause of the exception, the saved context and the error code.
        The others must be set as "not present".

- `void interrupts_set_isr(int n, isr_handler handler, int flags);`
    - *Description*:
    - *Arguments*:
        - `n`: interrupt index
        - `handler`: pointer to the IRQ handler
        - `flags`:
            - `ISR_USER`: the user can call it

## IRQ

### Brief

Now that the IDT is set up, the external interrupts have to handled. This can
be achieved thanks to the Programmable Interrupt Controller which is
responsible for multiplexing interrupts from peripherals into one interrupt
line on the CPU.

- *Chip reference*: i8259A
- *File*: src/irq.c
- *Header*: inc/irq.h

### Functions

- `int irq_init(uint8_t base);`
    - *Description*: Initialize PIC and set global interrupt flag.
    - *Arguments*:
        - `base`: base offset in the IDT to use (*Hint*: the first 32 entries
        are reserved).

- `void irq_mask(int irq);`
    - *Description*: Mask an IRQ (*Hint*: use *OCW1*)
    - *Arguments*:
        - `irq`: irq number

- `void irq_unmask(int irq);`
    - *Description*: Unmask an IRQ (*Hint*: use *OCW1*)
    - *Arguments*:
        - `irq`: irq number

- `void irq_send_eoi(void);`
    - *Description*: Send EOI command to PIC (*Hint*: use *OCW2*)

## Keyboard

### Brief

In order to test PIC configuration, you can write a simple keyboard
driver which is hooked on the IRQ1.

- *Chip reference*: i8042
- *File*: src/kb.c
- *Header*: inc/kb.h

### Functions

- `void kb_init(void);`
    - *Description*: Register and unmask an IRQ handler for keyboard events.

- `int kb_get_key(void);`
    - *Description*: Returns the key code of last pressed key.

## Programmable Interrupt Timer

### Brief

Once your keyboard driver is working, let's try to get some periodic
interrupts. This can be achieved by configuring the Programmable Interrupt
Timer.

- *Chip reference*: i8254
- *File*: src/pit.c
- *Header*: inc/pit.h

### Functions

- `int pit_init(int freq);`
    - *Description*: Configure PIT in mode 2 (rate generator) at a given
        frequency. Register and unmask an IRQ handler for timer events.
        (*Hint*: Input clock frequency is 1193182 Hertz)
    - *Arguments*:
        - `freq`: timer frequency (Hertz)

- `int pit_get_ticks(void);`
    - *Description*: Returns the number of ticks elapsed since the machine
      started.

## Bonus: Serial

### Brief

Try to improve your serial driver by handling UART interrupts.

- *File*: src/serial.c
- *Header*: inc/serial.h

### Functions

- `int uart_init(void);`
    - *Description*: Configure UART. Register and unmask an IRQ handler for
    - UART events.

- `void uart_send(uint8_t c);`
    - *Description*: Send a character using UART
    - *Arguments*:
        - `c`: character to be sent

- `uint8_t uart_recv(void);`
    - *Description*: Returns the last received character

## Conclusion

Corrections will take place in your computers.
Have fun :)

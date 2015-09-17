# PIC

## PIC Wiring

![](res/pic_overview.png)

## 8259 Overview

![](res/8259A_overview.png)

## Typical wiring of the PIC (Master)

- IRQ0 - PIT
- IRQ1 - Keyboard
- IRQ2 - Not assigned in PC/XT; cascaded to slave 8256
- IRQ3 - UART (COM2 and COM4)
- IRQ4 - UART (COM1 and COM3)
- IRQ5 - Hard disk in PC/XT; Parallel port LPT2 in PC/AT
- IRQ6 - Floppy disk controller
- IRQ7 - Parallel port LPT1

## Typical wiring of the PIC (Slave)

- IRQ8 - RTC
- IRQ9 -
- IRQ10 -
- IRQ11 -
- IRQ12 - PS/2 mouse controller
- IRQ13 - Math coprocessor
- IRQ14 - Hard disk controller 1
- IRQ15 - Hard disk controller 2

## Interrupt acknowledge (8086/8088)

![](res/pic_ack.eps)

## PIC ports

- `0x20`, the master PIC's port A
- `0x21`, the master PIC's port B
- `0xA0`, the slave PIC's port A
- `0xA1`, the slave PIC's port B

## PIC Initialization

![](res/pic_init.png)

## ICW1

![](res/pic_icw1.png)

## ICW2

![](res/pic_icw2.png)

## ICW3

![](res/pic_icw3.png)

## ICW4

![](res/pic_icw4.png)

## OCW1

![](res/pic_ocw1.png)

## OCW2

![](res/pic_ocw2.png)

# Keyboard

## 8042 Controller

- `0x60`: I/0 buffer
- `0x64`: Status register

## 8042 Status Register

![](res/8042_status.eps)

## Keyboard scancode

    x x x x x x x x
    | -------------
    |       |
    |       +--------- Key number
    +----------------- Key press (clear) or release (set)

# Timer

## 8254 Overview

![](res/8254_overview.png)

## Programmable Interval Timer

- Counter 0: fire an interrupt at a user-defined frequency.
- Counter 1: historically used in order to periodically refresh the RAM, but it not used anymore.
- Counter 2:  linked with the PC speaker, so you can use it in order to generate sound

## PIT Registers

- `0x40` : Counter 0
- `0x41` : Counter 1
- `0x42` : Counter 2
- `0x43` : Control Register

## PIT Configuration

![](res/pit_cw.png)

## PIT Operation Modes

- Mode 0: Interrupt on terminal count
- Mode 1: hardware retriggerable one-shot
- Mode 2: rate generator
- Mode 3: square generator
- Mode 4: Software Triggered Strobe
- Mode 5: Hardware Triggered Strobe

## PIT - Mode 2

![](res/pit_mode2.png)

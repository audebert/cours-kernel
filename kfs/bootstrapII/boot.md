# C features

## Inline assembly

- `__asm__()` or `asm()`
- `__asm__ ("mov $0, %eax\n");`

```
__asm__("[your assembly code]"
    : output operands /* optional */
    : input operands /* optional */
    : list of clobbered /* optional */
);
```

## Inline assembly

```
__asm__ volatile ("mov $0, %eax\n");
```

## Inline assembly

### Different output/input constraints:

- "m" : memory operand
- "r" : register operand

### Constraint modifiers

- "=" : Write Only
- "+" : Read/Write

### Different clobbers

- memory
- register names

## Bitfields

	struct {
		unsigned int field_a : 1; // max value is 0b1
		unsigned int field_b : 2; // max value is 0b11
		unsigned int field_c : 5; // max value is 0x1F
	} bitfields;

`sizeof(bitfields)` is equal to `sizeof(char)`.

## Packed Structs

### Not Packed

```
struct foo {
    unsigned char   a; /* 0 1 */
    unsigned int    b; /* 4 4 */
    unsigned char   c; /* 8 1 */

    /* size: 12 */

};
```

## Packed Structs

### Packed

```
struct foo {
    unsigned char	a; /* 0 1 */
    unsigned int	b; /* 1 4 */
    unsigned char	c; /* 5 1 */

    /* size: 6 */

}__attribute__((packed));
```

# I/O Ports

## I/O Ports

![](res/addr_space.png)

## I/O Ports

    asm volatile("outb %0, %1\n\t"
                : /* No output */
                : "a" (val), "d" (port));

    asm volatile("inb %1, %0\n\t"
                : "=a" (res)
                : "d" (port));

# Framebuffer

## VGA

- Video memory: `0xA0000` to `0xBFFFF`
- Text mode (3h):
    - Buffer starts at `0xB8000`
    - 25 rows of 80 columns
- Video mode (13h):

![](res/font.png)

## VGA

```
struct vga_text_char {
    uint16_t ascii_code             : 8;
    uint16_t fg_color_rgb           : 3;
    uint16_t fg_color_intensity     : 1;
    uint16_t bg_color_rgb           : 3;
    uint16_t bg_color_intensity     : 1;
} __attribute__(packed);
```

## VGA

```
char* video_mem = (void*) 0xb8000;
video_mem[(0 * 80 + 11) * 2] = 'k';
video_mem[(0 * 80 + 11) * 2 + 1] = 0x14;
```

![](res/framebuffer.png)

## Moving the cursor

```
uint_16 pos = (row * 80) + col;

outb(0x3D4, 0x0F);
outb(0x3D5, (uint8_t) (position & 0xFF));

outb(0x3D4, 0x0E);
outb(0x3D5, (uint8_t) ((position >> 8) & 0xFF));
```

# Serial Ports

## Parallel bus

![](res/comm1.eps)

## Synchronous serial bus

![](res/comm2.eps)

## Asynchronous serial bus

![](res/comm3.eps)

## 16650 UART

![](res/16650.png)

## 16650 Registers

- `RBR/THR`: Receive/Transmit buffer
- `IER`: Interrupt Enable Register
- `IIR`: Interrupt Identification Register
- `FCR`: FIFO Control Register
- `LCR`: Line Control Register (DLAB)
- `MCR`: Modem Control Register
- `LSR`: Line Status Register
- `MSR`: Modem Status Register
- `SCR`: Scratch Register

## IBM-PC Serial Ports

+----------+---------+
| COM Port | IO Port |
+==========+=========+
| `COM1`   | `3F8h`  |
+----------+---------+
| `COM2`   | `2F8h`  |
+----------+---------+
| `COM3`   | `3E8h`  |
+----------+---------+
| `COM4`   | `2E8h`  |
+----------+---------+

## IBM-PC Serial Ports Register

\scriptsize

+------------------+-------------+---------+------------+
| IO Port Offset   | DLAB        | Type    | Register   |
+==================+=============+=========+============+
| 0                | 0           | R       | RBR        |
+------------------+-------------+---------+------------+
| 0                | 0           | W       | THR        |
+------------------+-------------+---------+------------+
| 0                | 1           | R/W     | DLL        |
+------------------+-------------+---------+------------+
| 1                | 1           | R/W     | DLM        |
+------------------+-------------+---------+------------+
| 2                | X           | W       | FCR        |
+------------------+-------------+---------+------------+
| 3                | X           | R/W     | LCR        |
+------------------+-------------+---------+------------+
| 4                | X           | R/W     | MCR        |
+------------------+-------------+---------+------------+
| 5                | X           | R/W     | LSR        |
+------------------+-------------+---------+------------+
| 6                | X           | R/W     | MSR        |
+------------------+-------------+---------+------------+

\normalsize

## Line Protocol

- Baud Rate

$$Baudrate = \frac{115200}{DLM:DLL}$$

- Word Length
- Stop Bits
- Parity

## Serial on Qemu

- -serial *dev*
    - pty : Pseudo TTY (Linux only)
    - stdio : standard input/output

# Assignments

## Assignments

### Line Protocol

- 38400 bauds
- 8N1
    * 8 bits
    * No parity check
    * 1 stop bit
- No hardware flow control

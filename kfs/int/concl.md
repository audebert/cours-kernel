# Assignments

## Summary

- Build IDT
- Write context saving/restoring in assembly code
- Implement exceptions and interrupt wrappers
- Load IDT
- Initialize PIC
    - send ICWs to both master and slave
    - mask all interrupts
- Set keyboard interrupt handler
- Initialize PIT
    - Send CW
    - Set PIT interrupt handler

## Assignments

- `void interrupts_init(void);`
- `void interrupts_set_isr(int n, isr_handler handler, int flags);`

## Assignments

- `int irq_init(uint8_t base);`
- `void irq_mask(int irq);`
- `void irq_unmask(int irq);`
- `void irq_send_eoi(void);`

## Assignments

- `void kb_init(void);`
- `int kb_get_key(void);`

## Assignments

- `int pit_init(int freq);`
- `int pit_get_ticks(void);`

## Assignments (Bonus)

- `int uart_init(void);`
- `void uart_send(uint8_t c);`
- `uint8_t uart_recv(void);`

# Introduction

## Flat memory model

![](res/mem_model_flat.eps)

## Segmentation

![](res/seg_addr.eps)

## Segmentation

![](res/seg_overview.eps)

# Real-mode segmentation

## Segment selectors

![](res/regs_ss.png)

## Real-mode segmentation

![](res/real_mode_addr.eps)

## Segmented memory model

![](res/mem_model_real.eps)

# 80286 Protected mode

## 80286 Protected mode

![](res/seg_286.eps)

## Segmentation

![](res/addr_mode_calc.png)

## 80286 Protected mode

![](res/gdte_286.eps)

# 80386 Protected mode

## 80386 Protected mode

![](res/addr_transl.png)

## GDT Entry

![](res/gdte.eps)

## Entry Types and Permissions

![](res/gdte_type.eps)

## GDTR register

![](res/gdtr.eps)

## Loading GDT

	gdt_r gdtr;

	gdtr.base = gdt;		/* gdt base address */
	gdtr.limit = sizeof(gdt) - 1	/* gdt size - 1 */

	__asm__ volatile("lgdt %0\n"
			  : /* no output */
			  : "m" (gdtr)
			  : "memory");

## x86 modes

![](res/modes.eps)

## Switching to Protected Mode

![](res/cr0.png)

## Switching to Protected Mode

    movl $0x42, %cr0  ; It _won't_ assemble

    movl $0x42, %eax
    movl %eax, %cr0   ; OK

## Segment selectors

![](res/ss.eps)

## Segment selectors

![](res/ss_detail.png)

## Segment selectors reloading

    movw $0x42, %ax
    movw %ax, %ds
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss

## Segment selectors reloading

    pushl $0x42       ; push %cs on the stack
    pushl $1f         ; push %eip on the stack
    lret              ; far return
    1:                ; After the lret you will get
                        here, with cs set to 0x42

    ljmp $0x42, %1    ; long jump
    1:

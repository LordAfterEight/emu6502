.segment "CODE"
reset:
    lda #$A9
    pha
    and $100
    brk
    jmp reset

.segment "VECTORS"
    .word 0       ; NMI vector
    .word reset   ; RESET vector
    .word 0       ; IRQ vector

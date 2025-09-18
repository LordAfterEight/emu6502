.segment "CODE"
reset:
    lda #$A1
    and #$A3
    pha
    lda $0
    brk
    jmp reset

.segment "VECTORS"
    .word 0       ; NMI vector
    .word reset   ; RESET vector
    .word 0       ; IRQ vector

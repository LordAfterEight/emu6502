.segment "CODE"
reset:
    lda $2099
    jmp reset     ; infinite loop so CPU doesn't run into garbage

.segment "VECTORS"
    .word 0       ; NMI vector
    .word reset   ; RESET vector
    .word 0       ; IRQ vector

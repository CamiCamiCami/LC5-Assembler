;; Sets r to
;; <0, if a<b
;; =0, if a==b
;; >0, if a>b
;; Follows the conventions of C's qsort function
;; and Java's comparable interface.
suma        add     r2,r7,r3
resta       sub     r0,r1,r6
ylog        ANd     r6,r3,r1
olog        Or      r1,r2,r3
sumai1      addi    r1,r7,#12
sumai2      addi    r1,r7,b101010
sumai3      addi    r1,r7,x3F
sumai4      addi    r1,r7,-1
ylogi       andi    r1,r2,2,0b1111
ologi       ori     r1,r2,1,0b0000
bran        brp     suma
            brZ     load
            brn     bran
saltoRs      JR      r1
subproc     JALR    r3
oscall      TRAP    r7
return      RETI
neg         Not     r1,r3
saltoL      jal     sumai2
load        LD      r3,oscall
store       ST      r3,neg
loadR       LDR     r1,r2,r3
storeR      STR     r1,r2,r3
luisi       LUI     r4,-3
lorenzo     Lori    r4,#45
saltoLar    LJMP    suma

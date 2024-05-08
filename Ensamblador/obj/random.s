;; Sets r to
;; <0, if a<b
;; =0, if a==b
;; >0, if a>b
;; Follows the conventions of C's qsort function
;; and Java's comparable interface.

        lui         r0,b00000000
        Lori        r0,b00000000
        lui         r1,b00000000
        Lori        r1,b00000000
        lui         r2,b00000000
        Lori        r2,b00000000

        addi        r1,r1,10
        addi        r2,r2,3 
loop    add         r0,r0,r1
        addi        r2,r2,-1
        brz         exit
        LJMP        loop

exit    TRAP        r7
        trap        r0

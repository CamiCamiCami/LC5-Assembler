;; Sets r to
;; <0, if a<b
;; =0, if a==b
;; >0, if a>b
;; Follows the conventions of C's qsort function
;; and Java's comparable interface.

        lui         r0,b00000000
        Lori        r0,b00000100

        addi        r0,r0,5

        TRAP        r7
        trap        r0

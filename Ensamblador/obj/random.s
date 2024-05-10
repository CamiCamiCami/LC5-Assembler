;; Sets r to
;; <0, if a<b
;; =0, if a==b
;; >0, if a>b
;; Follows the conventions of C's qsort function
;; and Java's comparable interface.

        .orig       2000

        ld          r1,m1
        ld          r2,m2

        lui         r0,0
        Lori        r0,0

loop    add         r0,r0,r1
        addi        r2,r2,-1
        brz         exit
        ljmp        loop
        
exit    st          r0,fin
        TRAP        r7
        trap        r0

m1      .fill       7
m2      .fill       3
        .fill       b1111111111111111
fin     .blkw       2
        .fill       xFFFF
        .end

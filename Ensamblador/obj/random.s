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

       .fill "pppp"

loop    add         r0,r0,r1
        addi        r2,r2,-1
        brz         save
        ljmp        loop
        
save    ld          r3,loc
        lui         r4,0
        lori        r4,0
        str         r0,r3,r4
        addi        r4,r4,1
        str         r0,r3,r4        

exit    TRAP        r7
        trap        r0

m1      .fill       7
m2      .fill       3
loc     .fill       space
space   .blkw       2
        .fill       b101010101010
        .end

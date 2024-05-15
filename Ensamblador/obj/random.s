;; Sets r to
;; <0, if a<b
;; =0, if a==b
;; >0, if a>b
;; Follows the conventions of C's qsort function
;; Holis

        .orig       2000

        lui         r0,0
        Lori        r0,0

        lui         r1,0
        lori        r1,0

        ld          r2,dir

print   ldr         r0,r2,r1
        brz         exit
        trap        r7
        addi        r1,r1,1
        ljmp        print

exit    TRAP        r0

dir     .fill       text
        .fill       xFFFF
text    .stringz    "Hola Mundo\n"
        .end

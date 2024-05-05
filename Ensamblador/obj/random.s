;; Sets r to
;; <0, if a<b
;; =0, if a==b
;; >0, if a>b
;; Follows the conventions of C's qsort function
;; and Java's comparable interface.
    b        ld      R1,a
c        ld      R2,b
        not     R2,R2
 e        add     R2,R2,#1
 f        add     R2,R1,R2      ;; R2 <- a-b
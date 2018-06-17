( defun factorial (N)
    (write N)
    (write-line " ")
    (if (= N 0) ;Ha N = 0
        1   ;Akkor 1-gyel szorzás
        (* N (factorial (- N 1)))   ;Egyébként rekurzió
        ;N * factorial(N - 1)
    )
)
(write (factorial 5))

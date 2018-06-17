(defun iterfact (n)
    ;let lokális változó
    (let ((prod 1))

        (loop for i from 2 to n do
            (setf prod (* prod i )))
            ;prod = prod * i
    prod))

(write (iterfact 5))

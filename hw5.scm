(define shift-left
  (lambda (x)
    (if (not(null? x))
      (append (cdr x) (list(car x)))
      x
    )
  )
)

(define shift-right
  (lambda (x)
    (if (not(null? x))
      (reverse (append (cdr (reverse x)) (list(car (reverse x)))))
      x
    )
  )
)

(define count
  (lambda (mem l)
    (define recursion
      (lambda (mem n counter)
        (define cow counter)
        (cond
          ((not(null? n)) 
            (if (equal? mem (car n))
              (recursion mem (cdr n) (+ cow 1))
              (recursion mem (cdr n) cow)
            )
          )
          ( else counter)
        )
      )
    )
    (recursion mem l 0)
  )
)

(define formatDate
  (lambda (dates)
    (define createString
      (lambda (date)
          (cond
            ((equal? "January" date) "1")
            ((equal? "Febuary" date) "2")
            ((equal? "March" date) "3")
            ((equal? "April" date) "4")
            ((equal? "May" date) "5")
            ((equal? "June" date) "6")
            ((equal? "July" date) "7")
            ((equal? "August" date) "8")
            ((equal? "September" date) "9")
            ((equal? "October" date) "10")
            ((equal? "November" date) "11")
            ((equal? "December" date) "12")
            (else (number->string date))
          )
      )
    )
    (define stringList '())
    (define dateRecur
      (lambda (dateList)
        (append stringList (string-append (createString (car dateList)) "/" (createString (cadr dateList)) "/" (createString (caddr dateList)))
        )
      )
    )
    (if (not(null? dates))
        (map dateRecur dates)
    )
  )
)

(define divideAll
  (lambda (div)
    (define filtered (filter (lambda (x) (not(equal? x 0))) div))
    (if (not(null? filtered))
      (apply / filtered)
      "Nothing to divide by"
    )
  )
)

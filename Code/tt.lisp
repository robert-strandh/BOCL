(defun ff (form)
  (cond ((symbolp form)
         (multiple-value-bind (expansion expanded-p)
             (macroexpand-1 form)
           (if expanded-p
               (ff expansion)
               form)))
        ((atom form)
         form)
        ((symbolp (first form))
         (multiple-value-bind (expansion expanded-p)
             (macroexpand-1 form)
           (if expanded-p
               (ff expansion)
               (case (first form)
                 ((block return-from eval-when setq)
                  (list* (first form)
                         (second form)
                         (loop for subform in (rest (rest form))
                               collect (ff subform))))
                 ((flet labels)
                  (list* (first form)
                         (loop for definition in (second form)
                               collect (destructuring-bind (name lambda-list . body)
                                           definition
                                         (list* name
                                                lambda-list
                                                (loop for body-form in body
                                                      collect (ff body-form)))))
                         (loop for body-form in (rest (rest form))
                               collect (ff body-form))))
                 ((function go quote)
                  form)
                 ((let let*)
                  (destructuring-bind (operator bindings . body)
                      form
                    (list* operator
                           (loop for binding in bindings
                                 collect (list (first binding)
                                               (ff (second binding))))
                           (loop for body-form in body
                                 collect (ff body-form)))))
                 ((tagbody)
                  (cons (first form)
                        (loop for element in (rest form)
                              collect (if (atom element)
                                          element
                                          (ff element)))))
                 (t
                  (cons (first form)
                        (loop for body-form in (rest form)
                              collect (ff body-form))))))))
        (t
         (destructuring-bind ((lambda lambda-list . body) . arguments)
             form
           (cons (list* lambda
                        lambda-list
                        (loop for body-form in body
                              collect (ff body-form)))
                 (loop for argument in arguments
                       collect (ff argument)))))))
                 

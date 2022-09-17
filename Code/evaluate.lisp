(defgeneric call (fun args dynenv))

(defclass fun ()
  ((%entry-point :initarg :entry-point :reader entry-point)))

(defclass primitive-fun (fun)
  ())

(defmethod call ((fun primitive-fun) args dynenv)
  (funcall (entry-point fun) args dynenv))

(defclass interpreted-fun (fun)
  ((%vars :initarg :vars :reader vars)
   (%funs :initarg :funs :reader funs)
   (%param :initarg :param :reader param)
   (%form :initarg :form :reader form)))

(defun enclose (entry-point vars funs param form)
  (make-instance 'interpreted-fun
    :entry-point entry-point
    :vars vars
    :funs funs
    :param param
    :form form))

(defun interpreter (args vars funs param form dynenv)
  (let ((new-vars (cons (cons param args) vars)))
    (evaluate form new-vars funs dynenv)))

(defmethod call ((fun interpreted-fun) args dynenv)
  (funcall (entry-point fun)
           args
           (vars fun)
           (funs fun)
           (param fun)
           (form fun)
           dynenv))

(defparameter *functions* (make-hash-table :test #'equal))

(defun fdef (name)
  (gethash name *functions*))

(defun (setf fdef) (fun name)
  (setf (gethash name *functions*) fun))

(defun evaluate (form vars funs dynenv)
  (cond ((or (numberp form)
             (characterp form)
             (keywordp form)
             (member form '(t nil) :test #'eq)
             (and (atom form) (not (symbolp form))))
         (list form))
        ((symbolp form)
         (let ((entry (assoc form vars :test #'eq)))
           (if (null entry)
               (error "Udefined variable ~s" form)
               (list (cdr entry)))))
        ((symbolp (car form))
         (case (car form)
           ((function)
            (if (and (consp (cadr form))
                     (eq (caadr form) 'lambda))
                (destructuring-bind (function (lambda (param) body-form))
                    form
                  (declare (ignore function lambda))
                  (enclose #'interpreter
                           vars funs param body-form))
                (let ((entry (assoc (cadr form) funs :test #'equal)))
                  (if (null entry)
                      (let ((fun (fdef (cadr form))))
                        (if (null fun)
                            (error "Undefined function named ~s" (car form))
                            fun))
                      (cdr entry)))))
           ((let)
            (let ((new-vars vars))
              (loop for (var init) in (second form)
                    do (push (cons var 
                                   (car (evaluate init vars funs dynenv)))
                             new-vars))
              (evaluate (third form) new-vars funs dynenv)))
           ((let*)
            (let ((new-vars vars))
              (loop for (var init) in (second form)
                    do (push (cons var
                                   (car (evaluate init new-vars funs dynenv)))
                             new-vars))
              (evaluate (third form) new-vars funs dynenv)))
           ((progn)
            (let ((values (list nil)))
              (loop for body-form in (rest form)
                    do (setq values (evaluate body-form vars funs dynenv)))
              values))
           ((quote)
            (cdr form))
           (otherwise
            (let ((args
                    (loop for argument-form in (cdr form)
                          collect (car (evaluate argument-form vars funs dynenv))))
                  (entry (assoc (car form) funs :test #'eq)))
              (if (null entry)
                  (let ((fun (fdef (car form))))
                    (if (null fun)
                        (error "Undefined function named ~s" (car form))
                        (call fun args dynenv)))
                  (call (cdr entry) args dynenv))))))
        (t
         (error "Unknown first element ~s" (car form)))))

;Morse Code middleware
;IN  hard/keyboard/+ 0-1
;OUT firm/keyboard/+ a-z

(let morse {".-" \a  "-..." \b  ...})
(var presses []  start 0  timer nil)

(fn send-char []
  (reset presses)
  (msg! "firm/keyboard/char"
    (morse (str (map #(if (> % 320) \- \.) presses)))))

(fn hard-in [topic payload]
  (clear-timeout! timer)
  (let diff-ms (- (time/now) start))
  (when (= 0 payload)
    (set presses (add presses diff-ms))
    (set timer (timeout! send-char 320))))

(hook! hard-in "hard/keyboard/+")	
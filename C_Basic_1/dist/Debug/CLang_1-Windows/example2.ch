;Morse code middleware
;IN  hard/keyboard/+ 0-1
;OUT firm/keyboard/+ a-z

(const morse {0x01 \a 0x1000 \b})
(let presses [] start 0 timer nil)

(fn ms->morse [arr-ms]
  (alias dashes (map @(<= 320) arr-ms))
  (reduce | (map << dashes (range))))

(fn send-char!
  (msg! "firm/keyboard/char"
    (morse (ms->morse presses)))
  (reset presses))

(fn hard-in [topic payload]
  (stop-timer! timer)
  (when (= 0 payload)
    (alias diff-ms (- (time/now) start))
    (set presses (add presses diff-ms))
    (set timer (timeout! send-char! 320))))

(hook! hard-in "hard/keyboard/+")
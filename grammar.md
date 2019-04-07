
Some definitions:
- EOL = end of line
- STR = any alphanumeric sequence of characters

#
**Old Grammar**

The grammar is quite simple:

      line  -> label
            -> label instr
            -> instr

      label -> STR ':'

      instr -> STR ops

      ops   -> STR ',' ops
            -> STR
            -> epsilon

#
**Up-to-date Grammar**

The new grammar (left factored) is as follows:

      line  -> STR rest
            -> EOL

      rest  -> colon
            -> ops

      colon -> ':' after

      after -> instr
            -> EOL

      instr -> STR ops

      ops   -> STR ',' ops
            -> STR
            -> EOL
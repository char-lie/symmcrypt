#!/usr/bin/runhaskell

import Data.Char (ord,chr)

firstLetter = 'а'
mostFrequentLetter = 'о'
lettersInAlphabet = 32

main =
    getLine >>= \line -> mapM_ (\c ->
            putStr$(show((ord c) - (ord firstLetter))++[' '])) line

#!/usr/bin/runhaskell
import CharactersStatistics
import Data.Char (ord,chr)

firstLetter = 'а'
mostFrequentLetter = 'о'
lettersInAlphabet = 32
main =
    getLine >>= \line -> mapM_ (decypher$mostFrequentCharacter line)
        ([chr$caesar firstLetter
            (-2*((ord mostFrequentLetter-(ord$mostFrequentCharacter line))))]
         ++ line)
    where
        mostFrequentCharacter l = fst ((sortedCharactersFrequencies l)!!0) 
        decypher base = \c -> putStr[chr$caesar c
            (ord mostFrequentLetter-(ord base))]
        caesar c shift = (ord c - ord firstLetter + shift)
            `mod` lettersInAlphabet + (ord firstLetter)

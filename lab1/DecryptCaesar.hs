#!/usr/bin/runhaskell
import CharactersStatistics
import Data.Char (ord,chr)

main =
    getLine >>= \line -> mapM_ (decypher$mostFrequentCharacter line) line
    where
        mostFrequentCharacter l = fst ((sortedCharactersFrequencies l)!!0) 
        decypher base = \c -> putStr[chr$caesar c (ord 'e' - (ord base))]
        caesar c shift = (ord c - ord 'a' + shift) `mod` 26 + (ord 'a')

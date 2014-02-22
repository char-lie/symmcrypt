#!/usr/bin/runhaskell
import CharactersStatistics
import Data.Char (ord,chr)

main =
    getLine >>= \line -> mapM_ (decypher$mostFrequentCharacter line) line
    where
        mostFrequentCharacter l = fst ((sortedCharactersFrequencies l)!!0) 
        decypher base = \c -> putStr[chr$caesar c (ord 'о' - (ord base))]
        caesar c shift = (ord c - ord 'а' + shift) `mod` 32 + (ord 'а')

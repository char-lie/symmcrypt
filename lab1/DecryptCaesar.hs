#!/usr/bin/runhaskell
import CharactersStatistics
import Data.Char (ord,chr)

firstLetter = 'а'
mostFrequentLetter = 'о'
lettersInAlphabet = 32
main =
    getLine >>= \line -> mapM_
        (decypher$mostFrequentCharacter line)
        ([caesar firstLetter (-2*(mflo-(mfco line)))] ++ line)
    where
        mostFrequentCharacter l = fst ((sortedCharactersFrequencies l)!!0) 
        mflo = ord mostFrequentLetter
        mfco = ord.mostFrequentCharacter
        getShift base = (mflo-(ord base))
        decypher base = \c -> putStr [caesar c (getShift base)]
        caesar c shift = chr$(ord c - ord firstLetter + shift)
            `mod` lettersInAlphabet + (ord firstLetter)

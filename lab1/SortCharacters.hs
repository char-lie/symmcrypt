#!/usr/bin/runhaskell
import CharactersStatistics
import Data.Ord
import Data.List
import Data.Char (ord,chr)

main =
    getLine >>= \line -> mapM_ (decypher$array line) line
    where
        array line = sortBy (comparing cmpDesc) (charactersFrequencies line)
        decypher line = \x -> putStr[chr$caesar x (ord 'о' - (ord$fst (line!!0)))]
        cmpDesc x  = -(snd x)
        caesar x shift = (ord x - ord 'а' + shift) `mod` 32 + (ord 'а')

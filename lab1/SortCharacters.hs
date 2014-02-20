#!/usr/bin/runhaskell
import WordsStatistics
import Data.Ord
import Data.List

main = getLine >>= (\line -> putStr $ show $
        sortBy (comparing snd) (charactersFrequencies line))

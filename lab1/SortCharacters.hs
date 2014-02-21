#!/usr/bin/runhaskell
import CharactersStatistics
import Data.Ord
import Data.List

main = getLine >>= (\line -> putStr $ show $
        sortBy (comparing snd) (charactersFrequencies line))

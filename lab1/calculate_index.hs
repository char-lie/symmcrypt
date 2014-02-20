#!/usr/bin/runhaskell
import WordsStatistics

nn_1 n = n * (n-1)

main = getLine >>= (\line -> putStr $ show $
        foldl (\x y -> x + (nn_1 $ snd y)) 0 (charactersFrequencies line) /
        (nn_1 $ fromIntegral $ length line))

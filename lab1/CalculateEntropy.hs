#!/usr/bin/runhaskell
import CharactersStatistics

main =
    getLine >>= (\line -> putStr $ show $
            -foldl (\x y ->
                x + (entropyIteration ((snd y)/(fromIntegral$length line))))
                    0 (charactersFrequencies line))
    where entropyIteration x = x * (logBase 2 x)

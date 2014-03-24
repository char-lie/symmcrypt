#!/usr/bin/runhaskell
import CharactersStatistics

main =
    getLine >>= (\line -> putStr $
        foldl (\x y -> x++[[fst y]++":"++(show$snd$y)++" "]) []
            (charactersFrequencies line))

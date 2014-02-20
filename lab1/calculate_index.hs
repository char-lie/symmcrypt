#!/usr/bin/runhaskell
import Data.Map

calculate_ [] n = n
calculate_ (x:xs) n = calculate_ (xs) (n + (snd x) * ((snd x) - 1))

calculate charArray = calculate_ charArray 0

strStatistics str = (toList $ fromListWith (+) [(c, 1) | c <- str])

sqrLength :: String -> Double
sqrLength str = fromIntegral ((length str)*(length str))

calculateM str = calculate (strStatistics str) / ((fromIntegral$length str) * ((fromIntegral$length str) -1))

main :: IO()
main = do
    line <- getLine
    putStr $ show $ calculateM line--truncate ((calculateM line)*1000)

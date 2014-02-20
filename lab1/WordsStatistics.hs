module WordsStatistics where
import Data.Map

charactersFrequencies str = (toList $ fromListWith (+) [(c, 1) | c <- str])

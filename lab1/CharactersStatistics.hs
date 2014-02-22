module CharactersStatistics where
import Data.Map
import Data.Ord
import Data.List

charactersFrequencies str = (toList $ fromListWith (+) [(c, 1) | c <- str])
sortedCharactersFrequencies str =
    sortBy (comparing cmpDesc) (charactersFrequencies str)
    where
        cmpDesc tuple = -(snd tuple)

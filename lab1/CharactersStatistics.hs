module CharactersStatistics where
import Data.Map
import Data.Ord
import Data.List

listToPairs (a:b:xs) = [[a,b]] ++ (listToPairs xs)
listToPairs [_] = []
listToPairs [] = []

listToChainedPairs (a:b:xs) = [[a,b]] ++ (listToChainedPairs ([b]++xs))
listToChainedPairs [_] = []
listToChainedPairs [] = []

couplesToFrequencies couples = toList $ fromListWith (+) couples

elementsFrequencies lst = couplesToFrequencies [(e, 1) | e <- lst]

charactersFrequencies str = elementsFrequencies str


bigramsFrequencies str = elementsFrequencies $ listToPairs str

chainedBigramsFrequencies str = elementsFrequencies $ listToChainedPairs str

sortedFrequencies lst = sortBy (comparing cmpDesc) lst
    where cmpDesc couple = -(snd couple)

sortedCharactersFrequencies str = sortedFrequencies$charactersFrequencies str

sortedBigramsFrequencies str = sortedFrequencies$bigramsFrequencies str

sortedChainedBigramsFrequencies str =
    sortedFrequencies$chainedBigramsFrequencies str

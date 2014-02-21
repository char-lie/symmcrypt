EXACUTABLES=CalculateIndex

remove_garbage:
	rm *.o *.hi -f

clean:
	rm $(EXACUTABLES) -f

CalculateIndex: CharactersStatistics.hs CalculateIndex.hs
	ghc CalculateIndex.hs
	make remove_garbage

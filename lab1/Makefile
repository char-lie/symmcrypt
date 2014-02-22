EXACUTABLES=CalculateIndex DecryptCaesar

remove_garbage:
	rm *.o *.hi -f

clean:
	rm $(EXACUTABLES) -f

CalculateIndex: CharactersStatistics.hs CalculateIndex.hs
	ghc CalculateIndex.hs
	make remove_garbage

DecryptCaesar: CharactersStatistics.hs DecryptCaesar.hs
	ghc DecryptCaesar.hs
	make remove_garbage

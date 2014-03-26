#!/usr/bin/python
# -*- coding: utf-8 -*-
from sys import stdin, argv
from correct_vigenere import FIRT_LETTER_ORD, LETTERS_COUNT, caesar_shift, process_input

def print_usage():
    print '''USAGE:
    %s KEY1 KEY2 ... KEYn

    KEYi are non-negative numbers
    Uses STDIN for input and STDOUT for output
    '''%(argv[0])


if __name__ == '__main__':
    if len(argv)>1 and (argv[1] == '--h' or argv[1] == '--help'):
        print_usage()
        exit(0)
    input_data = unicode(raw_input(), 'utf-8').strip()
    if (len(argv)<2):
        print input_data.encode('utf-8')
    key = []
    for i in range(1,len(argv)):
        key.append(int(argv[i]))
    output = process_input(input_data,
                lambda i, character: caesar_shift(character,key[i%len(key)]))
    print output.encode('utf-8')

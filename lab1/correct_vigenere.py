#!/usr/bin/python
# -*- coding: utf-8 -*-
from sys import stdin, argv

FIRT_LETTER_ORD = ord(u'а')
LETTERS_COUNT = 32

def caesar_shift(character, shift):
    char_number = (ord(character) - FIRT_LETTER_ORD + shift) % LETTERS_COUNT
    return unichr(char_number + FIRT_LETTER_ORD)

def process_input(input_text, f):
    output_text = u''
    for i, character in enumerate(input_text):
        output_text += f(i,character)
    return output_text

def print_usage():
    print '''USAGE:
    %s SOURCE_LETTER DESTINATION_LETTER VIGENERE_KEY_LENGTH LETTER_POSITION
or  %s LETTER_SHIFT VIGENERE_KEY_LENGTH LETTER_POSITION

    Text will be read from STDIN and printed to STDOUT
    '''%(argv[0],argv[0])

if __name__ == '__main__':
    offset=0
    step=1
    shift=0
    cur_arg=2
    if (len(argv)>1):
        if argv[1] == '--h' or argv[1] == '--help':
            print_usage()
            exit(0)
        try:
            shift=int(argv[1])
        except Exception:
            shift = ord(unicode(argv[2],'utf-8'))-ord(unicode(argv[1],'utf-8'))
            cur_arg += 1
    if (len(argv)>cur_arg):
        step=int(argv[cur_arg])
        cur_arg+=1
    if (len(argv)>cur_arg):
        offset=int(argv[cur_arg])
    input_data = unicode(raw_input(), 'utf-8').strip()
    if (shift is 0):
        print input_data.encode('utf-8')
    output = process_input(input_data,
            lambda i, character:
                caesar_shift(character,shift) if (i-offset%step is 0) else character)
    print output.encode('utf-8')

#!/usr/bin/python
# -*- coding: utf-8 -*-
from sys import stdin, argv

def caesar_shift(character, shift):
    char_number = (ord(character) - ord(u'a') + shift) % 26
    return unichr(char_number + ord(u'a'))

if __name__ == '__main__':
    offset=0
    step=1
    shift=0
    cur_arg=2
    if (len(argv)>1):
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
    output = u''
#for i in range(offset, len(input_data), step):
    for i, character in enumerate(input_data):
        if (i-offset)%step is 0:
            output+=caesar_shift(character,shift)
        else:
            output+=character
    print output.encode('utf-8')

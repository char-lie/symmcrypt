#!/usr/bin/python
# -*- coding: utf-8 -*-
from sys import stdin, argv

def print_usage():
    print '''USAGE: %s [r=1]

    Uses STDIN for input and STDOUT for output
    '''%(argv[0])

if __name__ == '__main__':
    if len(argv)>1 and (argv[1] == '-h' or argv[1] == '--help'):
        print_usage()
        exit(0)
    r = 1
    if (len(argv)>1):
        r=int(argv[1])
    input_data = unicode(raw_input(), 'utf-8').strip()
    result = 0
    for i in range(len(input_data)-r):
        if input_data[i] == input_data[i+r]:
            result += 1
    print result

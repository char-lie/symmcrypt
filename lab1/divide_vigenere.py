#!/usr/bin/python

# -*- coding: utf-8 -*-

from sys import argv

if __name__ == '__main__':
    modulus = 1
    offset  = 0
    if (len(argv)>1):
        modulus = int(argv[1])
    if (len(argv)>2):
        offset  = int(argv[2])
    str1 = raw_input() #.encode('utf-8')[offset::modulus]
    print unicode(str1,'utf-8')[offset::modulus].encode('utf-8')

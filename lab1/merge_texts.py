#!/usr/bin/python
from sys import stdin

if __name__ == '__main__':
    input_data = [unicode(line[:-1], 'utf-8') for line in stdin]
    output_text = ''
    for i in range(len(input_data[0])):
        for line in input_data:
            if len(line)>i:
                output_text += line[i]
    print output_text

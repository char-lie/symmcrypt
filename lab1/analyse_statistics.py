#!/usr/bin/python

from sys import stdin;

if __name__ == '__main__':
    data = [[i]+map(float, l.strip().split(' ')) for i, l in enumerate(stdin,1)]
    data.sort(key = lambda line: line[1])
    data = filter(lambda line: line[1]>=data[-1][3], data)
    data.sort(key = lambda line: line[2])
    for (r, mean, deviation, minimum, maximum) in data:
        print r, mean, deviation, minimum, maximum

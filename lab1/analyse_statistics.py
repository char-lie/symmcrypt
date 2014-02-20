#!/usr/bin/python

from sys import stdin;

if __name__ == '__main__':
    data = list()
    i = 0
    for line in stdin:
        i+=1
        data.append([i]+map(float, line.strip().split(' ')))
    data.sort(key = lambda line: line[1])
    propably_right_data = filter(lambda line: line[1]>=data[-1][3], data)
    propably_right_data.sort(key = lambda line: line[2])
    for (r, mean, deviation, minimum, maximum) in propably_right_data:
        print r, mean, deviation, minimum, maximum

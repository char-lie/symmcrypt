#!/usr/bin/python

if __name__ == '__main__':
    data = map(float, raw_input().strip().split(' '))
    mean = float(sum(data))/len(data)
    dispersion = reduce(lambda disp, x: disp+(x-mean)*(x-mean),data,0)
    print mean, dispersion, min(data), max(data)

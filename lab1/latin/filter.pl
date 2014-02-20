#!/usr/bin/perl -w
$_ = lc join('', <>);
s/[^a-z]//g;
print;

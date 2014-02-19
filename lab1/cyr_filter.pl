#!/usr/bin/perl -w -CAS
use utf8;
$_ = lc join('', <>);
s/[^а-я]//g;
print;

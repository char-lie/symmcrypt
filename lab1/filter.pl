#!/usr/bin/perl -w -CAS
use utf8;
$_ = lc join('', <>);
s/ё/е/g;
s/[^а-яa-z]//g;
print;

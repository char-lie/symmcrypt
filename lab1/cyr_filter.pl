#!/usr/bin/perl -w -CAS
use utf8;
$_ = join('', <>);
s/[^а-я]//g;
print;

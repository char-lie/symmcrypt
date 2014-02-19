#!/usr/bin/perl -w -CAS
use utf8;
my $str = '';
while(<>) {
    $str .= lc $_;
}
$str =~ s/[^а-я]//g;
print "$str\n";

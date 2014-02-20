#!/usr/bin/perl -w
my $text = join('', <>);
@text =~ m/../g;
$index = 1;
while ($#text>0) {
    $tmp = ($text =~ s/join('', @text[0,1])//g);
    $index *= $tmp*$tmp;
}
print $index;

#!/usr/bin/perl

use strict;
use warnings;

my $counter = 0;

while ( $counter < 99 ) {
  $counter++;
 system("./dsqgen -template query$counter.tpl -directory ./query_templates/ -dialect greenplum -scale 1 -verbose -output_dir ./dsqueries/");
 system("mv ./dsqueries/query_0.sql ./dsqueries/query_$counter.sql");
 }

exit;

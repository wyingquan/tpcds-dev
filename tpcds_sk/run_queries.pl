#!/usr/bin/perl

use strict;
use warnings;

my $counter = 0;

while ( $counter < 99 ) {
 $counter++;

 #next if ($counter == 10 ); # LONG RUNNING?
 #next if ($counter == 35 ); # LONG RUNNING?
 #next if ($counter == 95 ); # LONG RUNNING?
 #next if ($counter == 36 ); # ERROR:  column "lochierarchy" does not exist
 #next if ($counter == 70 ); # ERROR:  column "lochierarchy" does not exist
 #next if ($counter == 86 ); # ERROR:  column "lochierarchy" does not exist
 print "Running query_$counter.sql\n";
 system("psql tpcds -f ./dsqueries/query_$counter.sql");
 }

exit;

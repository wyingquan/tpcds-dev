#!/bin/sh 
while read table ab sc child
do
if [ $sc = "NP" ]
then
echo $table too small to parallelize
continue
fi
cd c:/_CVS/tpc/tpcds
./dbgen2.exe /f /dir c:/temp /ab $ab /sc $sc /parallel 10 /child 10 > /dev/null 2>&1 &
./dbgen2.exe /f /dir c:/temp /ab $ab /sc $sc /parallel 20 /child 20 > /dev/null 2>&1 &
wait
cd c:/temp
compare=$table
while [ -n "$compare" ]
do
if [ ! -f ${compare}_10_10.csv ]
then
echo review $compare scaling -- $sc is too small to parallelize
break
fi
tail -1 ${compare}_10_10.csv > parallel.csv
tail -1 ${compare}_20_20.csv > serial.csv
diff parallel.csv serial.csv > ${compare}.diff
if [ -s ${compare}.diff ]
then
echo
echo $compare ERROR
echo =========
tail -1 serial.csv parallel.csv
echo
else
echo $compare ok
fi
rm ${compare}* parallel.csv serial.csv
if [ "$compare" = "$child" ]
then compare=""
else compare=$child
fi
done
done << _EOF_
call_center cc NP
catalog_page cp NP
catalog_sales cs 1 catalog_returns
customer cu 100
customer_address ca 100
customer_demographics cd NP
date_dim da NP
household_demographics hd NP
income_band ib NP
inventory inv 1
item it 10000
promotion pr NP
promotional_bundle pb NP
promotional_bundle_coverage pc NP
reason re NP
ship_mode sm NP
store st NP
store_sales ss 1 store_returns
time_dim ti NP
warehouse wa NP
web_page wp NP
web_sales ws 10 web_returns
web_site web NP
_EOF_

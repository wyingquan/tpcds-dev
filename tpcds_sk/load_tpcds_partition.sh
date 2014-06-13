#!/bin/bash

if [ "$#" !=  "1" ]; then
        echo "Please specify a database name."; exit
fi
echo $1
echo $2
echo "Loading schema..."
#psql $1 -f "ddl_tpcds_partition.sql"

#loading data
for f in dsdata/*.dat
do
    echo "loading... $f"
    filename=$(basename $f)
    filename=${filename%.*}
    echo $filename
    psql $1 -c "COPY $filename FROM '$(pwd)/$f' WITH DELIMITER AS '|' NULL AS '';"
    #psql -c "DROP TABLE $filename" gpadmin
done
psql $1 -c "analyze;"


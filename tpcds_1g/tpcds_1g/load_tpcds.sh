#!/bin/bash

if [ "$#" !=  "1" ]; then
        echo "Please specify a database name."; exit
fi
echo $1
echo $2
echo "Loading schema..."
psql $1 -f "ddl_tpcds.sql"

#loading data
for f in tpcds_1g/*.dat
do
    echo "loading... $f"
    filename=$(basename $f)
    filename=${filename%.*}
    echo $filename
    psql $1 -c "COPY $filename FROM '$(pwd)/$f' WITH DELIMITER AS '|' NULL AS '';"
done
psql $1 -c "analyze;"


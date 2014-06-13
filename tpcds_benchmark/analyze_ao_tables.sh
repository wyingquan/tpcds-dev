#!/bin/bash

# Three tables, the *_returns tables, can't be generated separately
# (e.g., catalog_sales builds catalog returns)
# And we'll skip the dbgen_version table as well
for table in `psql -tAc "\\d" | grep -v external | cut -f2 -d\| | grep -v '_prt_'`
do
    echo "Table: $table"
    echo "VACUUM ANALYZE $table;" | psql -tA
    echo ""
done


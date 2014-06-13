#!/bin/bash

if [ "$#" -ne 1 ]
then
    echo "Usage: $0 table_name"
    exit 1
fi

table_name=$1
data_size_GB=$(( 50 * 1024 ))
dsdgen_exe=/tmp/dsgen_tools_patched/dsdgen

$dsdgen_exe \
    -scale $data_size_GB \
    -parallel $GP_SEGMENT_COUNT \
    -child $(( GP_SEGMENT_ID + 1 )) \
    -terminate N \
    -distributions `dirname $dsdgen_exe`/tpcds.idx \
    -table $table_name \
    -FILTER Y \
    -quiet Y


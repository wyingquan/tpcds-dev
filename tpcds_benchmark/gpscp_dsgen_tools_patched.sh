
for i in `ls dsgen_tools_patched`
    do gpscp -f seg_host_list dsgen_tools_patched/$i =:/tmp/dsgen_tools_patched/
done

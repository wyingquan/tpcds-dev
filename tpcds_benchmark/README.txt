This is a quick guide on how to use the dsgen to generate 50TB of data and run queries 
against it in HAWQ. 

1. Edit wrap_dsdgen.sh Change the line data_size_GB=$(( 50 * 1024 )) to reflect the data 
	size you want. It is set to 50TB in the above example 
2. Run gpscp_dsgen_tools_patched.sh to copy the generator to /tmp/dsgen_tools_patched/ on 
	all segment nodes
3. Run gpscp_wrap_dsdgen.sh to copy the wrapper script to /tmp on all segment nodes
4. Create a DB in HAWQ and add export PGDATABASE=<your db name> into your .bashrc
5. psql -f tpcds_hawq.sql This will create all the tables and generate data for them
6. Now re-partition sore_sales to store_sales_25 using psql -f store_sales_partition.sql
7. Vacuum analyze everything using analyze_ao_tables.sh
8. Now you are ready to run the queries any which way you like. Below is an example of how to do this using runQueries.py:

time python runQueries.py > perf_times_`date +"%m-%d-%Y-%H-%M"`.log  
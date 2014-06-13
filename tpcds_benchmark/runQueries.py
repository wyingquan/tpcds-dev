#!/usr/bin/env python

import subprocess
import logging


num_iters=1
#query_path='Impala_TPC-DS_Queries/'
query_path='queries/'
prline = []

logger = logging.getLogger('runQueries')
hdlr = logging.FileHandler('runQueries.log')
formatter = logging.Formatter('%(asctime)s %(levelname)s %(message)s')
hdlr.setFormatter(formatter)
logger.addHandler(hdlr) 
logger.setLevel(logging.INFO)

#Run a query 3 times
def runQ(file):
    sql = 'time psql -tAf' + file
    run_count=1
    prline = []
    while run_count <= num_iters:
        p = subprocess.Popen(sql, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        logger.info('run count ' + str(run_count))
        for line in p.stdout.readlines():
            logger.info(line.strip())
            if "ERROR" in line:
                prline.append(line)
            else:
                if "real" in line:
                    time = line.split()
                    time = time[1]
                    prline.append(time)    
            retval = p.wait()
        run_count=run_count+1
        #print 'returned \t ' , retval
        if retval != 0:
            #print 'errors occured on query run ' , run_count
            prline.append('error on run' + str(run_count) + ' returned ' + str(retval))
    for item in prline:
        print item

def main():


    cmd = 'ls '+ query_path + '*.sql'
    p = subprocess.Popen(cmd,  shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    for file in p.stdout.readlines():
        logger.info('Running ' + file.strip())
        prline.append(file.rstrip())
        runQ(file)
        retval = p.wait()
    if retval != 0:
        print 'Error: Make sure query_path is set correctly! Error Code:' , retval
        logger.warn('Error: Make sure query_path is set correctly! Error Code:' , retval)
        for item in prline:
            print item
            #logger.warn(item)

if __name__ == "__main__":
        main()

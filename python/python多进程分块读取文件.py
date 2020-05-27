
import urlparse
import datetime
import os
from multiprocessing import Process,Queue,Array,RLock

"""
̷ֿȡļ
"""

WORKERS = 4
BLOCKSIZE = 100000000
FILE_SIZE = 0

def getFilesize(file):
    """
        ȡҪȡļĴС
    """
    global FILE_SIZE
    fstream = open(file,'r')
    fstream.seek(0,os.SEEK_END)
    FILE_SIZE = fstream.tell()
    fstream.close()

def process_found(pid,array,file,rlock):
    global FILE_SIZE
    global JOB
    global PREFIX
    """
        ̴
        Args:
            pid:̱
            array:̼乲УڱǸļλ
            file:ļ
        ȴarrayлȡǰֵΪʼλstartpossition
        λendpossition (startpossition+BLOCKSIZE) if (startpossition+BLOCKSIZE)<FILE_SIZE else FILE_SIZE
        if startpossition==FILE_SIZE̽
        if startpossition==00ʼȡ
        if startpossition!=0Ϊֹбblockضϵȶһвһпʼʽ
        if ǰλ <=endpossition readline
        Խ߽磬ʹ²arrayеֵ
    """
    fstream = open(file,'r')
    
    while True:
        rlock.acquire()
        print 'pid%s'%pid,','.join([str(v) for v in array])
        startpossition = max(array)            
        endpossition = array[pid] = (startpossition+BLOCKSIZE) if (startpossition+BLOCKSIZE)<FILE_SIZE else FILE_SIZE
        rlock.release()
        
        if startpossition == FILE_SIZE:#end of the file
            print 'pid%s end'%(pid)
            break
        elif startpossition !=0:
            fstream.seek(startpossition)
            fstream.readline()
        pos = ss = fstream.tell()
        ostream = open('/data/download/tmp_pid'+str(pid)+'_jobs'+str(endpossition),'w')
        while pos<endpossition:
            #line
            line = fstream.readline()                        
            ostream.write(line)
            pos = fstream.tell()

        print 'pid:%s,startposition:%s,endposition:%s,pos:%s'%(pid,ss,pos,pos)
        ostream.flush()
        ostream.close()
        ee = fstream.tell()        

    fstream.close()

def main():
    global FILE_SIZE
    print datetime.datetime.now().strftime("%Y/%d/%m %H:%M:%S") 
    
    file = "/data/pds/download/scmcc_log/tmp_format_2011004.log"
    getFilesize(file)
    print FILE_SIZE
    
    rlock = RLock()
    array = Array('l',WORKERS,lock=rlock)
    threads=[]
    for i in range(WORKERS):
        p=Process(target=process_found, args=[i,array,file,rlock])
        threads.append(p)

    for i in range(WORKERS):
        threads[i].start()
    
    for i in range(WORKERS):
        threads[i].join()

    print datetime.datetime.now().strftime("%Y/%d/%m %H:%M:%S") 

if __name__ == '__main__':
    main()
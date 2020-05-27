import sys
import os
import platform
import subprocess
import queue
import threading
import ipaddress
import re
import sqlite3
import argparse

def worker_func(pingArgs, pending, done):
    try:
        while True:
            # Get the next address to ping.
            address = pending.get_nowait()
            ping = subprocess.Popen(pingArgs + [address],
                stdout = subprocess.PIPE,
                stderr = subprocess.PIPE
            )
            out, error = ping.communicate()
            sout = out.decode("GBK")
            # serror = error.decode("GBK")
            # print(pingArgs,address,sout)
            pattern = r".*最短.=.(\d+)ms?.*最长.=.(\d+)ms?.*平均.=.(\d+)ms"
            m =re.search(pattern,sout)
            if m :
                mint = m.group(1)
                maxt = m.group(2)
                avgt = m.group(3)
                temp = [address,mint,maxt,avgt]
                done.put(temp)

            # Output the result to the 'done' queue.
    except queue.Empty:
        # No more addresses.
        pass
    finally:
        # Tell the main thread that a worker is about to terminate.
        done.put(None)

def getAvailiableIP(ips):
    # The number of workers.
    NUM_WORKERS = 4

    plat = platform.system()
    # The arguments for the 'ping', excluding the address.
    if plat == "Windows":
        pingArgs = ["ping", "-n", "1", "-l", "1", "-w", "100"]
    elif plat == "Linux":
        pingArgs = ["ping", "-c", "1", "-l", "1", "-s", "1", "-W", "1"]
    else:
        raise ValueError("Unknown platform")

    # The queue of addresses to ping.
    pending = queue.Queue()

    # The queue of results.
    done = queue.Queue()

    # scriptDir = sys.path[0]
    # hosts = os.path.join(scriptDir, 'dnsHost.txt')
    for ip in ips:
        pending.put(ip)
            
    # Create all the workers.
    workers = []
    for _ in range(NUM_WORKERS):
        workers.append(threading.Thread(target=worker_func, args=(pingArgs, pending, done)))

    # Put all the addresses into the 'pending' queue.


    # for ip in list(ipaddress.ip_network("192.168.16.0/24").hosts()):
    #     pending.put(str(ip))

    # Start all the workers.
    for w in workers:
        w.daemon = True
        w.start()

    # Print out the results as they arrive.
    conn = sqlite3.connect('temp.db')
    c = conn.cursor()
    purchases = []
    numTerminated = 0
    while numTerminated < NUM_WORKERS:
        result = done.get()
        if result is None:
            # A worker is about to terminate.
            numTerminated += 1
        else:
            # print(result) # print out the ok ip
            purchases.append(result)

    # Wait for all the workers to terminate.
    for w in workers:
        w.join()

    
    SQL = "create table dns_table (ip,mint interger,maxt interger, avgt interger)"
    c.execute(SQL) 
    c.executemany('INSERT INTO dns_table VALUES (?,?,?,?)', purchases)
    SQL = "select ip,mint,maxt,avgt from dns_table order by avgt"
    c.execute(SQL)
    rows = c.fetchall()
    for row in rows:
        print(row)

def main():
    parser = argparse.ArgumentParser(description='ip[网址]获取和统计')
    parser.add_argument('-f','--file', help='从指定文件里提取ip')
    parser.add_argument('--ip',help='指定网段,例:192.168.16.0/24')
    args = parser.parse_args()
    ips =list()
    if args.file:
        hosts = args.file
        with open(hosts,'r') as f:
            data = f.read()
            ips = data.split()
    if args.ip:
        # print(args.ip)
        temp=list(ipaddress.ip_network(args.ip).hosts())
        ips = [str(ip) for ip in temp ]
        # print(type(ips),ips)
        # for ip in ips:
        #     print(str(ip))
            # ip = re.match('(\d{1,3}\.){2}\d{1,3}',ip.decode)
    if os.path.exists('temp.db'):
        os.remove('temp.db')
    if ips:
        getAvailiableIP(ips)
        os.remove('temp.db')
    # netsh interface ipv4 set dnsservers "WLAN" static 202.96.64.68 primary        
    # netsh interface ipv4 add dnsservers "WLAN" 9.9.9.9

if __name__=="__main__":
    main()
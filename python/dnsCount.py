import sys
import os
import platform
import subprocess
import queue
import threading
import ipaddress
import re
import sqlite3

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

def getAvailableDNS():
    # The number of workers.
    NUM_WORKERS = 4

    plat = platform.system()
    scriptDir = sys.path[0]
    hosts = os.path.join(scriptDir, 'dnsHost.txt')
    print(hosts)
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

    # Create all the workers.
    workers = []
    for _ in range(NUM_WORKERS):
        workers.append(threading.Thread(target=worker_func, args=(pingArgs, pending, done)))

    # Put all the addresses into the 'pending' queue.
    with open(hosts,'r') as f:
        data = f.read()
        ips = data.split()
        for ip in ips:
            pending.put(ip)

    # for ip in list(ipaddress.ip_network("10.69.69.0/24").hosts()):
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

    
    SQL = "create table dns_table (ip,mint,maxt,avgt)"
    c.execute(SQL) 
    c.executemany('INSERT INTO dns_table VALUES (?,?,?,?)', purchases)
    SQL = "select ip,mint,maxt,avgt from dns_table order by avgt limit 1"
    c.execute(SQL)
    print(c.fetchone())

def main():
    os.remove('temp.db')
    getAvailableDNS()
    os.remove('temp.db')

if __name__=="__main__":
    main()
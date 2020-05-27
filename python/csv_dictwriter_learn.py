import csv
import sys

f = open(sys.argv[1], 'a')
try:
    fieldnames = ('Title 1', 'Title 2', 'Title 3')
    writer = csv.DictWriter(f, fieldnames=fieldnames)
    #headers = dict( (n,n) for n in fieldnames )
    #writer.writerow(headers)
    writer.writeheader()
    for i in range(10):
        writer.writerow({ 'Title 1':i+1,
                          'Title 2':chr(ord('a') + i),
                          'Title 3':'08/%02d/07' % (i+1),
                          })
finally:
    f.close()

print( open(sys.argv[1], 'rt').read() )
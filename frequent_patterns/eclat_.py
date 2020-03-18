from datetime import datetime
from fim import eclat

from data import return_data_rows


def do_eclat(min_support):
    f = open("/home/keyrooh/Desktop/ns-allinone-2.35_gcc482/ns-allinone-2.35/ns-2.35/tcl/ex/blah.txt","r")
    lines = f.readlines()
    result=[]
    for x in lines:
        result.append(x)
    f.close()
    transactions = []
    for row in result:
        one_trip_locations = []
        x = str(row.split(",")[2]) + "," + str(row.split(",")[3])
        x = x.rstrip("\n")
        one_trip_locations.append(x)
	#print(one_trip_locations)
        transactions.append(one_trip_locations)
    #print(transactions)
    start_time = datetime.now()
    rules = eclat(transactions, supp=min_support)
    #rules.sort(key=lambda x: x[1])
    end_time = datetime.now()
    print(rules)
    diff = (end_time - start_time)
    print("eclat longs : ", diff.total_seconds(), "seconds")

min_support = 0.05
do_eclat(min_support)

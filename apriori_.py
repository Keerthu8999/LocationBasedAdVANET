from datetime import datetime
from apyori import apriori
from data import return_data_rows

def do_apriori(min_support):
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
    item_sets = list(apriori(transactions, min_support=min_support,min_confidence=0.02))
    end_time = datetime.now()
    diff = (end_time - start_time)
    print(item_sets)
    print("apriori longs : ", diff.total_seconds(), "seconds")


min_support = 0.05
do_apriori(min_support)

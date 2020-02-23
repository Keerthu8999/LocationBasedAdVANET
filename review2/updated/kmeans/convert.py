fin = open("1.txt", "rt")
fout = open("1a.txt", "wt")

for line in fin:
	fout.write(' '.join(line.split()))
	fout.write('\n')
	
fin.close()
fout.close()


fin = open("2.txt", "rt")
fout = open("2a.txt", "wt")

for line in fin:
	fout.write(' '.join(line.split()))
	fout.write('\n')
	
fin.close()
fout.close()


fin = open("3.txt", "rt")
fout = open("3a.txt", "wt")

for line in fin:
	fout.write(' '.join(line.split()))
	fout.write('\n')
	
fin.close()
fout.close()


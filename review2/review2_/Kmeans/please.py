blocks_to_read = 4
blk_begin = 'A'
blk_end = '$$'

with open('output.txt', 'r') as f:
    fn = 1
    data = []
    write_block = False
    for line in f:
        if fn > blocks_to_read:
            break 
        line = line.strip()
        if line == blk_begin:
	    
            write_block = True
        if write_block:
            data.append(line)
        if line == blk_end:
            write_block = False
            with open(str(fn) + '.txt', 'w') as fout:
                fout.write('\n'.join(data[1:]))
                data = []
            fn += 1



def filter_opencv(im):
    for i in range(100000):
        im += 1
        
    return im

def filter_homemade(im):
    
    for i in range(100000):
        im += 2
        
    return im
 


import yappi
filename = 'callgrind.filename.prof'
yappi.set_clock_type('cpu')
yappi.start(builtins=True)
filter_homemade(0)
filter_opencv(0)
stats = yappi.get_func_stats()
stats.save(filename, type='callgrind')

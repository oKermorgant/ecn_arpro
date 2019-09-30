import pylab as pl
import yaml
from sys import argv

with open(argv[1]) as f:
   data = yaml.safe_load(f)
    
coord = pl.array(data['data'],dtype=float)

n = len(data['names'])

for i in range(n):
    pl.plot(coord[:,2*i], coord[:,2*i+1],data['colors'][i], label=data['names'][i])
    pl.plot([coord[0,2*i]],[coord[0,2*i+1]],data['colors'][i] + 'D')
    pl.plot([coord[-1,2*i]],[coord[-1,2*i+1]], data['colors'][i] + 's')
    
pl.plot([], [], "kD", label="Initial poses")
pl.plot([], [], "ks", label="Final poses")

if 'walls' in data:
    for key in ('x','y'):
        data['walls'][key].append(data['walls'][key][0])
    pl.plot(data['walls']['x'], data['walls']['y'], "k", linewidth=2)

pl.legend()
pl.tight_layout()
pl.show()

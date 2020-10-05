#!/usr/bin/env python

import yaml
import cartopy.crs as ccrs 
from sys import argv
import matplotlib.pyplot as plt
from numpy import array
import os

filename = 'tsp.yaml'
if len(argv) > 1 and not argv[1].isdigit():
    filename = argv[1]
    
with open(filename) as f:
    data = yaml.safe_load(f)
cities = data['cities']
positions = [data['positions'][city] for city in cities]

# read passed order
order = []
for i in argv[1:]:
    try:
        order.append(int(i))
    except:
        pass
for i in range(len(cities)):
    if i not in order:
        order.append(i)
order.append(order[0])

# display map
proj = ccrs.PlateCarree()

plt.close('all')
plt.figure(figsize=(15,8))
ax = plt.axes(projection=proj)

im = plt.imread(os.path.abspath(os.path.dirname(__file__)) + '/earth_2400.jpg')
img_extent = (-180, 180, -90, 90)
ax.imshow(im, origin='upper', extent=img_extent, transform=proj)
plt.tight_layout()

travel = array([positions[o] for o in order])
plt.plot(travel[:,1],travel[:,0],'r-D',transform=ccrs.Geodetic())

xm,xM = min(travel[:,1]), max(travel[:,1])
ym, yM = min(travel[:,0]), max(travel[:,0])
#plt.axis((xm - 0.05*(xM-xm), xM + 0.05*(xM-xm), ym - 0.05*(yM-ym), yM + 0.05*(yM-ym)))

plt.show()
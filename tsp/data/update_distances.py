#!/usr/bin/env python

import yaml
from geopy.geocoders import Nominatim
from geopy.distance import geodesic
from sys import argv

name = 'tsp.yaml'
if len(argv) > 1:
    name = argv[1]

data = yaml.load(open(name))
data['positions'] = {}

geolocator = Nominatim()
geo = [geolocator.geocode(city, timeout=10) for city in data['cities']]

for i,src in enumerate(geo):
    data[i] = [int(geodesic(src.point,dst.point).km) for dst in geo]
    for j in range(i):
        print('Distance from {} to {} is {} km'.format(data['cities'][i], data['cities'][j], data[i][j]))
        
    data['positions'][data['cities'][i]] = [src.latitude, src.longitude]


with open(name, 'w') as f:
    yaml.dump(data, f)

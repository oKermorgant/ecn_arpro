import yaml
from geopy.geocoders import Nominatim
from geopy.distance import vincenty

data = yaml.load(file('tsp.yaml'))
geolocator = Nominatim()
geo = [geolocator.geocode(city) for city in data['cities']]

for i,src in enumerate(geo):
    data[i] = []
    for j,dst in enumerate(geo):
        d = int(vincenty(src.point,dst.point).km)
        if i < j:
            print('Distance from {} to {}: {}'.format(data['cities'][i], data['cities'][j], d))
        data[i].append(d)

with open('tsp.yaml', 'w') as f:
    yaml.dump(data, f)

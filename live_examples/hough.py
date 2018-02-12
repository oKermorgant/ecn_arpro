from pylab import *

noise = 2
outliers = 50
size = 1000

a = 2
b = 4
x = linspace(-10, 10, size)
y = a * x + b + noise*randn(x.shape[0])

xy_out = -10 + 20*rand(2, outliers)

x = concatenate((x, xy_out[0])).reshape(size + outliers, 1)
y = concatenate((y, xy_out[1])).reshape(size + outliers, 1)
xy = concatenate((x, y), 1)

close('all')

plot(x,y,'.')


steps = 1000

theta_min = -pi
theta_max = pi
theta_vals = linspace(theta_min, theta_max, steps)
theta_step = theta_vals[1] - theta_min

rho_min = 0
rho_max = 20
rho_vals = linspace(rho_min, rho_max, steps)
rho_step = rho_vals[1] - rho_min

TR = zeros((steps, steps))

for xi, yi in xy:
    for idx, theta in enumerate(theta_vals):
        rho = cos(theta)*xi + sin(theta)*yi
        rho_idx = int(round((rho - rho_min)/rho_step))
        if rho_idx < TR.shape[1] and rho_idx >= 0:
            TR[idx,rho_idx] += 1
      
thres = 19
ok = find(TR > thres)
rho_theta = []
for idx in ok:
    idx_theta = idx / steps
    idx_rho = idx % steps
    rho_theta.append((rho_vals[idx_rho],theta_vals[idx_theta]))
    
# To (a, b)
print('Found {} lines'.format(len(rho_theta)))
for rho, theta in rho_theta:
    a = -cos(theta)/sin(theta)
    b = rho/sin(theta)
    print('y = {} x + {}'.format(round(a, 2), round(b, 2)))
    plot(x, a*x+b)



figure()

imshow(TR)
xlabel('$\\theta$')
ylabel('$\\rho$')

show()

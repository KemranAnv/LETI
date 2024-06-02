from cmath import *

def grad_to_rad(x):
	return (x*n(pi))/180

def find_N(x):
	return 1.3 + 0.2*cos(4*x)

def find_y(x):
	return tan(x)*dl

def find_ds(x):
	return sqrt(dl**2 + y[x]**2)

y = []
Y = []
alpha = []
N = []
alpha.append(grad_to_rad(20))
L = 50
step = 10000
dl = L/step
D = 1.4
y.append(0)
Y.append(y[0])
N.append( find_N(Y[0]))
S = find_ds(0)
max = 0

for i in range(1, step+1):
	y.append(find_y(alpha[i-1]))
	Y.append(Y[i-1]+y[i])
	N.append( find_N( Y[i] ) )
	alpha.append( grad_to_rad(90) - arcsin((N[i-1] * sin(grad_to_rad(90) -
alpha[i-1])/(N[i]) )))
	if alpha[i-1] < 0:
		alpha[i] = - alpha[i]
	if alpha[i] != alpha[i] or abs(Y[i]) >= D:
		alpha[i] = -alpha[i-1]
	S += find_ds(i)
	if max < Y[i]:
		max = Y[i]

	print(S)
	print(max)

list_plot([Y[i] for i in range(step+1)], plotjoined=True, axes_labels=['$z$',
'$y$'])

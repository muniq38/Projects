```python
test = "Hello World"
```


```python
print ("test: " + test)
```

    test: Hello World
    


```python
import math

def basic_sigmoid(x): 
    s = 1/(1+math.exp(-x))
    return s
```


```python
basic_sigmoid(3)
```




    0.9525741268224334




```python
import numpy as np
# example of np.exp
x = np.array([1, 2, 3])
print(np.exp(x)) # result is (exp(1), exp(2), exp(3))
```

    [ 2.71828183  7.3890561  20.08553692]
    


```python
# example of vector operation
x = np.array([1, 2, 3])
print (x + 3)
```

    [4 5 6]
    


```python
import numpy as np 

def sigmoid(x):
    s = 1/(1+np.exp(-x))
    return s
```


```python
x = np.array([1, 2, 3])
sigmoid(x)
```




    array([0.73105858, 0.88079708, 0.95257413])




```python
def sigmoid_derivative(x):
    s = 1/(1+np.exp(-x))
    ds = sigmoid(x)*(1-sigmoid(x))
    return ds
```


```python
x = np.array([1, 2, 3])
print ("sigmoid_derivative(x) = " + str(sigmoid_derivative(x)))
```

    sigmoid_derivative(x) = [0.19661193 0.10499359 0.04517666]
    


```python
def image2vector(image): # Converts into column vector
    v = image.reshape((image.shape[0]*image.shape[1]*image.shape[2],1))
    return v
```


```python
# This is a 3 by 3 by 2 array where 3 represents the RGB values
image = np.array([[[ 0.67826139,  0.29380381],
        [ 0.90714982,  0.52835647],
        [ 0.4215251 ,  0.45017551]],

       [[ 0.92814219,  0.96677647],
        [ 0.85304703,  0.52351845],
        [ 0.19981397,  0.27417313]],

       [[ 0.60659855,  0.00533165],
        [ 0.10820313,  0.49978937],
        [ 0.34144279,  0.94630077]]])

print ("image2vector(image) = " + str(image2vector(image)))
```

    image2vector(image) = [[0.67826139]
     [0.29380381]
     [0.90714982]
     [0.52835647]
     [0.4215251 ]
     [0.45017551]
     [0.92814219]
     [0.96677647]
     [0.85304703]
     [0.52351845]
     [0.19981397]
     [0.27417313]
     [0.60659855]
     [0.00533165]
     [0.10820313]
     [0.49978937]
     [0.34144279]
     [0.94630077]]
    


```python
def normalizeRows(x):
    x_norm = np.linalg.norm(x,axis=1,keepdims=True)
    x = x/x_norm
    return x
```


```python
x = np.array([
    [0, 3, 4],
    [1, 6, 4]])
print("normalizeRows(x) = " + str(normalizeRows(x)))
```

    normalizeRows(x) = [[0.         0.6        0.8       ]
     [0.13736056 0.82416338 0.54944226]]
    


```python
def softmax(x):
    x_exp = np.exp(x)
    x_sum = np.sum(x_exp,axis=1,keepdims=True)
    s = x_exp/x_sum
    return s
```


```python
x = np.array([
    [9, 2, 5, 0, 0],
    [7, 5, 0, 0 ,0]])
print("softmax(x) = " + str(softmax(x)))
```

    softmax(x) = [[9.80897665e-01 8.94462891e-04 1.79657674e-02 1.21052389e-04
      1.21052389e-04]
     [8.78679856e-01 1.18916387e-01 8.01252314e-04 8.01252314e-04
      8.01252314e-04]]
    


```python
def L1(yhat, y):
    loss = np.sum(abs(y-yhat))
    return loss
```


```python
yhat = np.array([.9, 0.2, 0.1, .4, .9])
y = np.array([1, 0, 0, 1, 1])
print("L1 = " + str(L1(yhat,y)))
```

    L1 = 1.1
    


```python
def L2(yhat, y):
    diff = y-yhat
    loss = np.dot(diff,diff)
    return loss
```


```python
yhat = np.array([.9, 0.2, 0.1, .4, .9])
y = np.array([1, 0, 0, 1, 1])
print("L2 = " + str(L2(yhat,y)))
```

    L2 = 0.43
    


```python
import time
x1 = [9, 2, 5, 0, 0, 7, 5, 0, 0, 0, 9, 2, 5, 0, 0]
x2 = [9, 2, 2, 9, 0, 9, 2, 5, 0, 0, 9, 2, 5, 0, 0]
W = np.random.rand(3,len(x1))

### VECTORIZED DOT PRODUCT OF VECTORS ###
tic = time.process_time()
dot = np.dot(x1,x2)
toc = time.process_time()
print ("dot = " + str(dot) + "\n ----- Computation time = " + str(1000*(toc - tic)) + "ms")

### VECTORIZED OUTER PRODUCT ###
tic = time.process_time()
outer = np.outer(x1,x2)
toc = time.process_time()
print ("outer = " + str(outer) + "\n ----- Computation time = " + str(1000*(toc - tic)) + "ms")

### VECTORIZED ELEMENTWISE MULTIPLICATION ###
tic = time.process_time()
mul = np.multiply(x1,x2)
toc = time.process_time()
print ("elementwise multiplication = " + str(mul) + "\n ----- Computation time = " + str(1000*(toc - tic)) + "ms")

### VECTORIZED GENERAL DOT PRODUCT ###
tic = time.process_time()
dot = np.dot(W,x1)
toc = time.process_time()
print ("gdot = " + str(dot) + "\n ----- Computation time = " + str(1000*(toc - tic)) + "ms")
```

    dot = 278
     ----- Computation time = 0.0ms
    outer = [[81 18 18 81  0 81 18 45  0  0 81 18 45  0  0]
     [18  4  4 18  0 18  4 10  0  0 18  4 10  0  0]
     [45 10 10 45  0 45 10 25  0  0 45 10 25  0  0]
     [ 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0]
     [ 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0]
     [63 14 14 63  0 63 14 35  0  0 63 14 35  0  0]
     [45 10 10 45  0 45 10 25  0  0 45 10 25  0  0]
     [ 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0]
     [ 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0]
     [ 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0]
     [81 18 18 81  0 81 18 45  0  0 81 18 45  0  0]
     [18  4  4 18  0 18  4 10  0  0 18  4 10  0  0]
     [45 10 10 45  0 45 10 25  0  0 45 10 25  0  0]
     [ 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0]
     [ 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0]]
     ----- Computation time = 0.0ms
    elementwise multiplication = [81  4 10  0  0 63 10  0  0  0 81  4 25  0  0]
     ----- Computation time = 0.0ms
    gdot = [21.07723952 25.91346313 29.89676169]
     ----- Computation time = 0.0ms
    


```python

```

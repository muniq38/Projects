```python
import numpy as np
```


```python
def sigmoid(Z):
    A = 1/(1+np.exp(-Z))
    cache = Z
    return A, cache
```


```python
def relu(Z):
    A = np.maximum(0,Z)
    cache = Z 
    assert(A.shape == Z.shape)
    return A, cache
```


```python
def initialize_parameters_deep(layer_dims):
    np.random.seed(3)
    parameters = {}
    L = len(layer_dims)     # number of layers in the network

    for l in range(1, L):
        parameters['W' + str(l)] = np.random.randn(layer_dims[l],layer_dims[l-1])*0.01
        parameters['b' + str(l)] = np.zeros((layer_dims[l],1))
        assert(parameters['W' + str(l)].shape == (layer_dims[l], layer_dims[l-1]))
        assert(parameters['b' + str(l)].shape == (layer_dims[l], 1))
        
    return parameters
```


```python
def linear_forward(A_prev, W, b):
    Z = np.dot(W,A_prev)+b
    cache = (A_prev, W, b)
    assert(Z.shape == (W.shape[0], A.shape[1]))
    return Z, cache
```


```python
def linear_activation_forward(A_prev, W, b, activation):
    
    if activation == "sigmoid":    
        Z, linear_cache = linear_forward(A_prev,W,b) 
        A, activation_cache = sigmoid(Z)
        
    elif activation == "relu":
        Z, linear_cache = linear_forward(A_prev,W,b) 
        A, activation_cache = relu(Z)
    
    cache = (linear_cache, activation_cache)
    assert (A.shape == (W.shape[0], A_prev.shape[1]))
    return A, cache
```


```python
def L_model_forward(X, parameters):
    caches = []
    A = X
    L = len(parameters) // 2  # number of layers 
    
    for l in range(1, L): 
        A_prev = A 
        A, cache = linear_activation_forward(A, parameters['W'+str(l)], parameters['b'+str(l)], "relu")
        caches.append(cache) # Use ReLU, add to caches
    
    AL, cache = linear_activation_forward(A, parameters['W'+str(L)], parameters['b'+str(L)], "sigmoid")
    caches.append(cache) # Use sigmoid, add to caches
    
    assert(AL.shape == (1,X.shape[1]))
    return AL, caches
```


```python
def compute_cost(AL, Y):
    m = Y.shape[1]
    cost = -np.sum(Y*np.log(AL)+(1-Y)*np.log(1-AL))/m  # Compute Cost
    cost = np.squeeze(cost) 
    
    assert(cost.shape == ())
    return cost
```


```python
def sigmoid_backward(dA, cache):
    Z = cache
    s, scache = sigmoid(Z)
    dZ = dA*s*(1-s)
    
    assert (dZ.shape == Z.shape) 
    return dZ
```


```python
def relu_backward(dA, cache):
    Z = cache
    dZ = np.array(dA, copy=True) 
    dZ[Z <= 0] = 0  # When z <= 0, dz = 0
    
    assert (dZ.shape == Z.shape)
    return dZ
```


```python
def linear_backward(dZ, cache): # computes dA_prev, dW, db from dZ 
    A_prev, W, b = cache
    m = A_prev.shape[1]

    dW = np.dot(dZ,A_prev.T)/m
    db = np.sum(dZ,axis=1,keepdims=True)/m
    dA_prev = np.dot(W.T,dZ)
    
    assert (dA_prev.shape == A_prev.shape)
    assert (dW.shape == W.shape)
    assert (db.shape == b.shape)
    return dA_prev, dW, db
```


```python
def linear_activation_backward(dA, cache, activation): # computes dA_prev, dW, db, dZ from dA
    linear_cache, activation_cache = cache  
    # linear : (A_prev, W, b)  //  activation : Z
    if activation == "relu":
        dZ = relu_backward(dA,activation_cache)
        dA_prev, dW, db = linear_backward(dZ,linear_cache)
        
    elif activation == "sigmoid":
        dZ = sigmoid_backward(dA,activation_cache)
        dA_prev, dW, db = linear_backward(dZ,linear_cache)
    
    return dA_prev, dW, db
```


```python
def L_model_backward(AL, Y, caches):
    grads = {}
    L = len(caches) # the number of layers
    m = AL.shape[1]
    Y = Y.reshape(AL.shape) # after this line, Y is the same shape as AL
    
    dAL = -(np.divide(Y, AL)-np.divide(1-Y,1-AL)) 
    current_cache = caches[L-1] # Backprop for Lth layer
    grads["dA" + str(L-1)], grads["dW" + str(L)], grads["db" + str(L)] = ...
    linear_activation_backward(dAL,current_cache,"sigmoid") 
    
    for l in reversed(range(L-1)):
        current_cache = caches[l] # Backprop for 1~(L-1)th layer
        dA_prev_temp, dW_temp, db_temp = ...
        linear_activation_backward(grads["dA"+str(l+1)],current_cache,"relu")
        
        grads["dA" + str(l)] = dA_prev_temp
        grads["dW" + str(l + 1)] = dW_temp
        grads["db" + str(l + 1)] = db_temp

    return grads
```


```python
def update_parameters(parameters, grads, learning_rate):
    L = len(parameters) // 2  # number of layers 

    for l in range(L): # Update Parameters
        parameters["W" + str(l+1)] -= learning_rate*grads["dW"+str(l+1)]
        parameters["b" + str(l+1)] -= learning_rate*grads["db"+str(l+1)]
        
    return parameters
```

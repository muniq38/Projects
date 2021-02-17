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
    return A, cache
```


```python
def initialize_parameters_random(layers_dims): 
    np.random.seed(3)               
    parameters = {}
    L = len(layers_dims)           
    
    for l in range(1, L):
        parameters['W' + str(l)] = np.random.randn(layers_dims[l],layers_dims[l-1])*0.01
        parameters['b' + str(l)] = np.zeros((layers_dims[l],1))

    return parameters
```


```python
def initialize_parameters_he(layers_dims): # Improvement : He Initialization
    np.random.seed(3)
    parameters = {}
    L = len(layers_dims)-1 
     
    for l in range(1, L + 1):
        parameters['W' + str(l)] = np.random.randn(layers_dims[l],layers_dims[l-1])*np.sqrt(2./layers_dims[l-1])
        parameters['b' + str(l)] = np.zeros((layers_dims[l],1))
        
    return parameters
```


```python
def linear_forward(A_prev, W, b): # computes Z (#1)
    Z = np.dot(W,A_prev)+b
    cache = (A_prev, W, b)
    return Z, cache
```


```python
def linear_activation_forward(A_prev, W, b, activation): # computes Z,A (#2)
    
    if activation == "sigmoid":    
        Z, linear_cache = linear_forward(A_prev,W,b) 
        A, activation_cache = sigmoid(Z)
        
    elif activation == "relu":
        Z, linear_cache = linear_forward(A_prev,W,b) 
        A, activation_cache = relu(Z)
    
    cache = (linear_cache, activation_cache)
    return A, cache
```


```python
def L_model_forward(X, parameters): # full forward prop (#3)
    caches = []
    A = X
    L = len(parameters) // 2  # number of layers 
    
    for l in range(1, L): 
        A_prev = A 
        A, cache = linear_activation_forward(A, parameters['W'+str(l)], parameters['b'+str(l)], "relu")
        caches.append(cache) # Use ReLU, add to caches
    
    AL, cache = linear_activation_forward(A, parameters['W'+str(L)], parameters['b'+str(L)], "sigmoid")
    caches.append(cache) # Use sigmoid, add to caches
    
    return AL, caches
```


```python
def compute_cost(AL, Y): # computes cost
    m = Y.shape[1]
    cost = -np.sum(Y*np.log(AL)+(1-Y)*np.log(1-AL))/m  # Compute Cost
    cost = np.squeeze(cost) 
    
    return cost
```


```python
def compute_cost_with_regularization(A3, Y, parameters, lambd): # Improvement : Regularization
    m = Y.shape[1]
    cross_entropy_cost = compute_cost(A3, Y)
    
    L2_regularization_cost = 0
    for l in range(L):
        L2_regularization_cost += np.sum(np.square( parameters["W"+str(l+1)] ))
    L2_regularization_cost *= lambd/(2*m)
    
    cost = cross_entropy_cost + L2_regularization_cost
    return cost
```


```python
def sigmoid_backward(dA, cache):
    Z = cache
    s, scache = sigmoid(Z)
    dZ = dA*s*(1-s)
    
    return dZ
```


```python
def relu_backward(dA, cache):
    Z = cache
    dZ = np.array(dA, copy=True) 
    dZ[Z <= 0] = 0  # When z <= 0, dz = 0
    
    return dZ
```


```python
def linear_backward(dZ, cache): # computes dA_prev, dW, db from dZ (#1)
    A_prev, W, b = cache
    m = A_prev.shape[1]

    dW = np.dot(dZ,A_prev.T)/m
    db = np.sum(dZ,axis=1,keepdims=True)/m
    dA_prev = np.dot(W.T,dZ)
    
    return dA_prev, dW, db
```


```python
def linear_activation_backward(dA, cache, activation): # computes dA_prev, dW, db, dZ from dA (#2)
    linear_cache, activation_cache = cache  
    # linear = (A_prev, W, b)  +  activation = Z
    if activation == "relu":
        dZ = relu_backward(dA,activation_cache)
        dA_prev, dW, db = linear_backward(dZ,linear_cache)
        
    elif activation == "sigmoid":
        dZ = sigmoid_backward(dA,activation_cache)
        dA_prev, dW, db = linear_backward(dZ,linear_cache)
    
    return dA_prev, dW, db
```


```python
def L_model_backward(AL, Y, caches): # full backprop (#3)
    grads = {}
    L = len(caches) 
    m = AL.shape[1]
    Y = Y.reshape(AL.shape)
    
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
def update_parameters(parameters, grads, learning_rate): # update parameters
    L = len(parameters) // 2  

    for l in range(L): # update from grads
        parameters["W" + str(l+1)] -= learning_rate*grads["dW"+str(l+1)]
        parameters["b" + str(l+1)] -= learning_rate*grads["db"+str(l+1)]
        
    return parameters
```


```python
def L_layer_model(X, Y, learning_rate = 0.01, num_iterations = 15000, print_cost=True, initialization = "he", lambd = 0, keep_prob = 1):
    
    grads = {}
    costs = []                        
    layers_dims = [X.shape[0], 20, 3, 1]
    
    if initialization == "random":
        parameters = initialize_parameters_random(layers_dims)
    elif initialization == "he":
        parameters = initialize_parameters_he(layers_dims)
    
    for i in range(0, num_iterations):
        if keep_prob == 1: # Forward
            a3, cache = forward_propagation(X, parameters)
        elif keep_prob < 1:
            a3, cache = forward_propagation_with_dropout(X, parameters, keep_prob)
        
        if lambd == 0: # Cost
            cost = compute_cost(a3, Y)
        else:
            cost = compute_cost_with_regularization(a3, Y, parameters, lambd)
            
        assert(lambd==0 or keep_prob==1)    
        if lambd == 0 and keep_prob == 1: # Backprop
            grads = backward_propagation(X, Y, cache)
        elif lambd != 0:
            grads = backward_propagation_with_regularization(X, Y, cache, lambd)
        elif keep_prob < 1:
            grads = backward_propagation_with_dropout(X, Y, cache, keep_prob)
        
        parameters = update_parameters(parameters, grads, learning_rate) # Update
        if print_cost and i % 10000 == 0: # Print cost
            print("Cost after iteration {}: {}".format(i, cost))
        if print_cost and i % 1000 == 0:
            costs.append(cost)
    
    return parameters 
```

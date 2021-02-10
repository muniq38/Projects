```python
import numpy as np
```


```python
def sigmoid(z):
    s = 1/(1+np.exp(-z))
    return s
```


```python
print ("sigmoid([0, 2]) = " + str(sigmoid(np.array([0,2]))))
```

    sigmoid([0, 2]) = [0.5        0.88079708]
    


```python
def initialize_with_zeros(dim):
    w = np.zeros((dim,1))
    b = 0
    assert(w.shape == (dim, 1))
    assert(isinstance(b, float) or isinstance(b, int))
    return w, b
```


```python
dim = 2
w, b = initialize_with_zeros(dim)
print ("w = " + str(w))
print ("b = " + str(b))
```

    w = [[0.]
     [0.]]
    b = 0
    


```python
def propagate(w, b, X, Y):
    m = X.shape[1]
    
    # FORWARD PROPAGATION (FROM X TO COST)
    A = sigmoid(np.dot(w.T,X)+b)                                    # compute activation
    cost = -np.sum(Y*np.log(A)+(1-Y)*np.log(1-A))/m                # compute cost = J
    
    # BACKWARD PROPAGATION (TO FIND GRAD)
    dw = np.dot(X,(A-Y).T)/m  # dJ/dw
    db = np.sum(A-Y)/m        # dJ/db

    assert(dw.shape == w.shape)
    assert(db.dtype == float)
    cost = np.squeeze(cost)
    assert(cost.shape == ())
    
    grads = {"dw": dw,"db": db}
    return grads, cost
```


```python
w, b, X, Y = np.array([[1.],[2.]]), 2., np.array([[1.,2.,-1.],[3.,4.,-3.2]]), np.array([[1,0,1]])
grads, cost = propagate(w, b, X, Y)
print ("dw = " + str(grads["dw"]))
print ("db = " + str(grads["db"]))
print ("cost = " + str(cost))
```

    dw = [[0.99845601]
     [2.39507239]]
    db = 0.001455578136784208
    cost = 5.801545319394553
    


```python
def optimize(w, b, X, Y, num_iterations, learning_rate, print_cost = False):
    costs = []
    
    for i in range(num_iterations):
        grads, cost = propagate(w, b, X, Y) # calculation
        dw = grads["dw"] # Retrieve derivatives 
        db = grads["db"]
        
        w = w - learning_rate*dw # update parameters
        b = b - learning_rate*db
        
        if i % 100 == 0:
            costs.append(cost) # Record the costs
        
        if print_cost and i % 100 == 0:
            print ("Cost after iteration %i: %f" %(i, cost))
            
    params = {"w": w,"b": b}
    grads = {"dw": dw,"db": db}
    return params, grads, costs
```


```python
params, grads, costs = optimize(w, b, X, Y, num_iterations= 100, learning_rate = 0.009, print_cost = False)

print ("w = " + str(params["w"]))
print ("b = " + str(params["b"]))
print ("dw = " + str(grads["dw"]))
print ("db = " + str(grads["db"]))
```

    w = [[0.19033591]
     [0.12259159]]
    b = 1.9253598300845747
    dw = [[0.67752042]
     [1.41625495]]
    db = 0.21919450454067654
    


```python
def predict(w, b, X):
    m = X.shape[1]
    Y_prediction = np.zeros((1,m))
    w = w.reshape(X.shape[0], 1)
    A = sigmoid(np.dot(w.T,X)+b) # Compute A = probability
    
    for i in range(A.shape[1]):
        Y_prediction[0,i] = 1 if A[0,i]>0.5 else 0
    
    assert(Y_prediction.shape == (1, m))
    return Y_prediction
```


```python
w = np.array([[0.1124579],[0.23106775]])
b = -0.3
X = np.array([[1.,-1.1,-3.2],[1.2,2.,0.1]])
print ("predictions = " + str(predict(w, b, X)))
```

    predictions = [[1. 1. 0.]]
    


```python
def model(X_train, Y_train, X_test, Y_test, num_iterations = 2000, learning_rate = 0.5, print_cost = False):
    w, b = initialize_with_zeros(X_train.shape[0]) #initialize parameters
    parameters, grads, costs = optimize(w, b, X_train, Y_train, num_iterations, learning_rate) # Grad desc.
    w = parameters["w"] # Retrieve parameters 
    b = parameters["b"]
    
    Y_prediction_test = predict(w, b, X_test) # make prediction, final results
    Y_prediction_train = predict(w, b, X_train)

    print("train accuracy: {} %".format(100 - np.mean(np.abs(Y_prediction_train - Y_train)) * 100))
    print("test accuracy: {} %".format(100 - np.mean(np.abs(Y_prediction_test - Y_test)) * 100))

    d = {"costs": costs,
         "Y_prediction_test": Y_prediction_test, 
         "Y_prediction_train" : Y_prediction_train, 
         "w" : w, "b" : b,
         "learning_rate" : learning_rate,
         "num_iterations": num_iterations}
    
    return d 
```

```python
import numpy as np
```


```python
def sigmoid(z):
    s = 1/(1+np.exp(-z))
    return s
```


```python
def initialize_with_zeros(dim):
    w = np.zeros((dim,1))
    b = 0
    assert(w.shape == (dim, 1))
    assert(isinstance(b, float) or isinstance(b, int))
    return w, b
```


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

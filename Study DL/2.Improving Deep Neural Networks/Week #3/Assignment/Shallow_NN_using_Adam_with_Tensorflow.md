```python
import math
import numpy as np
import h5py
import matplotlib.pyplot as plt
import tensorflow.compat.v1 as tf
from tensorflow.python.framework import ops
tf.disable_v2_behavior()

%matplotlib inline
np.random.seed(1)
```


```python
y_hat = tf.constant(36, name='y_hat')            # Define y_hat constant. Set to 36.
y = tf.constant(39, name='y')                    # Define y. Set to 39

loss = tf.Variable((y - y_hat)**2, name='loss')  # Create a variable for the loss

init = tf.global_variables_initializer()         # When init is run later (session.run(init)),                      
with tf.Session() as session:                    # Create a session and print the output
    session.run(init)                            # Initializes the variables
    print(session.run(loss))                     # Prints the loss
```

    9
    


```python
a = tf.constant(2)
b = tf.constant(10)
c = tf.multiply(a,b)
print(c) # tfconstant is not printable without session
```

    Tensor("Mul:0", shape=(), dtype=int32)
    


```python
sess = tf.Session()
print(sess.run(c))
```

    20
    


```python
x = tf.placeholder(tf.int64, name = 'x')
print(sess.run(2 * x, feed_dict = {x: 3})) # using placeholder & feed_dict
sess.close()
```

    6
    


```python
def linear_function():
    X = tf.constant(np.random.randn(3,1), name="X")
    W = tf.constant(np.random.randn(4,3), name="W")
    b = tf.constant(np.random.randn(4,1), name="b")
    Y = tf.add(tf.matmul(W,X),b)  # Y = WX+b
    
    sess = tf.Session()
    result = sess.run(Y)
    sess.close()
    
    return result
```


```python
def sigmoid(z):
    
    x = tf.placeholder(tf.float32, name="x")
    sigmoid = tf.sigmoid(x)

    with tf.Session() as sess:
        result = sess.run(sigmoid,feed_dict={x:z})
        
    return result
```


```python
def cost(logits, labels):
    
    z = tf.placeholder(tf.float32, name="z")
    y = tf.placeholder(tf.float32, name="y")
    cost = tf.nn.sigmoid_cross_entropy_with_logits(logits = z, labels = y)
    
    sess = tf.Session()
    cost = sess.run(cost,feed_dict={z:logits, y:labels})
    sess.close()
        
    return cost
```


```python
def one_hot_matrix(labels, C): # Multi classification setup
    
    C = tf.constant(C, name="C")
    one_hot_matrix = tf.one_hot(labels, C, axis=0)
    
    sess = tf.Session()
    one_hot = sess.run(one_hot_matrix)
    sess.close()
    
    return one_hot
```


```python
def ones(shape):
    ones = tf.ones(shape)
    sess = tf.Session()
    ones = sess.run(ones)
    sess.close()
    return ones
```


```python
def create_placeholders(n_x, n_y): # Create X, Y = placeholders
    X = tf.placeholder(shape = (n_x,None), dtype = tf.float32)
    Y = tf.placeholder(shape = (n_y,None), dtype = tf.float32)
    return X, Y
```


```python
def initialize_parameters(): # W : Xavier, b : Zeros 
    tf.set_random_seed(1)                   
    
    W1 = tf.get_variable("W1", [25,12288], initializer = tf.contrib.layers.xavier_initializer(seed = 1))
    b1 = tf.get_variable("b1", [25,1], initializer = tf.zeros_initializer())
    W2 = tf.get_variable("W2", [12,25], initializer = tf.contrib.layers.xavier_initializer(seed = 1))
    b2 = tf.get_variable("b2", [12,1], initializer = tf.zeros_initializer())
    W3 = tf.get_variable("W3", [6,12], initializer = tf.contrib.layers.xavier_initializer(seed = 1))
    b3 = tf.get_variable("b3", [6,1], initializer = tf.zeros_initializer())

    parameters = {"W1": W1,"b1": b1,"W2": W2,"b2": b2,"W3": W3,"b3": b3}
    return parameters
```


```python
def forward_propagation(X, parameters): # Forwardprop without for (shallow NN)
    
    W1 = parameters['W1']
    b1 = parameters['b1']
    W2 = parameters['W2']
    b2 = parameters['b2']
    W3 = parameters['W3']
    b3 = parameters['b3']
    
    Z1 = tf.add(tf.matmul(W1,X),b1)                                  # Z1 = np.dot(W1, X) + b1
    A1 = tf.nn.relu(Z1)                                              # A1 = relu(Z1)
    Z2 = tf.add(tf.matmul(W2,A1),b2)                                 # Z2 = np.dot(W2, A1) + b2
    A2 = tf.nn.relu(Z2)                                              # A2 = relu(Z2)
    Z3 = tf.add(tf.matmul(W3,A2),b3)                                  # Z3 = np.dot(W3, A2) + b3
    
    return Z3
```


```python
def compute_cost(Z3, Y): # implement with simple function in tf
    logits = tf.transpose(Z3)
    labels = tf.transpose(Y)
    cost = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(logits=logits, labels=labels))
    return cost
```


```python
def random_mini_batches(X, Y, mini_batch_size = 64, seed = 0):
    m = X.shape[1]                  # number of training examples
    mini_batches = []
    np.random.seed(seed)
    
    # Step 1: Shuffle (X, Y)
    permutation = list(np.random.permutation(m))
    shuffled_X = X[:, permutation]
    shuffled_Y = Y[:, permutation].reshape((Y.shape[0],m))

    # Step 2: Partition (shuffled_X, shuffled_Y). Minus the end case.
    num_complete_minibatches = math.floor(m/mini_batch_size) # number of mini batches
    for k in range(0, num_complete_minibatches): # select K samples from front
        mini_batch_X = shuffled_X[:, k * mini_batch_size : k * mini_batch_size + mini_batch_size]
        mini_batch_Y = shuffled_Y[:, k * mini_batch_size : k * mini_batch_size + mini_batch_size]
        mini_batch = (mini_batch_X, mini_batch_Y) # mini_batch = dataset size of K
        mini_batches.append(mini_batch) # mini_batches = list of mini_batch
    
    # Handling the end case (last mini-batch < mini_batch_size)
    if m % mini_batch_size != 0:
        mini_batch_X = shuffled_X[:, num_complete_minibatches * mini_batch_size : m]
        mini_batch_Y = shuffled_Y[:, num_complete_minibatches * mini_batch_size : m]
        mini_batch = (mini_batch_X, mini_batch_Y)
        mini_batches.append(mini_batch)
    
    return mini_batches
```


```python
def model(X_train, Y_train, X_test, Y_test, learning_rate = 0.0001,
          num_epochs = 1500, minibatch_size = 32, print_cost = True): # shallow NN with mini-batches
    
    ops.reset_default_graph()                         
    tf.set_random_seed(1)                             
    seed = 3                                         
    (n_x, m) = X_train.shape                          
    n_y = Y_train.shape[0]                            
    costs = []                                        
    
    X, Y = create_placeholders(n_x, n_y)  # Create Placeholders of shape (n_x, n_y)
    parameters = initialize_parameters()  # Initialize parameters
    Z3 = forward_propagation(X,parameters) # Forward 
    cost = compute_cost(Z3,Y) # Cost
    optimizer = tf.train.AdamOptimizer(learning_rate=learning_rate).minimize(cost) # Adam Optimizer (GD)
    
    init = tf.global_variables_initializer()
    with tf.Session() as sess: # Start Learning
        sess.run(init)
        for epoch in range(num_epochs): # Gradient Descent x (num_epochs * num_minibatches) 
            epoch_cost = 0.                      
            num_minibatches = int(m / minibatch_size) # number of minibatches 
            seed += 1
            minibatches = random_mini_batches(X_train, Y_train, minibatch_size, seed)

            for minibatch in minibatches:
                (minibatch_X, minibatch_Y) = minibatch  # select one minibatch (32 samples in minibatch)
                _ , minibatch_cost = sess.run([optimizer, cost], feed_dict={X: minibatch_X, Y: minibatch_Y})
                epoch_cost += minibatch_cost / minibatch_size

            if print_cost == True and epoch % 100 == 0: # print every 100 epochs
                print ("Cost after epoch %i: %f" % (epoch, epoch_cost))
            if print_cost == True and epoch % 5 == 0:
                costs.append(epoch_cost)
                
        # plot using matplotlib
        plt.plot(np.squeeze(costs))
        plt.ylabel('cost')
        plt.xlabel('iterations (per fives)')
        plt.title("Learning rate =" + str(learning_rate))
        plt.show()

        # Computing Accuracy
        parameters = sess.run(parameters)
        print ("Parameters have been trained!")
        correct_prediction = tf.equal(tf.argmax(Z3), tf.argmax(Y))
        accuracy = tf.reduce_mean(tf.cast(correct_prediction, "float"))

        print ("Train Accuracy:", accuracy.eval({X: X_train, Y: Y_train}))
        print ("Test Accuracy:", accuracy.eval({X: X_test, Y: Y_test}))
        
        return parameters
```

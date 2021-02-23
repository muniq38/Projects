```python
import numpy as np
import tensorflow.compat.v1 as tf
import matplotlib.pyplot as plt
import h5py
import math
np.random.seed(1)
```


```python
def create_placeholders(n_H0, n_W0, n_C0, n_y):
    X = tf.placeholder(dtype=tf.float32, shape=[None, n_H0, n_W0, n_C0])
    Y = tf.placeholder(dtype=tf.float32, shape=[None, n_y])
    return X, Y
```


```python
def initialize_parameters():
    tf.set_random_seed(1)       
    W1 = tf.get_variable(name="W1", shape=[4, 4, 3, 8], initializer=tf.contrib.layers.xavier_initializer(seed = 0))
    W2 = tf.get_variable(name="W2", shape=[2, 2, 8, 16], initializer=tf.contrib.layers.xavier_initializer(seed = 0))
    parameters = {"W1": W1,"W2": W2}
    return parameters
```


```python
def forward_propagation(X, parameters): # CONV - RELU - POOL(1/8) - CONV - RELU - POOL(1/4) - FLAT - FCN
    W1 = parameters['W1'] # retrieve parameters
    W2 = parameters['W2']
    
    Z1 = tf.nn.conv2d(X, W1, strides = [1,1,1,1], padding = 'SAME') 
    A1 = tf.nn.relu(Z1)
    P1 = tf.nn.max_pool(A1, ksize = [1,8,8,1], strides = [1,8,8,1], padding = 'SAME')
    
    Z2 = tf.nn.conv2d(P1,W2, strides = [1,1,1,1], padding = 'SAME')
    A2 = tf.nn.relu(Z2)
    P2 = tf.nn.max_pool(A2, ksize = [1,4,4,1], strides = [1,4,4,1], padding = 'SAME')
    
    F = tf.contrib.layers.flatten(P2)
    Z3 = tf.contrib.layers.fully_connected(F, 6, activation_fn=None)

    return Z3
```


```python
def compute_cost(Z3, Y):
    cost = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(logits=Z3, labels=Y))
    return cost
```


```python
def model(X_train, Y_train, X_test, Y_test, learning_rate = 0.009, num_epochs = 100, minibatch_size = 64, print_cost = True):
    
    tf.set_random_seed(1)                                                                 
    (m, n_H0, n_W0, n_C0) = X_train.shape             
    n_y = Y_train.shape[1]                            
    costs = []
    seed = 3
    
    # pipeline where tf.Session will work on
    init = tf.global_variables_initializer()
    X, Y = create_placeholders(n_H0, n_W0, n_C0, n_y)  # create (X,Y) placeholder, where pipeline starts
    parameters = initialize_parameters()  # initialize parameters
    Z3 = forward_propagation(X,parameters)  # Forward with CNN
    cost = compute_cost(Z3,Y)  # Compute Cost
    optimizer = tf.train.AdamOptimizer(learning_rate=learning_rate).minimize(cost)  # Backprop
    
    with tf.Session() as sess:  # Turn Session on
        sess.run(init)  # Run initialize pipeline
        
        for epoch in range(num_epochs): # GradDesc iteration = num_epochs x num_minibatches
            minibatch_cost = 0. # initialize cost and seed
            seed = seed + 1
            num_minibatches = int(m / minibatch_size) 
            minibatches = random_mini_batches(X_train, Y_train, minibatch_size, seed) # shuffle train set

            for minibatch in minibatches: # 1 minibatch = 1 GradDesc
                (minibatch_X, minibatch_Y) = minibatch  # Run CNN learning pipeline
                _, temp_cost = sess.run([optimizer, cost], feed_dict={X: minibatch_X, Y: minibatch_Y})
                minibatch_cost += temp_cost / num_minibatches
                
            if print_cost == True and epoch % 5 == 0:
                print ("Cost after epoch %i: %f" % (epoch, minibatch_cost)) # print cost
            if print_cost == True and epoch % 1 == 0:
                costs.append(minibatch_cost)

        # Calculate accuracy (test)
        predict_op = tf.argmax(Z3, 1)
        correct_prediction = tf.equal(predict_op, tf.argmax(Y, 1))
        accuracy = tf.reduce_mean(tf.cast(correct_prediction, "float"))
        print(accuracy)
        train_accuracy = accuracy.eval({X: X_train, Y: Y_train})
        test_accuracy = accuracy.eval({X: X_test, Y: Y_test})
        print("Train Accuracy:", train_accuracy)
        print("Test Accuracy:", test_accuracy)
                
         # Additional task : plot the cost
        plt.plot(np.squeeze(costs))
        plt.ylabel('cost')
        plt.xlabel('iterations (per tens)')
        plt.title("Learning rate =" + str(learning_rate))
        plt.show()
        
        return train_accuracy, test_accuracy, parameters
```

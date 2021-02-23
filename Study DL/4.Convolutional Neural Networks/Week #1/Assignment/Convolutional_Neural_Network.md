```python
import numpy as np
import h5py
np.random.seed(1)
```


```python
def zero_pad(X, pad):
    X_pad = np.pad(X, ((0,0), (pad,pad), (pad,pad), (0,0)), mode='constant', constant_values = (0,0))
    return X_pad
```


```python
def conv_single_step(a_slice_prev, W, b): # single convolution (filter -> single unit) operation
    s = np.sum(W*a_slice_prev)+b
    return float(s)
```


```python
def conv_forward(A_prev, W, b, hparameters):
    
    (m, n_H_prev, n_W_prev, n_C_prev) = A_prev.shape # Retrieving shapes and hparams
    (f, f, n_C_prev, n_C) = W.shape
    stride = hparameters["stride"]
    pad = hparameters["pad"]
    
    n_H = int( (n_H_prev-f+2*pad)/stride )+1  # dimension of next output
    n_W = int( (n_W_prev-f+2*pad)/stride )+1
    Z = np.zeros((m, n_H, n_W, n_C))  # initialize output Z
    A_prev_pad = zero_pad(A_prev,pad)  # apply padding to A_prev (activated samples)
    
    for i in range(m):  # use m samples in NN             
        a_prev_pad = A_prev_pad[i]  # Take an activated sample (3D matrix)           
        for h in range(n_H):  # moving filter's position         
            for w in range(n_W):       
                for c in range(n_C):   
                    # placing fxf filter 
                    vert_start = h*stride
                    vert_end = vert_start+f   
                    horiz_start = w*stride
                    horiz_end = horiz_start+f
                    # slice the sample with filter, then compress to a next single unit   
                    a_slice_prev = a_prev_pad[vert_start:vert_end, horiz_start:horiz_end, :]
                    Z[i, h, w, c] = conv_single_step(a_slice_prev, W[...,c], b[...,c])
    
    assert(Z.shape == (m, n_H, n_W, n_C))
    cache = (A_prev, W, b, hparameters)  # cache is saved for backprop
    return Z, cache
```


```python
def pool_forward(A_prev, hparameters, mode = "max"):
    
    (m, n_H_prev, n_W_prev, n_C_prev) = A_prev.shape  # Retrieving shapes and hparams
    f = hparameters["f"] # call f (for pooling, not dimension of any layer)
    stride = hparameters["stride"]
    
    n_C = n_C_prev  # dimensions of next output
    n_H = int(1 + (n_H_prev - f) / stride) 
    n_W = int(1 + (n_W_prev - f) / stride)
    A = np.zeros((m, n_H, n_W, n_C))  # initialize output A            
    
    for i in range(m):  # use m samples in NN                             
        for h in range(n_H):                    
            for w in range(n_W):               
                for c in range (n_C):
                    # placing fxf block to pool(extract)
                    vert_start = h*stride
                    vert_end = vert_start+f   
                    horiz_start = w*stride
                    horiz_end = horiz_start+f
                    # slice the sample with filter, then to a next single unit   
                    a_prev_slice = A_prev[i, vert_start:vert_end, horiz_start:horiz_end, c]
                    if mode == "max":
                        A[i, h, w, c] = np.max(a_prev_slice)
                    elif mode == "average":
                        A[i, h, w, c] = np.mean(a_prev_slice)
                        
    cache = (A_prev, hparameters)
    assert(A.shape == (m, n_H, n_W, n_C))  # cache is saved for backprop
    return A, cache
```


```python
def conv_backward(dZ, cache):
    
    (A_prev, W, b, hparameters) = cache  # Retrieving shapes and hparams
    (m, n_H_prev, n_W_prev, n_C_prev) = A_prev.shape
    (f, f, n_C_prev, n_C) = W.shape
    stride = hparameters["stride"]
    pad = hparameters["pad"]
    (m, n_H, n_W, n_C) = dZ.shape
    
    dA_prev = np.zeros(A_prev.shape) # initialize outputs
    dW = np.zeros(W.shape)
    db = np.zeros((1, 1, 1, n_C))
    A_prev_pad = zero_pad(A_prev,pad)
    dA_prev_pad = zero_pad(dA_prev,pad)
    
    for i in range(m):                      
        a_prev_pad = A_prev_pad[i]
        da_prev_pad = dA_prev_pad[i]
        for h in range(n_H):                
            for w in range(n_W):             
                for c in range(n_C):      
                    # placing fxf filter
                    vert_start = h*stride
                    vert_end = vert_start+f
                    horiz_start = w*stride
                    horiz_end = horiz_start+f
                    # slice the sample with filter, then compute dW and db from it
                    a_slice = a_prev_pad[vert_start:vert_end, horiz_start:horiz_end, :]
                    da_prev_pad[vert_start:vert_end, horiz_start:horiz_end, :] += W[...,c] * dZ[i, h, w, c]
                    dW[...,c] += a_slice * dZ[i, h, w, c]
                    db[...,c] += dZ[i, h, w, c]
                    
        dA_prev[i] = da_prev_pad[pad:-pad, pad:-pad, :] # remove pad and finish da_prev
        
    assert(dA_prev.shape == (m, n_H_prev, n_W_prev, n_C_prev))
    return dA_prev, dW, db
```


```python
def create_mask_from_window(x): # Rollback operation of maxpool
    mask = (x==np.max(x))
    return mask
```


```python
def distribute_value(dz, shape): # Rollback operation of averagepool
    (n_H, n_W) = shape)
    average = dz/(n_H*n_W)
    a = np.ones(shape)*average
    return a
```


```python
def pool_backward(dA, cache, mode = "max"):
    
    (A_prev, hparameters) = cache
    stride = hparameters["stride"]
    f = hparameters["f"]
    m, n_H_prev, n_W_prev, n_C_prev = A_prev.shape
    m, n_H, n_W, n_C = dA.shape
    dA_prev = np.zeros(A_prev.shape)
    
    for i in range(m):                       
        a_prev = A_prev[i]
        for h in range(n_H):                   
            for w in range(n_W):              
                for c in range(n_C):           
                    # placing fxf block
                    vert_start = h*stride
                    vert_end = vert_start+f
                    horiz_start = w*stride
                    horiz_end = horiz_start+f
                    
                    if mode == "max": # backprop for maxpool
                        a_prev_slice = a_prev[vert_start:vert_end, horiz_start:horiz_end, c]
                        mask = create_mask_from_window(a_prev_slice)
                        dA_prev[i, vert_start: vert_end, horiz_start: horiz_end, c] += mask*dA[i,h,w,c]
                        
                    elif mode == "average": # backprop for averagepool
                        da = dA[i,h,w,c]
                        shape = (f,f)
                        dA_prev[i, vert_start: vert_end, horiz_start: horiz_end, c] += distribute_value(da,shape)

    assert(dA_prev.shape == A_prev.shape)
    return dA_prev
```

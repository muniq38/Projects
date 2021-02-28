```python
import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
from sklearn.linear_model import SGDRegressor
from sklearn.linear_model import Ridge
from sklearn.linear_model import Lasso
from sklearn.linear_model import ElasticNet
from sklearn.linear_model import LogisticRegression
from sklearn.preprocessing import PolynomialFeatures
from sklearn.metrics import mean_squared_error
from sklearn.model_selection import train_test_split
from sklearn.pipeline import Pipeline
from sklearn.base import clone
from sklearn import datasets
```


```python
from IPython.core.interactiveshell import InteractiveShell
InteractiveShell.ast_node_interactivity = "all" # last / all
```


```python
X = 2*np.random.rand(100,1) # X는 길이 100인 열벡터
y = 3*X + 4 + np.random.randn(100,1) # y = 3X + 4 + noise
```


```python
X_b = np.c_[np.ones((100,1)), X] # X_b = [1 x], theta = [th0 th1], h(X_b) = [th1]x + [th0]
theta_best = np.linalg.inv(X_b.T.dot(X_b)).dot(X_b.T).dot(y) # numerical theta 구하기 = inv(X'X)X'y 
theta_best # [[4],[3]] 근처가 나와야함
```




    array([[4.34336618],
           [2.75391162]])




```python
def Plot(X, theta, linecol="r-", datacol="b.", rng=(0,2)): # 데이터 시각화 함수
    (s,e) = rng
    X_line = np.array([[s],[e]]) # X=s,X=e를 양 끝점으로 하는 직선
    X_line_b = np.c_[np.ones((2,1)), X_line]
    pred_line = X_line_b.dot(theta) # predict = h(X)
    plt.plot(X_line, pred_line, "r-") # 직선 추세선 [h(X)]
    plt.plot(X, y, "b.")
    plt.axis([s, e, np.floor(pred_line[0]-4), np.ceil(pred_line[1]+4)]) 
```


```python
Plot(X, theta_best)
plt.show() # 추세선이 잘 그려진 것을 확인할 수 있다.
```


![png](output_5_0.png)



```python
lin_reg = LinearRegression() # [cost-MSE] Linear Regression을 모델로 사용
lin_reg.fit(X,y) # fit
lin_reg.predict(X_line) # linreg predict (x=0,2)
X_line_b.dot(theta_best) # numerical predict (x=0,2)
```




    array([[4.34336618],
           [9.85118941]])




```python
lin_reg.intercept_, lin_reg.coef_ # Linear Regression 모델의 파라미터가 pint(X)y와 유사
np.linalg.pinv(X_b).dot(y) # pint(X)는 특잇값 분해(SVD)를 통해 얻을 수 있음 
```




    (array([4.34336618]), array([[2.75391162]]))






    array([[4.34336618],
           [2.75391162]])




```python
def Linear_GradDesc(X, learning_rate=0.1, plot=False, n_iterations=1000): # Gradient Descent 구현
    m = X.shape[0] # train-set의 sample 수
    X_b = np.c_[np.ones((m,1)), X] # X_b = [1 x], theta = [th0 th1], h(X_b) = [th1]x + [th0]
    theta = np.random.randn(2,1) # Initialize
    for iteration in range(n_iterations): # 1-epoch = 1-learn
        gradients = 2/m * X_b.T.dot(X_b.dot(theta)-y) # 벡터 theta[1~n] 각 원소에 대한 MSE cost의 편미분벡터 = X'(thetaX-y)
        theta -= learning_rate*gradients # GradDesc 기본공식
        if plot: Plot(X,theta)
    if plot: plt.show()
    return theta # 학습된 파라미터
```


```python
Linear_GradDesc(X, 0.1, True, 5)
Linear_GradDesc(X, 0.02, True, 15) # learning_rate가 작으면 학습이 느려진다.
Linear_GradDesc(X, 0.4, True, 4) # learning_rate가 크면 학습이 불안정해진다.
```


![png](output_9_0.png)





    array([[3.78549096],
           [2.86167391]])




![png](output_9_2.png)





    array([[2.3119142 ],
           [2.82633064]])




![png](output_9_4.png)





    array([[2.4703284 ],
           [3.05491163]])




```python
def learning_schedule(t, t0=5, t1=50):
    return t0/(t+t1) # t에 대한 유리함수 형태로 감소시킴

def Linear_StocGradDesc(X, plot=False, plot_iteration=20, n_epochs=100): # Stochastic Gradient Descent 구현
    m = X.shape[0] 
    X_b = np.c_[np.ones((m,1)), X]
    theta = np.random.randn(2,1) 
    np.random.seed(42)
    for epoch in range(n_epochs): # 1-epoch = m-learn : SGD 최대장점
        np.random.shuffle(X_b) # stochastic(확률적)인 이유
        np.random.shuffle(y)
        for i in range(m):
            xi, yi = X_b[1], y[1]
            xi.reshape(1,2)
            yi.reshape(1,1)
            gradients = 2 * xi.T.dot(xi.dot(theta)-yi) # 벡터 theta[1~n] 각 원소에 대한 MSE cost의 편미분벡터 = X'(thetaX-y)
            learning_rate = learning_schedule(epoch*m+i) # SGD는 답에 갈수록 불안정하기 때문에 learning_rate를 감쇠시킴
            theta -= learning_rate*gradients # GradDesc 기본공식
            if plot and plot_iteration > epoch*m+i : Plot(X,theta)
    if plot: plt.show()
    return theta # 학습된 파라미터
```


```python
Linear_StocGradDesc(X, plot=True, n_epochs=50)
```


    ---------------------------------------------------------------------------

    ValueError                                Traceback (most recent call last)

    <ipython-input-68-9dfd13b37434> in <module>
    ----> 1 Linear_StocGradDesc(X, plot=True, n_epochs=50)
    

    <ipython-input-67-b57f7bc6069b> in Linear_StocGradDesc(X, plot, plot_iteration, n_epochs)
         14             xi.reshape(1,2)
         15             yi.reshape(1,1)
    ---> 16             gradients = 2 * xi.T.dot(xi.dot(theta)-yi) # 벡터 theta[1~n] 각 원소에 대한 MSE cost의 편미분벡터 = X'(thetaX-y)
         17             learning_rate = learning_schedule(epoch*m+i) # SGD는 답에 갈수록 불안정하기 때문에 learning_rate를 감쇠시킴
         18             theta -= learning_rate*gradients # GradDesc 기본공식
    

    ValueError: shapes (2,) and (1,) not aligned: 2 (dim 0) != 1 (dim 0)



```python

```

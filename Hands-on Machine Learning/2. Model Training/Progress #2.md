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




    array([[3.98554103],
           [2.97021897]])




```python
def Plot(X, y, theta, linecol="r.", datacol="b.", rng=(0,2)): # 데이터 시각화 함수
    m = X.shape[0]
    (s,e) = rng # x축의 범위
    X_b = np.c_[np.ones((m,1)), X]
    pred_line = X_b.dot(theta) # predict = h(X)
    plt.plot(X[:,0:1], pred_line, linecol) # 추세선 [h(X)]
    plt.plot(X[:,0:1], y, datacol)
    plt.axis([s, e, np.floor(min(pred_line)-4), np.ceil(max(pred_line)+4)]) 
```


```python
Plot(X, y, theta_best, "r-")
plt.show() # 추세선이 잘 그려진 것을 확인할 수 있다.
```


    
![png](output_5_0.png)
    



```python
lin_reg = LinearRegression() # [cost-MSE] Linear Regression을 모델로 사용
lin_reg.fit(X,y) # fit
lin_reg.predict(X[3:4]) # linreg predict (x=X[3])
X_b[3:4].dot(theta_best) # numerical predict (x=X[3])
```




    LinearRegression()






    array([[6.18708398]])






    array([[6.18708398]])




```python
lin_reg.intercept_, lin_reg.coef_ # Linear Regression 모델의 파라미터가 pint(X)y와 유사
np.linalg.pinv(X_b).dot(y) # pint(X)는 특잇값 분해(SVD)를 통해 얻을 수 있음 
```




    (array([3.98554103]), array([[2.97021897]]))






    array([[3.98554103],
           [2.97021897]])




```python
def Linear_GradDesc(X, y, learning_rate=0.1, plot=False, plot_iterations=15, linecol="r-", n_iterations=1000, rng=(0,2)): # Gradient Descent 구현
    m = X.shape[0] # train-set의 sample 수
    X_b = np.c_[np.ones((m,1)), X] # X_b = [1 x], theta = [th0 th1], h(X_b) = [th1]x + [th0]
    theta = np.random.randn(X_b.shape[1],1) # Initialize
    for i in range(n_iterations): # 1-epoch = 1-learn
        gradients = 2/m * X_b.T.dot(X_b.dot(theta)-y) # 벡터 theta[1~n] 각 원소에 대한 MSE cost의 편미분벡터 = X'(thetaX-y)
        theta -= learning_rate*gradients # GradDesc 기본공식
        if plot and plot_iterations > i: Plot(X,y,theta,linecol=linecol,rng=rng)
    if plot: plt.show()
    return theta # 학습된 파라미터
```


```python
Linear_GradDesc(X, y, 0.1, True, 15)
Linear_GradDesc(X, y, 0.02, True, 15) # learning_rate가 작으면 학습이 느려진다.
Linear_GradDesc(X, y, 0.4, True, 4) # learning_rate가 크면 학습이 불안정해진다.
```


    
![png](output_9_0.png)
    





    array([[3.98554103],
           [2.97021897]])




    
![png](output_9_2.png)
    





    array([[3.9825759 ],
           [2.97271018]])




    
![png](output_9_4.png)
    





    array([[3.98554103],
           [2.97021897]])




```python
sgd_reg = SGDRegressor(max_iter=1000, tol=1e-3, penalty=None, eta0=0.1) # Stochastic Gradient Descent를 모델로 사용
sgd_reg.fit(X,y.ravel()) # fit
sgd_reg.intercept_, sgd_reg.coef_ # 두 모델로 얻어낸 parameter 비교
lin_reg.intercept_, lin_reg.coef_ 
```




    SGDRegressor(eta0=0.1, penalty=None)






    (array([3.97308109]), array([3.06297367]))






    (array([3.98554103]), array([[2.97021897]]))




```python
def learning_schedule(t, t0=5, t1=50):
    return t0/(t+t1) # t에 대한 유리함수 형태로 감소시킴

def Linear_StocGradDesc(X, y, plot=False, mb_size=1, linecol="r-", plot_iterations=10, n_epochs=50): # Stochastic(Mini-batch) Gradient Descent 구현
    m = X.shape[0] 
    mb = int(m/mb_size) # mb_size=1이면 SGD, mb_size=m이면 batch(기본)
    rand = np.arange(mb) 
    X_b = np.c_[np.ones((m,1)), X]
    theta = np.random.randn(X_b.shape[1],1) 
    for epoch in range(n_epochs): # 1-epoch = mb-learn : 더 효율적임
        np.random.shuffle(rand) # X,y에서 순서대로 꺼낼 때 permutation 결정
        for i in range(mb):
            xi = X_b[mb_size*rand[i]:mb_size*(rand[i]+1)] # 순서대로 샘플 mb_size개 가져감
            yi = y[mb_size*rand[i]:mb_size*(rand[i]+1)]
            gradients = 2/mb_size * xi.T.dot(xi.dot(theta)-yi) # 벡터 theta[1~n] 각 원소에 대한 MSE cost의 편미분벡터, 사실상 근사값
            learning_rate = learning_schedule(epoch*mb+i) # SGD는 답에 갈수록 불안정하기 때문에 learning_rate를 감쇠시킴
            theta -= learning_rate*gradients # GradDesc 기본공식
            if plot and plot_iterations > epoch*mb+i : Plot(X,y,theta,linecol=linecol)
    if plot: plt.show()
    return theta # 학습된 파라미터
```


```python
Linear_StocGradDesc(X, y, plot=True) # Stochastic GradDesc
Linear_StocGradDesc(X, y, plot=True, mb_size=10) # Mini-batch(10) GradDesc
Linear_StocGradDesc(X, y, plot=True, mb_size=100) # Batch GradDesc 
```


    
![png](output_12_0.png)
    





    array([[3.98243578],
           [2.96888897]])




    
![png](output_12_2.png)
    





    array([[3.9484196 ],
           [3.00036975]])




    
![png](output_12_4.png)
    





    array([[3.34673935],
           [3.5069211 ]])




```python
X2 = 9*np.random.rand(100,1)-6 # X2는 100x1 벡터
y2 = 0.1*(X2**3) + 0.5*(X2**2) - X2 + 1.5 + np.random.rand(100,1) # y = X*X + X + 2 + noise
poly_features = PolynomialFeatures(degree=3, include_bias=False)
X_poly = poly_features.fit_transform(X2) # [X]를 [X X**2 X**3] 형태로 변환
X_poly[0], y2[0]
```




    (array([  -5.53491816,   30.63531907, -169.56398398]), array([6.27386555]))




```python
lin_reg.fit(X_poly, y2) # fit (Linear Regression) - 다항식의 경우에도 poly_features 생성 후 선형회귀 적용 가능
lin_reg.predict(X_poly[0:1]), y2[0] # predict
lin_reg.intercept_, lin_reg.coef_ # [[2],[-1 0.5 0.1]] 근처가 나와야함
theta_poly_lin = Linear_GradDesc(X_poly, y2, learning_rate=0.0002, n_iterations=5000) # fit (수제모델)
Plot(X_poly, y2, theta_poly_lin, rng=(-6,3)) 
theta_poly_lin # [2,-1,0.5,0.1] 근처가 나와야함
```




    LinearRegression()






    (array([[5.79316303]]), array([6.27386555]))






    (array([1.98105075]), array([[-1.03587057,  0.50738766,  0.10300141]]))






    array([[ 1.12130782],
           [-1.13694195],
           [ 0.64115314],
           [ 0.12592196]])




    
![png](output_14_4.png)
    



```python
def plot_learning_curves(model, X, y): # 학습 곡선 : train-set의 크기를 점점 늘려갈 때 두 종류의 오차 확인 
    X_train, X_dev, y_train, y_dev = train_test_split(X, y, test_size=0.2) # train, dev, test셋 분할
    train_error, dev_error = [], []
    for m in range(1, X_train.shape[0]): # 매번 m개 학습 
        model.fit(X_train[:m], y_train[:m]) # train-fit
        y_train_predict = model.predict(X_train[:m]) # train-set predict
        y_dev_predict = model.predict(X_dev) # dev-set predict
        train_error.append(mean_squared_error(y_train[:m], y_train_predict)) # train-set의 MSE
        dev_error.append(mean_squared_error(y_dev, y_dev_predict)) # dev-set의 MSE
    plt.plot(np.sqrt(train_error), "r-", linewidth=2, label="train-set") 
    plt.plot(np.sqrt(dev_error), "b-", linewidth=3, label="dev-set")
```


```python
plot_learning_curves(lin_reg, X, y) # train과 dev가 높은 값에서 서로 수렴 : high-biased
```


    
![png](output_16_0.png)
    



```python
poly_reg = Pipeline([
    ("poly_features", PolynomialFeatures(degree=10, include_bias=False)), # poly_features 생성
    ("lin_reg", LinearRegression()) # 바로 선형회귀
])
```


```python
plt.ylim(0,3)
plot_learning_curves(poly_reg, X, y) # train과 dev의 수렴값 사이 공간이 있음 : high-variance
```




    (0.0, 3.0)




    
![png](output_18_1.png)
    



```python
poly_reg.fit(X,y)
poly_predict = poly_reg.predict(X)
lin_predict = lin_reg.predict(X)
plt.plot(X,lin_predict,"b.")
plt.plot(X,poly_predict,"g.")
plt.plot(X,y,"r.")
plt.show()
mean_squared_error(y, poly_predict)
```




    Pipeline(steps=[('poly_features',
                     PolynomialFeatures(degree=10, include_bias=False)),
                    ('lin_reg', LinearRegression())])






    [<matplotlib.lines.Line2D at 0x209f7a6e400>]






    [<matplotlib.lines.Line2D at 0x209f7a6e700>]






    [<matplotlib.lines.Line2D at 0x209f7715e20>]




    
![png](output_19_4.png)
    





    0.9059741165627951



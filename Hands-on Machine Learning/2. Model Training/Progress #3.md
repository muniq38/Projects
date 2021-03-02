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




    array([[3.92452247],
           [3.01152493]])




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






    array([[7.35078083]])






    array([[7.35078083]])




```python
lin_reg.intercept_, lin_reg.coef_ # Linear Regression 모델의 파라미터가 pint(X)y와 유사
np.linalg.pinv(X_b).dot(y) # pint(X)는 특잇값 분해(SVD)를 통해 얻을 수 있음 
```




    (array([3.92452247]), array([[3.01152493]]))






    array([[3.92452247],
           [3.01152493]])




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
    





    array([[3.92452247],
           [3.01152493]])




    
![png](output_9_2.png)
    





    array([[3.92024008],
           [3.01507222]])




    
![png](output_9_4.png)
    





    array([[3.92452247],
           [3.01152493]])




```python
sgd_reg = SGDRegressor(max_iter=1000, tol=1e-3, penalty=None, eta0=0.1) # Stochastic Gradient Descent를 모델로 사용
sgd_reg.fit(X,y.ravel()) # fit
sgd_reg.intercept_, sgd_reg.coef_ # 두 모델로 얻어낸 parameter 비교
lin_reg.intercept_, lin_reg.coef_ 
```




    SGDRegressor(eta0=0.1, penalty=None)






    (array([3.8609596]), array([3.04455603]))






    (array([3.92452247]), array([[3.01152493]]))




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
    





    array([[3.92399517],
           [3.01255404]])




    
![png](output_12_2.png)
    





    array([[3.92073876],
           [3.01600385]])




    
![png](output_12_4.png)
    





    array([[3.57654999],
           [3.29976575]])




```python
X2 = 9*np.random.rand(100,1)-6 # X2는 100x1 벡터
y2 = 0.1*(X2**3) + 0.5*(X2**2) - X2 + 1.5 + np.random.rand(100,1) # y = X*X + X + 2 + noise
poly_features = PolynomialFeatures(degree=3, include_bias=False)
X_poly = poly_features.fit_transform(X2) # [X]를 [X X**2 X**3] 형태로 변환
X_poly[0], y2[0]
```




    (array([2.02879971, 4.11602827, 8.35059696]), array([2.99935416]))




```python
lin_reg.fit(X_poly, y2) # fit (Linear Regression) - 다항식의 경우에 poly_features+선형회귀 적용 
lin_reg.predict(X_poly[0:1]), y2[0] # predict
lin_reg.intercept_, lin_reg.coef_ # [[2],[-1 0.5 0.1]] 근처가 나와야함
theta_poly_lin = Linear_GradDesc(X_poly, y2, learning_rate=0.00002, n_iterations=10000) # fit (수제) 
Plot(X_poly, y2, theta_poly_lin, rng=(-6,3)) 
theta_poly_lin # [2,-1,0.5,0.1] 근처가 나와야함, 수제 모델은 규제가 없어서 learning_rate가 매우 낮아야 학습됨
```




    LinearRegression()






    (array([[2.92078916]]), array([2.99935416]))






    (array([1.94760344]), array([[-0.96737061,  0.51062701,  0.0998769 ]]))






    array([[ 1.44601797],
           [-1.18822237],
           [ 0.5995634 ],
           [ 0.12102137]])




    
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
plot_learning_curves(lin_reg, X, y) # train과 dev가 서로 수렴 : biased
```


    
![png](output_16_0.png)
    



```python
poly_reg = Pipeline([
    ("poly_features", PolynomialFeatures(degree=30, include_bias=False)), # poly_features 생성
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
                     PolynomialFeatures(degree=30, include_bias=False)),
                    ('lin_reg', LinearRegression())])






    [<matplotlib.lines.Line2D at 0x277b3c91850>]






    [<matplotlib.lines.Line2D at 0x277b3c91ca0>]






    [<matplotlib.lines.Line2D at 0x277b3c91fd0>]




    
![png](output_19_4.png)
    





    0.932798311971355




```python
ridge_reg = Ridge(alpha=1, solver="cholesky") # Ridge Regression를 모델로 사용 (= L2 Regularization) 
ridge_reg.fit(X,y) # fit (cholesky 분해로 정규방정식의 해를 구함)
sgd_l2_reg = SGDRegressor(penalty="l2", alpha=0.07, max_iter=5000) # L2 Regularization을 적용한 SGD를 모델로 사용 
sgd_l2_reg.fit(X,y) # fit (GradDesc로 최적의 해 구함)
ridge_reg.intercept_, ridge_reg.coef_ # 두 모델로 얻어낸 parameter 비교
sgd_l2_reg.intercept_, sgd_l2_reg.coef_
```




    Ridge(alpha=1, solver='cholesky')



    C:\Users\andre\anaconda3\lib\site-packages\sklearn\utils\validation.py:72: DataConversionWarning: A column-vector y was passed when a 1d array was expected. Please change the shape of y to (n_samples, ), for example using ravel().
      return f(**kwargs)
    




    SGDRegressor(alpha=0.07, max_iter=5000)






    (array([4.01798495]), array([[2.92111123]]))






    (array([3.91838635]), array([2.9248527]))




```python
lasso_reg = Lasso(alpha=0.025) # Lasso Regression을 모델로 사용 (= L1 Regularization)
lasso_reg.fit(X,y) # fit
sgd_l1_reg = SGDRegressor(penalty="l1", alpha=0.25, max_iter=5000) # L1 Regularization을 적용한 SGD를 모델로 사용
sgd_l1_reg.fit(X,y) # fit
lasso_reg.intercept_, lasso_reg.coef_ # 두 모델로 얻어낸 parameter 비교하며 hyperparameter 조정
sgd_l1_reg.intercept_, sgd_l1_reg.coef_ 
```




    Lasso(alpha=0.025)



    C:\Users\andre\anaconda3\lib\site-packages\sklearn\utils\validation.py:72: DataConversionWarning: A column-vector y was passed when a 1d array was expected. Please change the shape of y to (n_samples, ), for example using ravel().
      return f(**kwargs)
    




    SGDRegressor(alpha=0.25, max_iter=5000, penalty='l1')






    (array([4.00451127]), array([2.93414539]))






    (array([3.8457437]), array([2.96157832]))




```python
elastic_net = ElasticNet(alpha=0.015, l1_ratio=0.5) # ElasticNet을 모델로 사용 (= L1과 L2의 혼합)
elastic_net.fit(X,y)
elastic_net.intercept_, elastic_net.coef_ # parameter 확인
```




    ElasticNet(alpha=0.015)






    (array([4.01860165]), array([2.92051464]))




```python
def Ridge_GradDesc(X, y, learning_rate=0.1, alpha=1, n_iterations=1000): # Gradient Descent with L2 Regularization 구현
    m = X.shape[0] 
    X_b = np.c_[np.ones((m,1)), X] # X_b = [1 x], theta = [th0 th1], h(X_b) = [th1]x + [th0]
    theta = np.random.randn(X_b.shape[1],1) # Initialize
    for i in range(n_iterations): 
        gradients = 2/m * X_b.T.dot(X_b.dot(theta)-y) # 벡터 theta[1~n] 각 원소에 대한 MSE cost의 편미분벡터 = X'(thetaX-y)
        gradients += alpha*theta # L2 Regularization = alpha*sum(theta**2)/2 - 편미분 시 alpha*theta
        gradients[0] -= alpha*theta[0] # 단, th0에는 규제가 적용되지 않음 (bias)
        theta -= learning_rate*gradients # GradDesc 기본공식
    return theta # 학습된 파라미터
```


```python
theta_poly_lin = Ridge_GradDesc(X_poly, y2, learning_rate=0.0001, n_iterations=10000) # fit (수제 + L2 Regularization) 
Plot(X_poly, y2, theta_poly_lin, rng=(-6,3)) 
theta_poly_lin # [2,-1,0.5,0.1] 근처가 나와야함
```




    array([[ 1.64615634],
           [-0.943245  ],
           [ 0.51915363],
           [ 0.09845951]])




    
![png](output_24_1.png)
    



```python
ply_features = PolynomialFeatures(degree=7, include_bias=False) # 7차 polynomial regression
X_ply = ply_features.fit_transform(X)
theta_poly_l2 = Ridge_GradDesc(X_ply, y, alpha=0.2, learning_rate=0.0002, n_iterations=3000) # fit (수제 + L2 Regularization)
Plot(X_ply, y, theta_poly_l2, linecol="g.") # L2 규제를 적용한 쪽이 과적합에 더 안정하다는 것을 알 수 있음
theta_poly_lin = Linear_GradDesc(X_ply, y, learning_rate=0.0002, n_iterations=3000) # fit (수제)
Plot(X_ply, y, theta_poly_lin) 
```


    
![png](output_25_0.png)
    



```python
def EarlyStop_SGD(X_train, y_train, X_dev, y_dev, n_iterations=1000): # 학습 조기종료 구현, "볼록함수"인 val_error가 최소일 때 최적
    poly_scaler = Pipeline([ # 데이터 전처리 파이프라인
        ("poly_features", PolynomialFeatures(degree=90, include_bias=False)) # 고차식 형태 생성
        ,("std_scaler", StandardScaler()) # 데이터 분포 처리
    ])
    X_train_poly_scaled = poly_scaler.fit_transform(X_train)
    X_dev_poly_scaled = poly_scaler.fit_transform(X_dev)
    
    sgd_reg = SGDRegressor(max_iter=1, tol=-np.infty, warm_start=True) # SGD의 단일 iteration 수행해줌 (구현 대신 불러옴)
    min_val_error = float("inf") # Initialization
    best_iteration = None 
    best_model = None 
    for i in range(n_iterations):
        sgd_reg.fit(X_train_poly_scaled, y_train) # train-set으로 모델 fit (1 iteration)
        y_val_predict = sgd_reg.predict(X_val_poly_scaled) # dev-set에서 predict
        val_error = mean_squared_error(y_val, y_val_predict) # predict과 y_val 사이 MSE로 val_error 측정
        if val_error < minimum_val_error: # 최솟값(best) 처리
            minimum_val_error = val_error
            best_iteration = i
            best_model = clone(sgd_reg) # 최적의 모델일때 parameter 저장
```

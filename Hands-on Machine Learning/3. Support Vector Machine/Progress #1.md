```python
import numpy as np
from sklearn import datasets
from sklearn.pipeline import Pipeline
from sklearn.preprocessing import StandardScaler
from sklearn.preprocessing import PolynomialFeatures
from sklearn.svm import LinearSVC
from sklearn.svm import SVC
from sklearn.svm import LinearSVR
```


```python
iris = datasets.load_iris() # 데이터 불러오기
X = iris["data"][:,(2,3)] # X는 1차원 데이터
y = (iris["target"]==2).astype(np.float64) # y는 0 또는 1
svm_clf = Pipeline([
    ("scaler", StandardScaler()), # 데이터의 스케일이 SVM에 큰 영향을 미치므로 필수
    ("svm_clf", LinearSVC(C=1, loss="hinge")), # 힌지손실 사용하는 다항 SVM Classifier 모델
])
```


```python
svm_clf.fit(X,y) # fit - 적당한 정확도 안에서 margin이 최대가 되는 결정경계 찾기
svm_clf.predict([[5.5, 1.7]]) # predict(영역을 경계로 가르는 것이기 때문에 확률은 없음)
```




    array([1.])




```python
X, y = datasets.make_moons(n_samples=200, noise=0.15) # 새로운 데이터셋 생성, X는 2차원
polynomial_svm_clf = Pipeline([
    ("poly_features", PolynomialFeatures(degree=3)), # x1, x2에 대한 3차식 제공
    ("scaler", StandardScaler()), # 데이터 스케일링
    ("svm_clf", SVC(C=10, loss="hinge")), # 힌지손실 사용하는 다항 SVM Classifier 모델
])
```


```python
rbf_kernel_svm_clf = Pipeline([ # RBF = Radial Basis Function - 가까울수록 1에 수렴, 멀수록 0에 수렴하는 값
    ("scaler", StandardScaler()), # 데이터 스케일링
    ("svm_clf", SVC(kernel="rbf", gamma=5, C=0.001)), # 각 데이터의 RBF를 특성으로 대체한 Gaussian-RBF SVM Classifier 모델
])
```


```python
svm_reg = LinearSVR(epsilon=1.5) # 분류 대신 회귀 - SVM Regression 모델
```

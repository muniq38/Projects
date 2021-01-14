function [J, grad] = costFunctionReg(theta, X, y, lambda)
%COSTFUNCTIONREG Compute cost and gradient for logistic regression with regularization
%   J = COSTFUNCTIONREG(theta, X, y, lambda) computes the cost of using
%   theta as the parameter for regularized logistic regression and the
%   gradient of the cost w.r.t. to the parameters. 

% Initialize some useful values
m = length(y); % number of training examples

% You need to return the following variables correctly 
J = 0;
grad = zeros(size(theta));
% y m*1, theta n*1, X m*n
% ====================== YOUR CODE HERE ======================
% Instructions: Compute the cost of a particular choice of theta.
%               You should set J to the cost.
%               Compute the partial derivatives and set grad to the partial
%               derivatives of the cost w.r.t. each parameter in theta

n = size(theta);
J -= (y')*log(sigmoid(X*theta)) + (1-y')*log(1-sigmoid(X*theta));
J += lambda*sum(theta(2:n).^2)/2;
J /= m;
% 핵심 포인트 : theta(0)는 regularizate 시키면 안됨!
for i=1:n
  grad(i) = (sigmoid(X*theta)-y)'*X(:,i)/m;
endfor
grad(2:n) += lambda*theta(2:n)/m;

% =============================================================

end

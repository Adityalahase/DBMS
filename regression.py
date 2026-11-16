# PR6: Linear and Polynomial Regression
# Algorithm:
# 1. Load the California Housing dataset.
# 2. Split data into training and testing sets.
# 3. Train the Linear Regression model.
# 4. Train the Polynomial Regression model.
# 5. Predict house prices.
# 6. Compare model performance using MSE, MAE and R2 score.
# 7. Plot actual and predicted values.

import matplotlib.pyplot as plt
from sklearn.datasets import fetch_california_housing
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.preprocessing import PolynomialFeatures
from sklearn.pipeline import make_pipeline
from sklearn.metrics import mean_squared_error, mean_absolute_error, r2_score

data = fetch_california_housing()

X = data.data
y = data.target

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)

linear_model = LinearRegression()
linear_model.fit(X_train, y_train)
linear_pred = linear_model.predict(X_test)

polynomial_model = make_pipeline(
    PolynomialFeatures(degree=2),
    LinearRegression()
)

polynomial_model.fit(X_train, y_train)
polynomial_pred = polynomial_model.predict(X_test)

print("Linear Regression")
print("MSE:", mean_squared_error(y_test, linear_pred))
print("MAE:", mean_absolute_error(y_test, linear_pred))
print("R2 Score:", r2_score(y_test, linear_pred))

print("\nPolynomial Regression")
print("MSE:", mean_squared_error(y_test, polynomial_pred))
print("MAE:", mean_absolute_error(y_test, polynomial_pred))
print("R2 Score:", r2_score(y_test, polynomial_pred))

plt.scatter(y_test, linear_pred, label="Linear")
plt.scatter(y_test, polynomial_pred, label="Polynomial")
plt.xlabel("Actual House Value")
plt.ylabel("Predicted House Value")
plt.title("Regression Comparison")
plt.legend()
plt.show()
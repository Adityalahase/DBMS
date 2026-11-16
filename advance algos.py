
# PR11: Advanced Machine Learning and Model Optimization

# Algorithm:
# 1. Load the Wine dataset.
# 2. Split the dataset into training and testing sets.
# 3. Train SVM, Random Forest and AdaBoost models.
# 4. Calculate accuracy before optimization.
# 5. Perform cross-validation and Grid Search.
# 6. Calculate accuracy after optimization.
# 7. Compare model performance.

from sklearn.datasets import load_wine
from sklearn.model_selection import train_test_split, GridSearchCV, cross_val_score
from sklearn.preprocessing import StandardScaler
from sklearn.pipeline import make_pipeline
from sklearn.svm import SVC
from sklearn.ensemble import RandomForestClassifier, AdaBoostClassifier
from sklearn.metrics import accuracy_score

# Load Dataset
data = load_wine()
X = data.data
y = data.target

# Train-Test Split
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42, stratify=y
)

# Models and Parameters
models = [
    make_pipeline(StandardScaler(), SVC()),
    RandomForestClassifier(random_state=42),
    AdaBoostClassifier(random_state=42)
]

parameters = [
    {"svc__C": [1, 10], "svc__kernel": ["linear", "rbf"]},
    {"n_estimators": [50, 100], "max_depth": [None, 5]},
    {"n_estimators": [50, 100], "learning_rate": [0.5, 1.0]}
]

names = ["SVM", "Random Forest", "AdaBoost"]
before = []
after = []

# Train, Evaluate and Optimize Models
for i in range(3):
    model = models[i]
    model.fit(X_train, y_train)
    pred = model.predict(X_test)

    acc = accuracy_score(y_test, pred)
    before.append(acc)

    print("\n", names[i])
    print("Accuracy Before Optimization:", acc)

    # Cross Validation
    scores = cross_val_score(model, X_train, y_train, cv=5)
    print("Cross Validation Accuracy:", scores.mean())

    # Grid Search
    grid = GridSearchCV(
        model, parameters[i], cv=5, scoring="accuracy"
    )
    grid.fit(X_train, y_train)

    best_model = grid.best_estimator_
    pred = best_model.predict(X_test)

    acc = accuracy_score(y_test, pred)
    after.append(acc)

    print("Best Parameters:", grid.best_params_)
    print("Accuracy After Optimization:", acc)

# Model Comparison
print("\nModel Comparison")
print("-" * 60)
print(f"{'Model':<20}{'Before':<15}{'After':<15}")

for i in range(3):
    print(f"{names[i]:<20}{before[i]:<15.4f}{after[i]:<15.4f}")

print("\nPR11 Completed Successfully!")
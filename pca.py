
# PR10: Dimensionality Reduction using PCA

# Algorithm:
# 1. Load the Wine dataset.
# 2. Split data into training and testing sets.
# 3. Standardize the features.
# 4. Apply PCA to reduce the number of features.
# 5. Train Logistic Regression before and after PCA.
# 6. Compare accuracy and visualize the results.

import matplotlib.pyplot as plt
from sklearn.datasets import load_wine
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.decomposition import PCA
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score

# Load Dataset
data = load_wine()
X = data.data
y = data.target

print("Dataset Shape:", X.shape)

# Train-Test Split
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42, stratify=y
)

# Standardize Features
scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

# Logistic Regression Before PCA
model1 = LogisticRegression(max_iter=5000)
model1.fit(X_train, y_train)
pred1 = model1.predict(X_test)

acc1 = accuracy_score(y_test, pred1)
print("\nAccuracy before PCA:", acc1)

# Apply PCA
pca = PCA(n_components=2)
X_train_pca = pca.fit_transform(X_train)
X_test_pca = pca.transform(X_test)

# Logistic Regression After PCA
model2 = LogisticRegression(max_iter=5000)
model2.fit(X_train_pca, y_train)
pred2 = model2.predict(X_test_pca)

acc2 = accuracy_score(y_test, pred2)
print("Accuracy after PCA:", acc2)

print("Features before PCA:", X_train.shape[1])
print("Features after PCA:", X_train_pca.shape[1])

print("Explained Variance Ratio:", pca.explained_variance_ratio_)
print("Total Explained Variance:", sum(pca.explained_variance_ratio_))

# PCA Visualization
plt.scatter(X_train_pca[:, 0], X_train_pca[:, 1], c=y_train)
plt.xlabel("Principal Component 1")
plt.ylabel("Principal Component 2")
plt.title("Wine Dataset using PCA")
plt.show()

# Explained Variance Graph
pca_full = PCA()
pca_full.fit(X_train)

plt.plot(
    range(1, len(pca_full.explained_variance_ratio_) + 1),
    pca_full.explained_variance_ratio_,
    marker="o"
)
plt.xlabel("Principal Component")
plt.ylabel("Explained Variance Ratio")
plt.title("PCA Explained Variance")
plt.show()

# Impact on Classification Performance
print("\nImpact on Classification Performance:")
print("Accuracy before PCA:", acc1)
print("Accuracy after PCA:", acc2)

if acc2 > acc1:
    print("PCA improved classification accuracy.")
elif acc2 < acc1:
    print("PCA reduced classification accuracy.")
else:
    print("PCA did not change classification accuracy.")

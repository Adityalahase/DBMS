
# PR9: K-Means and Hierarchical Clustering

# Algorithm:
# 1. Load the Iris dataset.
# 2. Scale the features.
# 3. Use the Elbow Method to find optimal clusters.
# 4. Apply K-Means clustering.
# 5. Use a Dendrogram for Hierarchical clustering.
# 6. Display cluster counts.
# 7. Visualize the clusters.

import matplotlib.pyplot as plt
from sklearn.datasets import load_iris
from sklearn.preprocessing import StandardScaler
from sklearn.cluster import KMeans, AgglomerativeClustering
from scipy.cluster.hierarchy import dendrogram, linkage

# Load Dataset
data = load_iris()
X = data.data

# Scale Features
scaler = StandardScaler()
X = scaler.fit_transform(X)

# Elbow Method
wcss = []

for k in range(1, 11):
    kmeans = KMeans(n_clusters=k, random_state=42, n_init=10)
    kmeans.fit(X)
    wcss.append(kmeans.inertia_)

plt.plot(range(1, 11), wcss, marker="o")
plt.title("Elbow Method")
plt.xlabel("Number of Clusters")
plt.ylabel("WCSS")
plt.show()

# K-Means Clustering
kmeans = KMeans(n_clusters=3, random_state=42, n_init=10)
kmeans_labels = kmeans.fit_predict(X)

print("K-Means Cluster Counts:")
for i in range(3):
    print("Cluster", i, ":", list(kmeans_labels).count(i))

# Hierarchical Clustering Dendrogram
Z = linkage(X, method="ward")

plt.figure(figsize=(10, 5))
dendrogram(Z, truncate_mode="lastp", p=30)
plt.title("Hierarchical Clustering Dendrogram")
plt.xlabel("Data Points / Merged Clusters")
plt.ylabel("Distance")
plt.show()

# Hierarchical Clustering
hierarchical = AgglomerativeClustering(n_clusters=3)
hierarchical_labels = hierarchical.fit_predict(X)

print("\nHierarchical Cluster Counts:")
for i in range(3):
    print("Cluster", i, ":", list(hierarchical_labels).count(i))

# Visualize K-Means Clusters
plt.scatter(X[:, 0], X[:, 1], c=kmeans_labels, cmap="viridis")
plt.title("K-Means Clustering")
plt.xlabel("Feature 1")
plt.ylabel("Feature 2")
plt.show()

# Visualize Hierarchical Clusters
plt.scatter(X[:, 0], X[:, 1], c=hierarchical_labels, cmap="viridis")
plt.title("Hierarchical Clustering")
plt.xlabel("Feature 1")
plt.ylabel("Feature 2")
plt.show()

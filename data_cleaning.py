
# PR5: Data Preprocessing and Exploratory Data Analysis

# Algorithm:
# 1. Load the dataset.
# 2. Display and understand the data.
# 3. Remove duplicate rows.
# 4. Handle missing values.
# 5. Analyze the target column.
# 6. Split data into training and testing sets.
# 7. Scale the features.
# 8. Display statistics and graphs.

import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler

# Load Dataset
df = pd.read_csv("heart.csv")

# from sklearn.datasets import fetch_california_housing
# from sklearn.model_selection import train_test_split
# from sklearn.preprocessing import StandardScaler

# Load Dataset
# data = fetch_california_housing(as_frame=True)
# df = data.frame

print(df.head())
print("\nShape:", df.shape)

print("\nColumn Names:")
print(df.columns.tolist())

print("\nDataset Information:")
df.info()

#Statistical analysis
print("\nStatistical Summary:")
print(df.describe())

print("\nTotal Rows:", len(df))

# Remove Duplicates
print("\nNumber of Duplicate Rows:")
print(df.duplicated().sum())

df = df.drop_duplicates()

print("\nShape After Removing Duplicates:")
print(df.shape)

# Handle Missing Values
print("\nMissing Values before:")
print(df.isnull().sum())

for col in df.columns:
    if df[col].isnull().sum() > 0:
        df[col] = df[col].fillna(df[col].median())

print("\nMissing Values after:")
print(df.isnull().sum())

# Analyze Target Column
print("\nTarget Counts:")
print(df["target"].value_counts())

sns.countplot(x="target", data=df)
plt.title("Heart Disease Target Distribution")
plt.show()

# Separate Features and Target
X = df.drop("target", axis=1)
y = df["target"]

# Train-Test Split
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42, stratify=y
)

# Feature Scaling
scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

print("\nTraining Shape:", X_train.shape)
print("Testing Shape:", X_test.shape)

# Display Statistics
print("\nMean:")
print(df.mean())

print("\nMode:")
print(df.mode())

print("\nMedian:")
print(df.median())

print("\nStandard Deviation:")
print(df.std())

# Histograms
df.hist(figsize=(12, 8), bins=15)
plt.tight_layout()
plt.show()

# Boxplots
sns.boxplot(x=df["age"])
plt.show()

sns.boxplot(x=df["chol"])
plt.show()

print("\nEDA Completed")
# Import necessary libraries
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.svm import SVC
from sklearn.metrics import accuracy_score
from sklearn.decomposition import PCA
import matplotlib.pyplot as plt

# Load the dataset from the CSV file
data = pd.read_csv('preprocessed_multi.csv')

# Assuming the last column contains the target labels
X = data.iloc[:, :-1]  # Features (all columns except the last one)
y = data.iloc[:, -1]   # Target labels (last column)

# Split the dataset into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# # Create an SVC classifier with a radial basis function (RBF) kernel
# classifier = SVC(kernel='rbf', C=1, gamma='scale')

# # Train the classifier on the training data
# classifier.fit(X_train, y_train)

# # Make predictions on the test data
# y_pred = classifier.predict(X_test)

# # Evaluate the accuracy of the classifier
# accuracy = accuracy_score(y_test, y_pred)
# print(f"Accuracy: {accuracy}")

# Apply PCA to reduce dimensionality to 2 components
pca = PCA(n_components=2)
X_train_pca = pca.fit_transform(X_train)
X_test_pca = pca.transform(X_test)

# Create an SVC classifier with a radial basis function (RBF) kernel
classifier = SVC(kernel='rbf', C=1, gamma='scale')

# Train the classifier on the training data
classifier.fit(X_train_pca, y_train)

# Make predictions on the test data
y_pred = classifier.predict(X_test_pca)

# Evaluate the accuracy of the classifier
accuracy = accuracy_score(y_test, y_pred)
print(f"Accuracy: {accuracy}")

# Plot the results in 2D
plt.figure(figsize=(10, 6))
plt.scatter(X_test_pca[:, 0], X_test_pca[:, 1], c=y_test, cmap='viridis', edgecolors='k', s=50, alpha=0.8)
plt.title('2D Visualization of Test Data with SVM Decision Boundaries')
plt.xlabel('Principal Component 1')
plt.ylabel('Principal Component 2')
plt.show()
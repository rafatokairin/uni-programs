import numpy as np
from sklearn.model_selection import KFold
from sklearn.metrics import accuracy_score
from ucimlrepo import fetch_ucirepo
from knn_rafael_tokairin import KNN

# Carregar os dados Iris
iris = fetch_ucirepo(id=53)
X = iris.data.features.to_numpy()
y = iris.data.targets.to_numpy()

# Certifique-se de que os rótulos sejam valores escalares
y = np.array([label[0] if isinstance(label, np.ndarray) else label for label in y])

# Configurar validação cruzada k-fold
k_folds = 5
kf = KFold(n_splits=k_folds, shuffle=True, random_state=1234)

# Inicializar o modelo
k = 5
clf = KNN(k=k)

# Armazenar métricas para cada fold
fold_accuracies = []

for train_index, test_index in kf.split(X):
    # Divisão dos dados
    X_train, X_test = X[train_index], X[test_index]
    y_train, y_test = y[train_index], y[test_index]

    # Treinar o modelo
    clf.fit(X_train, y_train)
    
    # Predições no conjunto de teste
    y_test_pred = clf.predict(X_test)
    
    # Calcular acurácia
    acc = accuracy_score(y_test, y_test_pred)
    fold_accuracies.append(acc)

# Resultados
mean_accuracy = np.mean(fold_accuracies)
std_accuracy = np.std(fold_accuracies)

print(f"Validação cruzada com {k_folds} partições:")
print(f"Acurácia média: {mean_accuracy:.4f}")
print(f"Desvio padrão da acurácia: {std_accuracy:.4f}")

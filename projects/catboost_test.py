import numpy as np
from catboost import Pool, CatBoostRegressor
from sklearn.model_selection import train_test_split
import shap

np.set_printoptions(precision=2, suppress=True)

X,y = shap.datasets.boston()
X_train, X_validation, y_train, y_validation = train_test_split(X, y, train_size = 0.8, random_state=12)

model = CatBoostRegressor(iterations=700,
                            learning_rate=0.001,
                            eval_metric='RMSE',
                            random_seed = 23,
                            silent=True)

model.fit(X_train, y_train, eval_set=(X_validation, y_validation), plot=True)


shap.initjs()
explainer = shap.TreeExplainer(model)
shap_values = explainer.shap_values(X)
shap.force_plot(explainer.expected_value, shap_values[0,:], X.iloc[0,:])
shap.summary_plot(shap_values, X, plot_type="bar")

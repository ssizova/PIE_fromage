import numpy as np
import pandas as pd
# from xgboost import XGBClassifier
import sklearn
from sklearn.metrics import matthews_corrcoef, roc_auc_score
from sklearn.model_selection import cross_val_score, StratifiedKFold
import matplotlib.pyplot as plt
import seaborn as sns
%matplotlib inline

date_chunks = pd.read_csv("C:/Users/Sizov/Downloads/bosch-production-line-performance/train_date.csv", index_col=0, chunksize=100000, dtype=np.float32)
num_chunks = pd.read_csv("C:/Users/Sizov/Downloads/bosch-production-line-performance/train_numeric.csv", index_col=0,
                         usecols=list(range(969)), chunksize=100000, dtype=np.float32)
X = pd.concat([pd.concat([dchunk, nchunk], axis=1).sample(frac=0.05)
               for dchunk, nchunk in zip(date_chunks, num_chunks)])
y = pd.read_csv("C:/Users/Sizov/Downloads/bosch-production-line-performance/train_numeric.csv", index_col=0, usecols=[0,969], dtype=np.float32).loc[X.index].values.ravel()
X = X.values
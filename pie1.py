{
 "cells": [
  {
   "cell_type": "code",
   "execution_count": 13,
   "metadata": {},
   "outputs": [],
   "source": [
    "import numpy as np\n",
    "import pandas as pd\n",
    "# from xgboost import XGBClassifier\n",
    "import sklearn\n",
    "from sklearn.metrics import matthews_corrcoef, roc_auc_score\n",
    "from sklearn.model_selection import cross_val_score, StratifiedKFold\n",
    "import matplotlib.pyplot as plt\n",
    "import seaborn as sns\n",
    "%matplotlib inline"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {},
   "outputs": [],
   "source": [
    "date_chunks = pd.read_csv(\"C:/Users/Sizov/Downloads/bosch-production-line-performance/train_date.csv\", index_col=0, chunksize=100000, dtype=np.float32)\n",
    "num_chunks = pd.read_csv(\"C:/Users/Sizov/Downloads/bosch-production-line-performance/train_numeric.csv\", index_col=0,\n",
    "                         usecols=list(range(969)), chunksize=100000, dtype=np.float32)\n",
    "X = pd.concat([pd.concat([dchunk, nchunk], axis=1).sample(frac=0.05)\n",
    "               for dchunk, nchunk in zip(date_chunks, num_chunks)])\n",
    "y = pd.read_csv(\"C:/Users/Sizov/Downloads/bosch-production-line-performance/train_numeric.csv\", index_col=0, usecols=[0,969], dtype=np.float32).loc[X.index].values.ravel()\n",
    "X = X.values"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {},
   "outputs": [],
   "source": [
    "s"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {},
   "outputs": [],
   "source": []
  }
 ],
 "metadata": {
  "kernelspec": {
   "display_name": "Python 3",
   "language": "python",
   "name": "python3"
  },
  "language_info": {
   "codemirror_mode": {
    "name": "ipython",
    "version": 3
   },
   "file_extension": ".py",
   "mimetype": "text/x-python",
   "name": "python",
   "nbconvert_exporter": "python",
   "pygments_lexer": "ipython3",
   "version": "3.6.10"
  }
 },
 "nbformat": 4,
 "nbformat_minor": 4
}

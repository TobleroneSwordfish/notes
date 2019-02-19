from __future__ import print_function # to avoid issues between Python 2 and 3 printing

import numpy as np
from scipy import stats
from skimage import data, io, color, transform, exposure
from pprint import pprint
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from utilities import load_points_from_file
from utilities import view_data_segments


#%matplotlib inline
# notebook
import matplotlib.pylab as pylab
pylab.rcParams['figure.figsize'] = (32.0, 24.0)
pylab.rcParams['font.size'] = 24

print(load_points_from_file("./train/basic_1.csv"))

def leastSquares(X, Y):
    Y = np.matrix(Y).T
    Xones = np.matrix([np.ones(X.size), X]).T
    ans = np.linalg.inv(Xones.T.dot(Xones)).dot(Xones.T).dot(Y)
    return ans
from __future__ import print_function # to avoid issues between Python 2 and 3 printing

import numpy as np
import sys
import math
from scipy import stats
from skimage import data, io, color, transform, exposure
from pprint import pprint
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from utilities import load_points_from_file
from utilities import view_data_segments

# notebook
import matplotlib.pylab as pylab
pylab.rcParams['figure.figsize'] = (32.0, 24.0)
pylab.rcParams['font.size'] = 24

segmentLength = 20

#does least squares
def leastSquares(X, Y, n):
    Y = np.matrix(Y).T
    XMatrix = np.matrix([nDegree(X, i) for i in range(0, n)]).T
    ans = np.linalg.inv(XMatrix.T.dot(XMatrix)).dot(XMatrix.T).dot(Y)
    return ans


#returns X with every element raised to n, kinda pointless but eh
def nDegree(X, n):
   return [x ** n for x in X]

#evaluates each point in X for the polynomial represented by coefficients
def evalArray(X, coefficients, f):
    return [f(x, coefficients) for x in X]

#evaluates the data point x with a polynomial represented by coefficients
def evalPoly(x, coefficients):
    return sum([c * (x ** i) for i, c in enumerate(coefficients)])

def evalSin(x, coefficients):
    return sum([c * (math.sin(x) ** i) for i, c in enumerate(coefficients)])

def split(array, n):
    if len(array) == n:
        return [array]
    return [array[:n]] + split(array[n:len(array)], n)

#returns the total squared error between the original data points and the estimated ones
def error(X, Y, estY):
    range = abs(max(Y) - min(Y)) * abs(max(X) - min(X))
    return sum([(y - y1) * (y - y1) for y, y1 in zip(Y, estY)])/range

data = load_points_from_file(sys.argv[1])

dataX = split(data[0], segmentLength)
dataY = split(data[1], segmentLength)

def getError(X, Y, n, f):
    poly = leastSquares(X, Y, n)
    evalY = evalArray(X, poly, f)
    return error(X, Y, evalY)

# def getPolynomial(X, Y, lastError, n = 2):
#     poly = leastSquares(X, Y, n)
#     evalY = evalArray(X, poly)
#     e = error(X, Y, evalY)
#     print ("Error at degree {} is {} where the polynomial is {}".format(n - 1, e, poly))
#     if (lastError - e > .006):
#         return getPolynomial(X, Y, e, n + 1)
#     return leastSquares(X, Y, n - 1) #ehhhh, no worries

def getPolynomial(X, Y):
    # straight = leastSquares(X, Y, 1)
    # gay = leastSquares(X, Y, 5)
    thefuck = leastSquares(math.sin(X), Y, 2)
    err1 = getError(X, Y, 1, evalPoly)
    err2 = getError(X, Y, 5, evalPoly)
    err3 = getError([math.sin(x) for x in X], Y, evalSin())
    if ()
        

def truncate(n, decimals=0):
    multiplier = 10 ** decimals
    return int(n * multiplier) / multiplier

def printPoly(coefficients):
    return " + ".join(["{}x^{}".format(truncate(c, 3), i) for i, c in enumerate(coefficients)])
    

# As = [leastSquares(x, y, 3) for x, y in zip(dataX, dataY)]
# As = [getPolynomial(X, Y, getError(X, Y, 1)) for X, Y in zip(dataX, dataY)]

ymxc = 

print([printPoly(c.A1) for c in As])

for i, x in enumerate(dataX):
    plt.plot(x, evalArray(x, As[i].A1))


[plt.scatter(x, y) for x, y in zip(dataX, dataY)]

plt.show()
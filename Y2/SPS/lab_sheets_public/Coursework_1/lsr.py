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
def error(Y, estY):
    return sum([(y - y1) * (y - y1) for y, y1 in zip(Y, estY)]).item(0)

def getError(X, Y, n, f):
    poly = leastSquares(X, Y, n)
    evalY = evalArray(X, poly, f)
    return error(Y, evalY)

def getFunction(X, Y):
    errs = [getError(X, Y, 2, evalPoly), getError(X, Y, 5, evalPoly), getError([math.sin(x) for x in X], Y, 2, evalSin)]
    return evalPoly, leastSquares(X, Y, 5), errs[1]
    if (min(errs) == errs[0]):
        return evalPoly, leastSquares(X, Y, 2), errs[0]
    elif (min(errs) == errs[1]):
        return evalPoly, leastSquares(X, Y, 5), errs[1]
    elif (min(errs) == errs[2]):
        return evalSin, leastSquares([math.sin(x) for x in X], Y, 2), errs[2]

data = load_points_from_file(sys.argv[1])

dataX = split(data[0], segmentLength)
dataY = split(data[1], segmentLength)

As = [getFunction(X, Y) for X, Y in zip(dataX, dataY)]

errorT = sum([x[2] for x in As])
print(errorT)

if (len(sys.argv) > 2 and sys.argv[2] == "--plot"):
    for i, x in enumerate(dataX):
        plt.plot(x, evalArray(x, As[i][1].A1, As[i][0]))

    [plt.scatter(x, y) for x, y in zip(dataX, dataY)]
    plt.show()
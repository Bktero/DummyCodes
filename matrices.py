M = [[j+i*3+1 for j in xrange(0,3)] for i in xrange(0,2)]
print M
#[[1, 2, 3], [4, 5, 6]]

M = [[0 for j in xrange(0,3)] for i in xrange(0,2)]
 
print M
#[[0, 0, 0], [0, 0, 0]]

# On accède à chaque élément ligne i, colonne j comme suit: M[i][j]


# On peut aussi créer une fonction qui fabrique des matrices:
fmat = lambda : [[0 for j in xrange(0,3)] for i in xrange(0,2)]
A = fmat()
B = fmat()
 
print "A=", A, "  B=", B
#A= [[0, 0, 0], [0, 0, 0]]   B= [[0, 0, 0], [0, 0, 0]]



# "numarray" de la bibliothèque numpy
# http://www.scipy.org/PerformancePython#head-a73fa06d3c4f3bda71b3526d30d51c492d8f80df




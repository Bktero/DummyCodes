# -*- coding: utf-8 -*-

import sys
import os
from PyQt4 import QtGui, QtCore
from SubGrid_ui import Ui_SubGrid

def factorielle(n):
    if n <= 1 :
        return 1
    else :        
        return n * factorielle(n-1)


class SubGrid(QtGui.QWidget, Ui_SubGrid):
    def __init__(self, parent=None):
        super(SubGrid, self).__init__(parent)
        self.setupUi(self)
        self.connectSignals()
        self.gridvalues = [ [0,0,0], [0,0,0], [0,0,0] ]
        
    def connectSignals(self):
        pass
        #self.pushButton.clicked.connect( self.isGridCorrect )

    def isGridCorrect(self):
        self.extractValues()
        
        check = 0
        
        # Somme de la grille
        check = sum( self.gridvalues[0] ) + sum( self.gridvalues[1] ) + sum( self.gridvalues[2] )
        
        if check != 45 :
            print "Grille incorrecte (somme)"
            return False
        
        # Produit de la grille
        check = 1
        
        for row in range(0, 3):
            for col in range(0, 3):
                check *= self.gridvalues[row][col]
                
        if check != factorielle(9):
            print "Grille incorrect (produit = {} au lieu de {})".format( check , factorielle(9) )
            return False
            
        # Si on est arrive la, c'est que c'est OK
        print "ok"
        return True
        
    
    def extractValues(self):
        for row in range(0, 3):
            for col in range(0, 3):
                self.gridvalues[row][col] = self.gridLayout.itemAtPosition(row, col).widget().value()
                ''' Attention !
                Pour utiliser la methode itemAtPosition, il faut faire bien attention a la mise en forme
                dans QtDesigner. Il est possible qu'il y ait des cases vides si on a mis les widgets 
                un a un, puis on les a deplacer, etc.
                '''
        
    
    def main(self):
        self.show()
    
if __name__=='__main__':
    app = QtGui.QApplication(sys.argv)
    sudoku = SubGrid()
    sudoku.main()
    app.exec_()
    print( factorielle(4) )
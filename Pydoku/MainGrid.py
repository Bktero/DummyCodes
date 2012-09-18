# -*- coding: utf-8 -*-

import sys
from PyQt4 import QtGui, QtCore
from MainGrid_ui import Ui_MainGrid

class MainGrid(QtGui.QWidget, Ui_MainGrid):
    def __init__(self, parent=None):
        super(MainGrid, self).__init__(parent)
        self.setupUi(self)
        
if __name__=='__main__':
    app = QtGui.QApplication(sys.argv)
    sudoku = MainGrid()
    sudoku.show()
    app.exec_()
    print( factorielle(4) )        
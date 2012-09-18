# -*- coding: utf-8 -*-

from SubGrid_ui import Ui_SubGrid
from PyQt4 import QtGui

class SubGrid(QtGui.QWidget):
    def __init__(self, parent=None):
        QtGui.QWidget.__init__(self, parent)
        self.ui = Ui_SubGrid()
        self.ui.setupUi(self)
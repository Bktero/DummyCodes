# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'MainGrid.ui'
#
# Created: Wed Sep 05 16:50:20 2012
#      by: PyQt4 UI code generator 4.9.1
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    _fromUtf8 = lambda s: s

class Ui_MainGrid(object):
    def setupUi(self, MainGrid):
        MainGrid.setObjectName(_fromUtf8("MainGrid"))
        MainGrid.resize(586, 689)
        self.gridLayout_2 = QtGui.QGridLayout(MainGrid)
        self.gridLayout_2.setObjectName(_fromUtf8("gridLayout_2"))
        self.gridLayout = QtGui.QGridLayout()
        self.gridLayout.setSizeConstraint(QtGui.QLayout.SetNoConstraint)
        self.gridLayout.setSpacing(0)
        self.gridLayout.setObjectName(_fromUtf8("gridLayout"))
        self.widget_4 = SubGrid(MainGrid)
        self.widget_4.setObjectName(_fromUtf8("widget_4"))
        self.gridLayout.addWidget(self.widget_4, 1, 0, 1, 1)
        self.widget_6 = SubGrid(MainGrid)
        self.widget_6.setObjectName(_fromUtf8("widget_6"))
        self.gridLayout.addWidget(self.widget_6, 1, 2, 1, 1)
        self.widget_3 = SubGrid(MainGrid)
        self.widget_3.setObjectName(_fromUtf8("widget_3"))
        self.gridLayout.addWidget(self.widget_3, 0, 2, 1, 1)
        self.widget = SubGrid(MainGrid)
        self.widget.setObjectName(_fromUtf8("widget"))
        self.gridLayout.addWidget(self.widget, 0, 0, 1, 1)
        self.widget_2 = SubGrid(MainGrid)
        self.widget_2.setObjectName(_fromUtf8("widget_2"))
        self.gridLayout.addWidget(self.widget_2, 0, 1, 1, 1)
        self.widget_5 = SubGrid(MainGrid)
        self.widget_5.setObjectName(_fromUtf8("widget_5"))
        self.gridLayout.addWidget(self.widget_5, 1, 1, 1, 1)
        self.widget_7 = SubGrid(MainGrid)
        self.widget_7.setObjectName(_fromUtf8("widget_7"))
        self.gridLayout.addWidget(self.widget_7, 2, 0, 1, 1)
        self.widget_8 = SubGrid(MainGrid)
        self.widget_8.setObjectName(_fromUtf8("widget_8"))
        self.gridLayout.addWidget(self.widget_8, 2, 1, 1, 1)
        self.widget_9 = SubGrid(MainGrid)
        self.widget_9.setObjectName(_fromUtf8("widget_9"))
        self.gridLayout.addWidget(self.widget_9, 2, 2, 1, 1)
        self.gridLayout_2.addLayout(self.gridLayout, 0, 0, 1, 1)

        self.retranslateUi(MainGrid)
        QtCore.QMetaObject.connectSlotsByName(MainGrid)

    def retranslateUi(self, MainGrid):
        MainGrid.setWindowTitle(QtGui.QApplication.translate("MainGrid", "Form", None, QtGui.QApplication.UnicodeUTF8))

from SubGrid import SubGrid

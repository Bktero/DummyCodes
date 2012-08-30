'''
Une application minimaliste qui switche a intervalle de temps regulier entre deux pages Internet.
L'idée de l'application vient de cette discussion :
http://www.developpez.net/forums/d1255957/autres-langages/python-zope/general-python/jongler-entre-onglets-navigateur-web
'''

import sys
from PyQt4 import QtCore, QtGui, QtWebKit

class Browser(QtGui.QTabWidget):
    def __init__(self, parent=None):
        super(Browser, self).__init__(parent)
       
        # Deux pages dans deux onglets
        page1 = QtWebKit.QWebView()
        page1.load(QtCore.QUrl("http://www.developpez.com/"));
        
        page2 = QtWebKit.QWebView()
        page2.load(QtCore.QUrl("http://www.google.com/"));
        
        self.addTab(page1, "Developpez")
        self.addTab(page2, "Google")
        
        # Creation du timer
        self.timer = QtCore.QTimer();
        self.timer.timeout.connect(self.switchTab)
        self.timer.start(3000);
  
    def switchTab(self):
        curIndex = self.currentIndex()
        if curIndex == 0 :
            self.setCurrentIndex(1)
        else :
            self.setCurrentIndex(0)
        
    def main(self):
        self.show()
    
if __name__=='__main__':
    app = QtGui.QApplication(sys.argv)
    nav = Browser()
    nav.main()
    app.exec_()
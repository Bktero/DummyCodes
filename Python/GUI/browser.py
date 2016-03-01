'''
Une application minimaliste qui switche a intervalle de temps regulier entre deux pages Internet.
L'idée de l'application vient de cette discussion :
http://www.developpez.net/forums/d1255957/autres-langages/python-zope/general-python/jongler-entre-onglets-navigateur-web
'''

import sys
from PyQt4 import QtCore, QtGui, QtWebKit

class Browser(QtGui.QMainWindow):
    def __init__(self, parent=None):
        super(Browser, self).__init__(parent)
       
        # Deux pages dans deux onglets comme centralWidget
        page1 = QtWebKit.QWebView()
        page1.load(QtCore.QUrl("http://www.developpez.com/"));
        
        page2 = QtWebKit.QWebView()
        page2.load(QtCore.QUrl("http://www.google.com/"));
        
        self.tabs = QtGui.QTabWidget()        
        self.tabs.addTab(page1, "Developpez")
        self.tabs.addTab(page2, "Google")
        
        self.setCentralWidget( self.tabs )
        
        # Creation du timer
        self.timer = QtCore.QTimer();
        self.timer.timeout.connect(self.switchTab)
        self.timerInterval = 3000
        self.timer.start( self.timerInterval )
        
        # Barre de menus
        # Menu "application"
        menuApp = self.menuBar().addMenu("&Application");
        
        self.actionQuit = QtGui.QAction("&Quitter", self)
        self.actionQuit.triggered.connect(QtGui.qApp.quit) # reference magique a l'application en cours
        menuApp.addAction(self.actionQuit);
        
        # Menu "tabs"
        menuTabs = self.menuBar().addMenu("&Onglets");
        
        self.actionAdd = QtGui.QAction("&Ajouter", self)
        self.actionAdd.triggered.connect(self.addTab)
        menuTabs.addAction(self.actionAdd);
        
        self.actionRemove = QtGui.QAction("&Enlever", self)
        self.actionRemove.triggered.connect(self.removeTab)
        menuTabs.addAction(self.actionRemove);
        
        # Menu "timer"
        menuTimer = self.menuBar().addMenu("&Timer");
        
        self.actionStop = QtGui.QAction("&Stopper", self)
        self.actionStop.triggered.connect(self.stopTimer)
        menuTimer.addAction(self.actionStop);
        
        self.actionRestart = QtGui.QAction("&Relancer", self)
        self.actionRestart.triggered.connect(self.restartTimer)
        menuTimer.addAction(self.actionRestart);
        
        self.actionChangeTimerInterval = QtGui.QAction("&Periodicite", self)
        self.actionChangeTimerInterval.triggered.connect(self.changeTimerInterval)
        menuTimer.addAction(self.actionChangeTimerInterval);        
             
    def changeTimerInterval(self):
        results = QtGui.QInputDialog.getInt(self, "Periodicite du timer", "Periode", self.timerInterval, 1, 2147483647, 100)
        
        if results[1] == True:
            self.timerInterval = int( results[0] )
            self.timer.setInterval( self.timerInterval )
    
    def stopTimer(self):

        self.timer.stop()
    def restartTimer(self):
        self.timer.start( self.timerInterval )
        
    def switchTab(self):
        newindex = self.tabs.currentIndex() + 1
        if newindex >= self.tabs.count() :
            self.tabs.setCurrentIndex(0)
        else :
            self.tabs.setCurrentIndex(newindex)
            
    def addTab(self):
        resultsUrl = QtGui.QInputDialog.getText(self, "Entrer l'URL souhaitee", "URL")
        resultsTitle = QtGui.QInputDialog.getText(self, "Entrer le titre de l'onglet", "Titre")
        
        '''
        Voir comment faire une gestion des URL invalides plus robutes avec :
        http://www.riverbankcomputing.co.uk/static/Docs/PyQt4/html/qnetworkaccessmanager.html
        http://www.riverbankcomputing.co.uk/static/Docs/PyQt4/html/qnetworkreply.html#NetworkError-enum
       '''
       
        if (resultsUrl[1] == True) & (resultsTitle[1] == True):
            page = QtWebKit.QWebView()
            page.load(QtCore.QUrl.fromUserInput( resultsUrl[0] ))
            self.tabs.addTab(page, resultsTitle[0])
           
    def removeTab(self): 
        results = QtGui.QInputDialog.getInt(self, "Numero de l'onglet a retirer", "Numero", 1, 1, self.tabs.count(), 1)
        
        if results[1] == True:
            self.tabs.removeTab(results[0]-1)
            # ne supprime pas le widget mais je presume que le GC de Python le fait rapidement  
        
    def main(self):
        self.show()
    
if __name__=='__main__':
    app = QtGui.QApplication(sys.argv)
    
    nav = Browser()
    nav.setWindowTitle("Monitoring")
    nav.main()
    
    sys.exit( app.exec_() )
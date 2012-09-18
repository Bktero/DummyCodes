'''
Code pour demander a l'utilisateur de choisir de maniere interactive un fichier.
On utilise pour cela le module integre Tkinter.

Il est import de noter que ce module se comporte de facon differente selon si on utilise Python 2 ou Python 3.
http://python.developpez.com/faq/?page=TkinterPrerequis#Tkinter2To3
'''

# Pour Python 2
import Tkinter as tk
import tkFileDialog as tkfiledialog


# Pour Python 3
#import tkinter as tk
#import tkinter.filedialog as tkfiledialog

root = tk.Tk()
root.withdraw()

choice = tkfiledialog.askopenfilename()
print choice
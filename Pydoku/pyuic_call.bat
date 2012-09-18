@echo off
REM Il faut enregistrer sans BOM UTF-8

echo Conversion du fichier UI....
C:\Python27\Lib\site-packages\PyQt4\uic\pyuic.py SubGrid.ui -o SubGrid_ui.py
C:\Python27\Lib\site-packages\PyQt4\uic\pyuic.py MainGrid.ui -o MainGrid_ui.py
echo Fait !
pause
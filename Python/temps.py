#!/usr/bin/python
# -*- coding:Utf-8 -*-

def demande_et_convertir():
    '''
    Cette fonction demande a l'utilisateur de saisir au clavier un nombre de secondes.
    La saisie peut etre une valeur brute (ex : '1053') ou un calcul a evaluer (ex : '(5*  10 +5) * 60) ').
    Elle convertit ce nombre de secondes en une somme d'annees, mois (de 30 jours), jours, minutes et secondes.
    '''
    # Demande du nombre de secondes a convertir
    print "Nombre de secondes ?"
    secondes = input()
    print "secondes equivalent a :"

    # Nombre d'années entières
    annees = secondes/60/60/24/365
    secondes=secondes%(60*60*24*365)

    # Nombre de mois entiers
    mois = secondes/60/60/24/30
    secondes=secondes%(60*60*24*30)

    # Nombre de jours entières
    jours = secondes/60/60/24
    secondes=secondes%(60*60*24)

    # Nombre d'heures entières
    heures = secondes/60/60
    secondes=secondes%(60*60)

    # Nombre de minutes entières
    minutes = secondes/60
    secondes=secondes%(60) # il doit rester quelques secondes

    # Affichage de la duree correspondante
    if annees != 0:
        print annees, "annee(s),"
    if mois != 0:
        print mois, "mois,"
    if jours != 0:
        print jours, "jour(s),"
    if heures != 0:
        print heures, "heure(s),"
    if minutes != 0:
        print minutes, "minute(s),"	
    if secondes !=0:
        print secondes, "seconde(s)"

def strXchars(var, x):
        return str(var).zfill(x)


print "-" * 50

while(1):
    demande_et_convertir()
    print

print "-" * 50
raw_input("Appuyer sur ENTREE pour terminer....")
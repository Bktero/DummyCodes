# -*- coding:Utf-8 -*-

# Chaine a convertir
#raw = '41-12-18-30-30-02-03-74-02-66-41'
raw = raw_input("Suite de codes a 2 chiffres hexadecimaux representant une chaine ?\n")

# Separateur entre les nombres hexadecimaux
separator = raw_input("Separateur entre chaque code ?\n")

# Chaine nettoyee
fullhexa = raw.replace(separator,'')

# Si la chaine est de longueur impaire, le dernier caractere sera mal converti
if( len(fullhexa) % 2 != 0):
    print "Attention ! La chaine n'est pas de longueur paire !"
    
# Convertion caractere par caractere et assemblage
result = []
for i in range(0, len(fullhexa), 2):
    subhexa = fullhexa[i:i+2]
    subint = int(subhexa,16)
    subchar = chr(subint)
    result.append(subchar)
    #print "Hexa", subhexa, "int", subint, "char", subchar
result = ''.join(result)

# Affichage du resultat
print
print fullhexa
print "veut dire"
print result

print
print
raw_input("Appuyer sur ENTREE pour terminer...")
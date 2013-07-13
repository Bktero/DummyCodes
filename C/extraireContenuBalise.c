int main(int argc, char *argv[])
{
    const char * original = "Un <b>Lien</b> Publicitaire sur Google<br><cite>www.google.fr/AdWords</cite><br></li><li><h3><a id=\"an2\"";

    char * debut = strstr(original, "<cite>");
    char * fin = strstr(debut, "</cite>");
    debut = debut + 6;

    printf("Original : %s\n", original);
    printf("Debut : %s\n", debut);
    printf("Fin : %s\n", fin);

    int longueur = fin - debut;
    char * lien = malloc(longueur+1);
    strncpy(lien, debut, longueur);
    lien[longueur] = 0;

    printf("\n\nLien (%d = %d) : %s\n", longueur, strlen(lien), lien);

    return argc;
}
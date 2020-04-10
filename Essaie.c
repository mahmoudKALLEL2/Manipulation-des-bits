/*
 ============================================================================
 Name        : Essaie.c
 Author      : mahmoud kallel
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>


static void modifie_jour(unsigned char *date, unsigned jour)
{
    /* Nous stockons le jour (cinq bits). */
    date[0] |= jour;
}


static void modifie_mois(unsigned char *date, unsigned mois)
{
    /* Nous ajoutons les trois premiers bits du mois après ceux du jour. */
    date[0] |= (mois & 0x07) << 5;
    /* Puis le bit restant dans le second octet. */
    date[1] |= (mois >> 3);
}


static void modifie_annee(unsigned char *date, unsigned annee)
{
    /* Nous ajoutons sept bits de l'année après le dernier bit du mois. */
    date[1] |= (annee & 0x7F) << 1;
    /* Et ensuite les cinq restants. */
    date[2] |= (annee) >> 7;
}


static unsigned calcule_jour(unsigned char *date)
{
    return date[0] & 0x1F;
}


static unsigned calcule_mois(unsigned char *date)
{
    return (date[0] >> 5) | ((date[1] & 0x1) << 3);
}


static unsigned calcule_annee(unsigned char *date)
{
    return (date[1] >> 1) | (date[2] << 7);
}


int
main(void)
{
    unsigned char date[3] = { 0 }; /* Initialisation à zéro. */
    unsigned jour, mois, annee;

    printf("Entrez une date au format jj/mm/aaaa : ");

    if (scanf("%u/%u/%u", &jour, &mois, &annee) != 3) {
        perror("fscanf");
        return EXIT_FAILURE;
    }

    modifie_jour(date, jour);
    modifie_mois(date, mois);
    modifie_annee(date, annee);
    printf("Le %u/%u/%u\n", calcule_jour(date), calcule_mois(date), calcule_annee(date));

    return 0;
}

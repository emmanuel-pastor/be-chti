#ifndef GESTIONDFT_H__
#define GESTIONDFT_H__

// Re�oit Signal64ech : l'adresse d'un tableau de 64 �chantillons d'un signal
// Re�oit k : le rang de la raie qui nous int�resse
// Retourne le module au carr� de la fr�quence normalis�e k du signal
// Valeur de retour au format fractionnaire 10.54 dont seulement les 32bits de poids fort sont retourn�s
int DFT_ModuleAuCarre( short int * Signal64ech, char k);

#endif
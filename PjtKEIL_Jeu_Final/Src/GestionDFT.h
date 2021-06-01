#ifndef GESTIONDFT_H__
#define GESTIONDFT_H__

// Reçoit Signal64ech : l'adresse d'un tableau de 64 échantillons d'un signal
// Reçoit k : le rang de la raie qui nous intéresse
// Retourne le module au carré de la fréquence normalisée k du signal
// Valeur de retour au format fractionnaire 10.54 dont seulement les 32bits de poids fort sont retournés
int DFT_ModuleAuCarre( short int * Signal64ech, char k);

#endif
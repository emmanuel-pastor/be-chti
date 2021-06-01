#ifndef GESTIONSON_H__
#define GESTIONSON_H__

// Emet le son "bruit de verre" via un PWM sur le port PB0
void CallbackSon(void);

// Remets l'Index du son "bruit de verre" à zéro pour qu'il puisse être rejoué
void StartSon(void);

#endif
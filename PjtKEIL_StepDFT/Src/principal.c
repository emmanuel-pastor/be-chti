

#include "DriverJeuLaser.h"
#include "GestionDFT.h"

extern short int LeSignal;
int Resu[64];

int main(void)
{
int i;
// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
CLOCK_Configure();



	

//============================================================================	
	
	
while	(1)
	{
		for (i=0;i<64;i++)
		{
			Resu[i]= DFT_ModuleAuCarre(&LeSignal, i);
		}
	}
}


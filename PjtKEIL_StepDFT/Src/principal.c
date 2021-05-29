

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

// Apr�s ex�cution : le coeur CPU est clock� � 72MHz ainsi que tous les timers
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


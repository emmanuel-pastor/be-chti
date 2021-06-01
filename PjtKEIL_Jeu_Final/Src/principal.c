

#include "DriverJeuLaser.h"
#include "GestionDFT.h"
#include "GestionSon.h"
#include "Affichage_Valise.h"

extern int PeriodeSonMicroSec;

short int dma_buf[64];
int Scores [4] = {0,0,0,0};
int Semaphore [4] = {0,0,0,0};
int Resu [4];

int DFT_ModuleAuCarre(short int * Signal64ech, char k);

void Systick_Callback() {
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	
	// Calcul de la DFT pour les joueurs avec une fréquence de 85kHz à 100 kHz
	for(int i=17; i < 25; i++) {
		Resu[i-17] = DFT_ModuleAuCarre(dma_buf, i);
	}

	// Vérifie si le seuil est dépassé pour cetain joueurs
	// Si dépassé, ajouter un point au joueur concerné
	for (int i=0; i < 4; i++) {
		if(Resu[i] < 0x4000000 && Resu[i] > 0x3d70a ) {
			if(Semaphore[i] == 0) {
				Scores[i] ++;
				StartSon();
			}
			Semaphore[i] = 1;
		} else {
			Semaphore[i] = 0;
		}
	}
}

int main(void)
{
	// ===========================================================================
	// ============= INIT PERIPH (faites qu'une seule fois)  =====================
	// ===========================================================================

	// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
	CLOCK_Configure();

	// Config Systick Timer : Mesure DFT
	Systick_Period_ff(360000);
	Systick_Prio_IT(0, Systick_Callback);
	SysTick_On;
	SysTick_Enable_IT;
		
	// Config archi matériel: Mesure DFT
	Init_TimingADC_ActiveADC_ff(ADC1, 72);
	Single_Channel_ADC(ADC1, 2);
	Init_Conversion_On_Trig_Timer_ff(ADC1, TIM2_CC2, 225);
	Init_ADC1_DMA1(0, dma_buf);
	
	// Config Son
	Timer_1234_Init_ff(TIM4, 72*PeriodeSonMicroSec);
	Active_IT_Debordement_Timer(TIM4, 2, CallbackSon);
	PWM_Init_ff( TIM3, 3, 720);
	GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
	
	// Config Afficheur
	Init_Affichage();
	for (int i=0; i < 4; i++) {
		Prepare_Afficheur(i, 0);
	}
	Prepare_Set_LED(LED_Cible_2);
	Mise_A_Jour_Afficheurs_LED();

	//============================================================================		
	while	(1)
	{
		for(int i=0; i < 7200000; i++) {
			// Delay de 100ms
		}

		// Mise à jour des scores
		for(int j=0; j < 4; j++) {
			Prepare_Afficheur(j+1, Scores[j]);
		}
		Mise_A_Jour_Afficheurs_LED();
	}
}

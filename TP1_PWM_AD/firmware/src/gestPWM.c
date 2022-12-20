/*--------------------------------------------------------*/
// GestPWM.c
/*--------------------------------------------------------*/
//	Description :	Gestion des PWM 
//			        pour TP1 2016-2017
//
//	Auteur 		: 	C. HUBER
//
//	Version		:	V1.1
//	Compilateur	:	XC32 V1.42 + Harmony 1.08
//
/*--------------------------------------------------------*/



#include "GestPWM.h"
<<<<<<< HEAD
#include "bsp.h"
=======
#include "Mc32DriverLcd.h"
#include "Mc32DriverAdc.h"
#include "bsp.h"

S_pwmSettings PWMData;            //Pour les settings
S_ADCResults AdcResult;           //Pour la lecture des ADC
static uint16_t tabMoyenne0 [10]; //Tableau pour moyenne glissante canal 0
static uint16_t tabMoyenne1 [10]; //Tableau pour moyenne glissante canal 1
>>>>>>> 6e08bbfb0856bc323cf27330cc2adf29a99891fb


void GPWM_Initialize(S_pwmSettings *pData)
{
<<<<<<< HEAD
    // Start Timers
    DRV_TMR0_Start();
    DRV_TMR1_Start();
    DRV_TMR2_Start();
    DRV_TMR3_Start();
    // Start Output Compare
    DRV_OC0_Start();
    DRV_OC1_Start();
    // Init les data 
    PWMData.AngleSetting = 20;
    PWMData.SpeedSetting = 20;
    PWMData.absAngle = 20;
    PWMData.absSpeed = 20;
    // Init état du pont en H
    BSP_EnableHbrige();
=======
   // Init les data 
   int i;
   for (i=0 ; i<= 9 ; i++)  //Mettre à 0 les 10 cases
   {
       tabMoyenne0 [i] = 0;
       tabMoyenne1 [i] = 0;
   }
      
   // Init état du pont en H
    
   // lance les timers et OC
    
>>>>>>> 6e08bbfb0856bc323cf27330cc2adf29a99891fb
}

// Obtention vitesse et angle (mise a jour des 4 champs de la structure)
void GPWM_GetSettings(S_pwmSettings *pData)	
{ 
    //Lecture des ADC
    AdcResult = BSP_ReadAllADC();       
      
    //Variables Moyenne glissante
    static uint8_t count = 0;       //Compteur stockage ADC
    int moyenne0 = 0;               //Reception de la val moyenne CH0  SPEED         
    int moyenne1 = 0;               //Reception de la val moyenne CH1  ANGLE
    uint8_t i;                      //Variable boucle for
    
    //Injection val ADC dans le tableaux en fonction du compteur
    tabMoyenne0[count] = AdcResult.Chan0;
    tabMoyenne1[count] = AdcResult.Chan1;
    count ++;                       //Incrémentation du compteur
    
    //Test de la valeur max du compteur
    if (count > VAL_MOYENNE - 1)
    {
        count = 0; //Remise à 0 du compteur
    }
    
    //Calculer la moyenne
    for(i = 0 ; i < VAL_MOYENNE; i++)
    {
        moyenne0 += tabMoyenne0[i];
        moyenne1 += tabMoyenne1[i];
    }
    moyenne0 = moyenne0 / VAL_MOYENNE;
    moyenne1 = moyenne1 / VAL_MOYENNE;
    
    // Conversion 
    pData->absSpeed = (moyenne0 * VAL_MAX_VITESSEABS) / VAL_MAX_ADC - VAL_MAX_VITESSE;
    pData->SpeedSetting = (int8_t)(moyenne0 * VAL_MAX_VITESSEABS) / VAL_MAX_ADC - VAL_MAX_VITESSE;
    pData->absAngle = (moyenne1 * VAL_MAX_ANGLEABS) / VAL_MAX_ADC ;
    pData->AngleSetting = (int8_t) pData->absAngle - VAL_MAX_ANGLE;
}


// Affichage des information en exploitant la structure
void GPWM_DispSettings(S_pwmSettings *pData)
{
    lcd_ClearLine(2);
    lcd_ClearLine(3);
    lcd_ClearLine(4);
    lcd_gotoxy(1,2);
    printf_lcd("SpeedSetting = %3d",pData->SpeedSetting);
    lcd_gotoxy(1,3);
    printf_lcd("absSpeed = %3d",abs(pData->absSpeed));
    lcd_gotoxy(1,4);
    printf_lcd("Angle = %3d",pData->AngleSetting);
}

// Execution PWM et gestion moteur à partir des info dans structure
void GPWM_ExecPWM(S_pwmSettings *pData)
{
<<<<<<< HEAD
    if(pData->SpeedSetting > 0){
        
        // Change the sens of rotation
        AIN1_HBRIDGE_W = 1;  //AIN1 High
        AIN2_HBRIDGE_W = 0;  //AIN2 Low
    }
    else if(pData->SpeedSetting == 0){
        
        // Stop the motor
        AIN1_HBRIDGE_W = 1;  //AIN1 High
        AIN2_HBRIDGE_W = 0;  //AIN2 Low
    }
    else if(pData->SpeedSetting < 0){
        
        // Stop the motor
        AIN1_HBRIDGE_W = 0;  //AIN1 High
        AIN2_HBRIDGE_W = 1;  //AIN2 Low
    }
=======
    //Variables pour OC
    uint16_t nbrPulseOC2 = 0;
    uint16_t nbrPulseOC3  = 0;
    
    //Gestion du sens de rotation du moteur
    if (pData->SpeedSetting == 0)
    {
        //Moteur ne tourne pas
        AIN1_HBRIDGE_W = 0;
        AIN2_HBRIDGE_W = 0;
    }
    else if (pData->SpeedSetting > 0)
    {
        //Moteur tourne a droite
        AIN1_HBRIDGE_W = 0;
        AIN2_HBRIDGE_W = 1;
    }
    else
    {
        //Moteur tourne a gauche
        AIN1_HBRIDGE_W = 1;
        AIN2_HBRIDGE_W = 0;
    }
    
    //
>>>>>>> 6e08bbfb0856bc323cf27330cc2adf29a99891fb
    
}

// Execution PWM software
void GPWM_ExecPWMSoft(S_pwmSettings *pData)
{
    
}



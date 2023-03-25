//#include "stm32f0xx_wwdg.h"
#include "stm32f0xx_iwdg.h"
#include "iwdg.h"

void WDG_Init(void)
{
    if(RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET)
    {   
        RCC_ClearFlag();    
    }
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
    IWDG_SetPrescaler(IWDG_Prescaler_32);
    IWDG_SetReload(4000/32);
    IWDG_ReloadCounter();
    IWDG_Enable();  
}
void Feed_Dog(void)
{
    
    IWDG_ReloadCounter();

}


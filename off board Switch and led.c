#include <stdint.h>
#include "tm4c123gh6pm.h"
void PortD_Init(void);
//void Delay(unsigned long time);
//void PortF_Init(void);
unsigned long SW1,SW2;  // input from PF4,PF0
int main(void){
	//long led;
	PortD_Init();

while(1){
    SW1 = GPIO_PORTD_DATA_R&0x01;     // read PD4 into SW1
    SW2 = GPIO_PORTD_DATA_R&0x02;     // read PD0 into SW2
    //if(SW1&&SW2){                     // both pressed
      //GPIO_PORTD_DATA_R = 0x00;       // LED is blue
    //} else                           
      if(SW1&&(!SW2)){                // just SW1 pressed
        GPIO_PORTD_DATA_R = 0x04;     // LED is red
      } else                        
        if((!SW1)&&SW2){              // just SW2 pressed
          GPIO_PORTD_DATA_R = 0x08;   // LED is green
        }else if((!SW1) && (!SW2))
					{                        // neither switch
          GPIO_PORTD_DATA_R = 0x0C;
					}
          else{
              GPIO_PORTD_DATA_R=0x00;
					}						// LED is off
        }
      }
    
  
void PortD_Init(void)
	{volatile unsigned long delay;
		SYSCTL_RCGC2_R |= 0x08;           // Port D clock
  delay = SYSCTL_RCGC2_R;           // wait 3-5 bus cycles
  GPIO_PORTD_DIR_R |= 0x0C;         // PD3 PD0 output
  GPIO_PORTD_AFSEL_R &= ~0x0F;      // not alternative
  GPIO_PORTD_AMSEL_R &= ~0x0F;      // no analog
  GPIO_PORTD_PCTL_R &= ~0x0000FFFF; // bits for PD3, PD0
  GPIO_PORTD_DEN_R |= 0x0F;         // enable PD3, PD0
		 
			}
	
			
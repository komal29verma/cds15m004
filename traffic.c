#include "PLL.h"
#include "tm4c123gh6pm.h"

void DisableInterrupts(void);// Disable interrupts
void EnableInterrupts(void);// Enable interrupts
void WaitForInterrupt(void);// low power mode
void PortB_Init(void);// start sound output
void PortF_Init(void);
void SysHandler(void);
void SysInit(void);//initialize SysTick timer
void SysLoad(unsigned long period);//Load reload value

int main(void)
{
	int i;
	PLL_Init();
	SysHandler();
PortF_Init();
	PortB_Init();
	SysInit();
	SysLoad(800000);
	

	while(1)
	{
		for(i=0; i<=1080000000; i++){
		
GPIO_PORTB_DATA_R^=0x01;  // PB0-west red ON
GPIO_PORTB_DATA_R^=0x08; // PB3-EAST green ON
GPIO_PORTB_DATA_R&=~0x04; //PB2 WEST GREEN OFF
GPIO_PORTB_DATA_R&=~0x20; //PB5 EAST RED OFF
GPIO_PORTF_DATA_R^=0x02; //PF1 PEDESTRAIN WALK SIGNAL ON
GPIO_PORTF_DATA_R&=~0x08; // PF3-PEDESTRAIN DONT WALK SIGNAL OFF
 SysLoad(400000000);
// SysTick_Wait10ms(16000000);
 GPIO_PORTB_DATA_R&=~0x01;  // PB0-west red OFF
 GPIO_PORTB_DATA_R&=~0x08; // PB3-EAST green OFF
 GPIO_PORTB_DATA_R^=0x02; //PB1 WEST YELLOW ON
 GPIO_PORTB_DATA_R^=0x10; //PB4 east Yellow ON
			GPIO_PORTF_DATA_R&=~0x02; //PF1 PEDESTRAIN WALK SIGNAL OFF
		//	GPIO_PORTF_DATA_R&=~0x08; // PF3-PEDESTRAIN DONT WALK SIGNAL OFF
 SysLoad(80000000);
		GPIO_PORTB_DATA_R&=~0x01;  // PB0-west red OFF
 GPIO_PORTB_DATA_R&=~0x08; // PB3-EAST green OFF
 GPIO_PORTB_DATA_R&=~0x02; //PB1 WEST YELLOW ON
 GPIO_PORTB_DATA_R&=~0x10; //PB4 east Yellow ON
 GPIO_PORTB_DATA_R^=0x04; //PB2 WEST GREEN ON
GPIO_PORTB_DATA_R^=0x20; //PB5 EAST RED ON
GPIO_PORTF_DATA_R^=0x08; // PF3-PEDESTRAIN DONT WALK SIGNAL ON
 SysLoad(520000000);
	}
}

}
void PortB_Init(void){ unsigned long volatile delay;
  /*PORT A or PORTF Inititalisation*/
	SYSCTL_RCGC2_R |= 0x02;      // 1) B E
  delay = SYSCTL_RCGC2_R;      // 2) no need to unlock
	GPIO_PORTB_AMSEL_R &= ~0x3F; // 3) disable analog function on PB5-0
  GPIO_PORTB_PCTL_R &= ~0x00FFFFFF; // 4) enable regular GPIO
  GPIO_PORTB_DIR_R |= 0x3F;    // 5) outputs on PB5-0
  GPIO_PORTB_AFSEL_R &= ~0x3F; // 6) regular function on PB5-0
  GPIO_PORTB_DEN_R |= 0x3F;    // 7) enable digital on PB5-0
}

void PortF_Init(void)
{
	unsigned long volatile delay;
	SYSCTL_RCGC2_R |= 0x20;// clock for Port F
	delay = SYSCTL_RCGC2_R;// wait 3-5 bus cycles 	
	//GPIO_PORTF_LOCK_R = 0x4C4F434B;//unlock GPIOPortF
	//GPIO_PORTF_CR_R = 0x09; // allow changes to PF1
	// only PF0 to be unlocked, other bits can't be
	GPIO_PORTF_AMSEL_R &=~ 0x09;// disable analog
	GPIO_PORTF_PCTL_R &= ~0x0000F0F0;// bits for PF1
	GPIO_PORTF_DIR_R |= 0x09;// PF1 input
	GPIO_PORTF_AFSEL_R &=~ 0x09;//disable alt func
	GPIO_PORTF_DEN_R = 0x1F;// enable digital I/O
}
void SysLoad(unsigned long period)
{
	NVIC_ST_RELOAD_R = period -1;
	NVIC_ST_CURRENT_R = 0;       // any value written to CURRENT clears  
	while((NVIC_ST_CTRL_R&0x00010000)==0){ // wait for count flag 
		}
}
void SysInit(void)
{
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_CURRENT_R = 0;// any write to current clears it
	NVIC_SYS_PRI3_R = NVIC_SYS_PRI3_R&0x00FFFFFF;// priority 0
	NVIC_ST_CTRL_R = 0x00000005;// enable with core clock and interrupts
}
void SysHandler(void)
{
	NVIC_ST_CTRL_R = 0;               // disable SysTick during setup  
	NVIC_ST_CTRL_R = 0x00000005; 
} 


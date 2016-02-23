#include <stdint.h>
#include "tm4c123gh6pm.h"

int
main(void)
{
    volatile uint32_t ui32Loop;

    SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;

    ui32Loop = SYSCTL_RCGC2_R;

    GPIO_PORTF_DIR_R = 0x08;
    GPIO_PORTF_DEN_R = 0x08;

    while(1)
    {
        GPIO_PORTF_DATA_R |= 0x08;

        for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++)
        {
        }

        GPIO_PORTF_DATA_R &= ~(0x08);

        for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++)
        {
        }
    }
}

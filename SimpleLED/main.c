#include "tm4c123gxl.h"

//unsigned int *GPIO_F_port_Control = (unsigned int *)0x400FE608U;         //This pointer saves the address which controls GPIO F port switch on and off
//unsigned int *pinInOutControl = (unsigned int *)0x40025400U;             //This pointer saves the address which controls GPIO F port as an input or output
//unsigned int *Analog_digitalControl = (unsigned int *)0x4002551CU;       //This pointer saves the address which controls GPIO F port as digital or analog
//unsigned int *RGBControl = (unsigned int *)0x400253FCU;                  //This pointer saves the address which controls GPIO F port brighting Red Blue or Green

#define LED_RED  (0x1U << 1)
#define LED_BLUE (0x1U << 2)
#define LED_GREEN (0x1U << 3)

int main()
{
  SYSCTL_RCGCGPIO_R = SYSCTL_RCGCGPIO_R | (0x01U << 5);                  //Turn on clock gating
  SYSCTL_GPIOHBCTL_R = SYSCTL_GPIOHBCTL_R | (0x1U << 5);                 //Enable AHB for port
  GPIO_PORTF_AHB_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN);              //Set RGB all as outputs
  GPIO_PORTF_AHB_DEN_R |= (LED_RED | LED_BLUE | LED_GREEN);              //Set EGB all as digital

  //*pinInOutControl = 0x0EU;
  //*Analog_digitalControl = 0x0EU;
  
  while (1){
    GPIO_PORTF_AHB_DATA_R |= LED_RED;        //Turns Red on
    int counter = 0;
    while (counter < 1000000)
        counter++;
    GPIO_PORTF_AHB_DATA_R = 0x0U;
    counter = 0;
    while (counter < 1000000)
        counter++;
    GPIO_PORTF_AHB_DATA_R |= LED_BLUE;        //Turns Blue and Red On
    counter = 0;
    while (counter < 1000000)
        counter++;
    GPIO_PORTF_AHB_DATA_R = LED_BLUE;        //Turns Blue On
    counter = 0;
    while (counter < 1000000)
        counter++;
    
    GPIO_PORTF_AHB_DATA_R = LED_GREEN;         //Turns Green on
    counter = 0;
    while (counter < 1000000)
        counter++;
  }
  return 0;
}

int *GPIO_F_port_Control = (unsigned int *)0x400FE608U;         //This pointer saves the address which controls GPIO F port switch on and off
int *pinInOutControl = (unsigned int *)0x40025400U;             //This pointer saves the address which controls GPIO F port as an input or output
int *Analog_digitalControl = (unsigned int *)0x4002551CU;       //This pointer saves the address which controls GPIO F port as digital or analog
int *RGBControl = (unsigned int *)0x400253FCU;                  //This pointer saves the address which controls GPIO F port brighting Red Blue or Green

int main()
{
  *GPIO_F_port_Control = 0x20U;
  *pinInOutControl = 0x0EU;
  *Analog_digitalControl = 0x0EU;
  
  while (1){
    *RGBControl = 0x02U;        //Turns Red
    int counter = 0;
    while (counter < 10000000)
        counter++;
    *RGBControl = 0x04U;        //Turns Blue
    counter = 0;
    while (counter < 10000000)
        counter++;
    *RGBControl = 0x8U;         //Turns Green
    counter = 0;
    while (counter < 10000000)
        counter++;
    *RGBControl = 0x0U;         //Turns Off
    counter = 0;
    while (counter < 10000000)
        counter++;
  }
  return 0;
}

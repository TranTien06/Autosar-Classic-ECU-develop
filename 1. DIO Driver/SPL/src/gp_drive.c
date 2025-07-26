#include "gp_drive.h"

void init_GP(unsigned short port , unsigned short pin, unsigned short dir, unsigned short option )
{
volatile unsigned long * CR;
unsigned short tPIN = pin;
unsigned short offset = 0x00;	

if(pin > 7)
	{
	tPIN -= 8;
	offset = 0x01; // offset nhu này là cách nhau 16bit so voi 0x00
	}
if(port == 1)
	{
		RCC_APB2ENR |= 4; //mo clock port A
		CR = (volatile unsigned long * )(&GPIO_A + offset);
	}
else if(port == 2)
	{
		RCC_APB2ENR |= (1<<3); //mo clock port B
		CR = (volatile unsigned long * )(&GPIO_B + offset);
	}
else if(port == 3)
	{
		RCC_APB2ENR |= (1<<4); //mo clock port B
		CR = (volatile unsigned long * )(&GPIO_C + offset);
	}
		*CR &= ~(0xf<<(tPIN)*4); // reset tagert pin 
		*CR |= ((dir << (tPIN)*4)) | ((option<<(tPIN*4+2))) ;
	
}
int R_GP(unsigned short port, unsigned short pin){
	volatile unsigned long * IDR;
	unsigned long offset = 0x02; //0b00000010
	int state;
if(port == 1){
	IDR = (volatile unsigned long * )(&GPIO_A + offset);

}
else if(port == 2){
	IDR = (volatile unsigned long * )(&GPIO_B + offset);

}
else if(port == 3){
	IDR = (volatile unsigned long * )(&GPIO_C + offset);
}

state = ((*IDR & (1<<pin)) >> pin) ;
return state;

}
void W_GP(unsigned short port,unsigned short pin,unsigned short status){

	volatile unsigned long * ODR;
	unsigned long offset = 0x03;  
	int state;
if(port == 1){
	
	ODR = (volatile unsigned long * )(&GPIO_A + offset);

}
else if(port == 2){
	ODR = (volatile unsigned long * )(&GPIO_B + offset);

}
else if(port == 3){

	ODR = (volatile unsigned long * )(&GPIO_C + offset);
}	
 status ? (*ODR |= (1 << pin)) : (*ODR &= ~( 1 << pin ));
		
	

}
void toggle(unsigned short port, unsigned short pin){

	if(R_GP(port,pin)){
			W_GP(port,pin,0);
	
	}
	else{
			W_GP(port,pin,1);
	}

}



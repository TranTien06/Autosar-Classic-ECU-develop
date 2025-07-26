#define RCC_APB2ENR             (*((volatile unsigned long *) 0x40021018))
#define GPIO_A					(*((volatile unsigned long *) 0x40010800))
#define GPIO_B					(*((volatile unsigned long *) 0x40010C00))
#define GPIO_C					(*((volatile unsigned long *) 0x40011000))

#define PA 1
#define PB 2
#define PC 3

#define IN 			0
#define OUT10 	1
#define OUT2	 	2
#define OUT50 	3

#define I_AN 0
#define I_F  1
#define I_PP 2 // ngo vao pull up hay pull down phu thuoc vao viec ghi du lieu cho thanh ghi ODR

#define O_GP_PP 0
#define O_GP_OD	1
#define O_AF_PP 2
#define O_AF_OD 3

#define HIGH 1
#define LOW 0 

void init_GP(unsigned short port , unsigned short pin, unsigned short dir, unsigned short option );

int R_GP(unsigned short port, unsigned short pin);

void W_GP(unsigned short port,unsigned short pin,unsigned short status);

void toggle(unsigned short port, unsigned short pin);
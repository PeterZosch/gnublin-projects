#include <stdio.h>

int main()
{

	unsigned int a = 0x0008;
	unsigned int b = 0x18E7;
	unsigned int b1 = 0x0;
	unsigned int c = 0x0;
	unsigned int d = 0x000818E7;

	b1 = a << 16;	
	c = b + b1;

	printf("\na = %x, b = %x, b1 = %x, c = %x, d = %x\n", a, b, b1, c, d );
	printf("\na = %i, b = %i, b1 = %i, c = %i, d = %i\n", a, b, b1, c, d );

	return 0;

}

#include <stdio.h>

static unsigned int array[][2] = {
	{3001,0},
	{3002,1},
	{3003,2}
};

void main(void){
	printf("sizeof(array) %d\n",sizeof(array));
	printf("sizeof(int) * 2 %d\n",sizeof(int)*2);
	printf("%d\n",sizeof(array)/(2*sizeof(int)));
}

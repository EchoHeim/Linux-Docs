#include <stdio.h>
int main (void)
{
	char i=23,j=10,m;
	float n;

	i=Add(23,19);
	j=Sub(32,15);
	m=Mul(4,20);
	n=Div(50,2);
	i++;
	j+=i;
	printf("i=%d\n",i);
	printf("j=%d\n",j);
	printf("m=%d\n",m);
	printf("n=%f\n",n);
	return 0;
}

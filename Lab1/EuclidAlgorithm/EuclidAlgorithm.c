#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main()
{
    long long a = 1678;
	long long b = 432;

	while (a && b)
	{
		if (a > b)
			a = a - (a/b)*b;
		else
			b = b - (b/a)*a ;
	}

	a = max(a, b);

	printf("%d", a);

}
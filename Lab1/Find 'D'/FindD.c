#include <stdio.h>

int main()
{
	int i = 1, e = 11, d = 0, f = 724500;

	while (1)
	{
		d++;
		if (((e * d) % f) == 1)
		{
			printf("%d",d);
			break;
		}
	}
}
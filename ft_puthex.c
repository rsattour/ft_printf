
#include "ft_printf.h"


static int	ft_printr(size_t num, char *base)
{
	int count = 0;
	if (num < 0)
	{
		count +=ft_putchar('-',0);
		num *= (-1);
		count +=ft_printr(num, base);
	}
	else if (num >= 16)
	{
		count +=ft_printr(num / 16, base);
		count +=ft_printr(num % 16, base);
	}
	else
		count +=ft_putchar(base[num],0);
	return count ;
}

int	ft_puthex(size_t nbr, char *base,t_flag *flag)
{
	int count;

	count = 0;
	count += ft_printr(nbr, base);
	while(flag && flag->dash == 1 && flag->secondnbr-2 > count)
		count+= ft_putchar(' ',0);
	return (count);
}


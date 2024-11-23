/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ader <ader@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:46:22 by risattou          #+#    #+#             */
/*   Updated: 2024/11/23 00:49:32 by ader             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"



void ft_flage(const char **str,t_flag *flag)
{
   int cound;

   cound = 0;
    while(**str == ' ' ||**str == '+' ||**str == '#'  ||**str == '0' || **str == '-' || **str == '.'|| (**str >= 48 && **str <= 57))
    {
	    while ((**str >= 48 && **str <= 57 )&& cound == 0)
	    {
		    flag->firstnbr = flag->firstnbr * 10 + **str - 48;
		    (*str)++;
	    }
	    while ((**str >= 48 && **str <= 57) && cound == 1)
	    {
		    flag->secondnbr = flag->secondnbr * 10 + **str - 48;
		    (*str)++;
	    }
        if(**str == ' ')
            flag->space = 1;
        else if(**str == '+')
            flag->plus = 1;
        else if(**str == '#')
            flag->hash = 1;
        else if(**str == '0')
            flag->zero = 1;
        else if(**str == '.')
        {
            flag->full_stop = 1;
            cound = 1;
        }
        else if(**str == '-')
            flag->dash = 1;
        (*str)++;
    }
    
}
static void ft_reset(t_flag *flag)
{
    flag->dash = 0;
    flag->firstnbr = 0;
    flag->secondnbr = 0;
    flag->space = 0;
    flag->full_stop = 0;
    flag->zero = 0;
    flag->plus = 0;
    flag->hash = 0;
}

int ft_printf(const char *str, ...)
{
    if(write(1,0,0) < 0)
        return (-1);
    va_list args;
    t_flag *flag ;
    flag = malloc(sizeof(t_flag));
    if(!flag)
        return -1;
    int count = 0;
    int putnbr = 0;

    va_start(args, str);
    while(*str)
    {
        if (*str == '%' )
        {
            str++;
            if(*str == ' ' ||*str == '+' ||*str == '#'||*str == '0' || *str == '-' || *str == '.' || (*str >= '0' && *str <= '9'))
                ft_flage(&str,flag);
            if(*str == 'd' || *str == 'i')
            {
                putnbr =ft_putnbr(va_arg(args,int),flag,1);
                while(flag && (flag->dash == 1)&& flag->firstnbr > putnbr)
			        putnbr+= ft_putchar(' ',0);
                count += putnbr;
            }
            else if(*str == 'c')
                count +=ft_putchar(va_arg(args,int),flag);
            else if(*str == 's')
                count +=ft_putstr(va_arg(args,char *),flag);
            else if(*str == 'u')
            {
                putnbr =ft_putunbr(va_arg(args,unsigned int),flag);
                while(flag && (flag->dash == 1)&& flag->firstnbr > putnbr)
			        putnbr+= ft_putchar(' ',0);
                count += putnbr;
            }
            else if(*str == 'x')
            {
                putnbr =ft_putnbr_base(va_arg(args,int),"0123456789abcdef",flag);;
                while(flag && (flag->dash == 1)&& flag->firstnbr > putnbr)
			        putnbr+= ft_putchar(' ',0);
                count += putnbr;
            }        
            else if(*str == 'X')
            {
                putnbr =ft_putnbr_base(va_arg(args, int),"0123456789ABCDEF",flag);
                while(flag && (flag->dash == 1)&& flag->firstnbr > putnbr)
			        putnbr+= ft_putchar(' ',0);
                count += putnbr;
            }
            else if(*str == 'p')
            {
                count +=ft_putstr("0x",0);
                count +=ft_puthex(va_arg(args, size_t),"0123456789abcdef",flag);
            }
            else if(*str == '%')
                count +=ft_putchar(*str,0);
        }
        else
            count +=ft_putchar(*str,0);
        ft_reset(flag);
        str++;
    }
    va_end(args);
    free(flag);
    return count;
}

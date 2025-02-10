/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:01:50 by nrumpfhu          #+#    #+#             */
/*   Updated: 2024/09/29 13:29:56 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

int		ft_putchar(int c);
int		ft_printf(const char *format, ...);
int		ft_printformat(const char format, va_list args);
int		ft_putstr(char *str);
int		ft_countnum(int n);
int		ft_countnum_uns(unsigned int n);
int		ft_putnbr_uns(unsigned int n);
int		ft_putnbr(int n, const char format);
int		convert_dec_hex(unsigned int dec, const char format);
int		puthex(unsigned int dec);
void	convert_ptr_hex(unsigned long dec_a);
int		convert_ptr(void *deco);

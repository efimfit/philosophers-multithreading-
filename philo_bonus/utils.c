#include "philosophers.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*b;
	size_t			i;

	i = 0;
	b = (unsigned char *)s;
	while (i < n)
	{
		b[i] = '\0';
		i++;
	}
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putnbr(long long n)
{
	char	c;

	if (n == -2147483648)
	{
		write(1, "-2147483648", ft_strlen("-2147483648"));
		return ;
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
	{
		c = '0' + n;
		write(1, &c, 1);
	}
}

int	ft_atoi(char *nptr)
{
	int	i;
	int	sign;
	int	pow;

	i = 0;
	sign = 1;
	pow = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
		sign = -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		pow = pow * 10 + (nptr[i] - '0');
		i++;
	}
	return (pow * sign);
}

int	my_error(int n)
{
	if (n == 1)
		write(1, "malloc error\n", ft_strlen("malloc error\n"));
	if (n == 2)
		write(1, "wrong number of arguments\n", ft_strlen("wrong number of " \
													 "arguments\n"));
	if (n == 3)
		write(1, "bad arguments\n", ft_strlen("bad arguments\n"));
	return (1);
}

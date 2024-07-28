#include <stdio.h>
#include <stdlib.h>

void decomporNumero(unsigned long long numero) {
  if (numero == 0) {
    printf("Zero\n");
    return;
  }

  unsigned long long divisor = 1;
  while (numero / divisor > 9) {
    divisor *= 10;
  }

  while (divisor > 0) {
    unsigned long long digito = (numero / divisor) % 10;
    if (divisor == 1) {
      printf("%llu: %llu\n", divisor, digito);
    } else if (divisor == 10) {
      printf("%llu: %llu\n", divisor, digito);
    } else if (divisor == 100) {
      printf("%llu: %llu\n", divisor, digito);
    } else {
      printf("%llu: %llu\n", divisor, digito);
    }
    divisor /= 10;
  }
}

void	break_num(char *str, t_dicionario *dicionario, size_t *g_index)
{
  unsigned long long	*num = 0;
  unsigned long long	result = 0;
  unsigned long long	mod = 0;
  unsigned long long	divisor = 1000000000000000000;


  if (ft_srtlen(*str) <= 19 && *str != '\0')
  {
	*num = *num * 10 + (str - '0');
	str++;
  }
  while (num /divisor == 0)
  {
	divisor /= 1000;
  }
  while (num != 0)
  {
		result = num / divisor;
		ft_print_number(result, dicionario, g_index, num);
		result = divisor;
		ft_print_number(result, dicionario, g_index, num);
		num = num % divisor;

		if ((sizeof(num) / sizeof(num[0])) == 3)
		{
			result = num / 100;
			ft_print_number(result, dicionario, g_index, num);
			result = 100;
			ft_print_number(result, dicionario, g_index, num);
			num = num % 100;

		}
		else if (((sizeof(num) / sizeof(num[0])) == 2) && (num / 10) > 20)
		{
			result = num / 10;
			ft_print_number(result, dicionario, g_index, num);
			result = 10;
			ft_print_number(result, dicionario, g_index, num);
			num = num % 10;
		}
		else if (((sizeof(num) / sizeof(num[0])) == 2) && (num / 10) < 20)
		{
			result = num;
			ft_print_number(result, dicionario, g_index, num);
		}
		else if ((sizeof(num) / sizeof(num[0])) == 1)
		{
			result = num;
			ft_print_number(result, dicionario, g_index, num);
		}
		else
		{
			ft_search(num, dicionario, g_index);
			write(1, dicionario[*g_index].extenso, ft_srtlen(dicionario[*g_index].extenso));
		}
	}
}

void	ft_search(unsigned long long result, t_dicionario *dicionario, size_t *g_index)
{
  while (dicionario[*g_index].numero != result)
	{
	  (*g_index)++;
	}
}

void	ft_print_number(unsigned long long result, t_dicionario *dicionario, size_t *g_index, unsigned long long num)
{
  ft_search(result, dicionario, g_index);
  write(1, dicionario[*g_index].extenso, ft_srtlen(dicionario[*g_index].extenso));
  write(1, " ", 1);
  g_index = 0;
}
{

}


int	ft_srtlen(char *str)
{
  int	i = 0;

  while (str[i] != '\0')
  {
	i++;
  }
  return (i);
}

int main() {
  unsigned long long numero = 987654321; // Exemplo de número para decompor
  decomporNumero(numero);
  return 0;
}

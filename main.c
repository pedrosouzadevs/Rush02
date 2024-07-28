#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    unsigned long long	numero;
    char	extenso[100];
  char	number_ext[100];
} t_dicionario;

void processar_linha(char *linha, t_dicionario *dicionario, size_t *g_index);
unsigned int	ft_strlen(char *str);
void	break_num(char *str, t_dicionario *dicionario, size_t *g_index);
void	ft_print_number(unsigned long long result, t_dicionario *dicionario, size_t *g_index);
void	ft_search(unsigned long long result, t_dicionario *dicionario, size_t *g_index);
void dividir_linha(char *linha, unsigned long long *numero, char *extenso, char *number_ext);
int	ft_intlen(int nbr);

size_t g_index;

int main(void)
{
  int fd;
  ssize_t			bytes_read;
  char			buffer[4098];
  char			*linha;
  t_dicionario	*dicionario;
  char 			*linha_inicio;

  fd = open("/home/pdro/code/pedrosouzadevs/42/rush-02/numbers.dict", O_RDONLY);
  if (fd == -1)
  {
    write(STDOUT_FILENO, "Não foi possível abrir o arquivo\n", 34);
    return (1);
  }
  dicionario = (t_dicionario *)malloc(100 * sizeof(t_dicionario));
  if (dicionario == NULL)
  {
    write(STDOUT_FILENO, "Falha ao alocar memória\n", 25);
    close(fd);
    return (1);
  }
  g_index = 0;
  while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0)
  {
    buffer[bytes_read] = '\0';
    linha = buffer;
    while (*linha != '\0' && g_index < 100)
    {
      linha_inicio = linha;
      while (*linha != '\n' && *linha != '\0')
        linha++;
      if (*linha == '\n')
        *linha++ = '\0';

      processar_linha(linha_inicio, dicionario, &g_index);
    }
  }
  if (bytes_read == -1)
    write(STDOUT_FILENO, "Erro ao ler o arquivo\n", 22);

  close(fd);

  break_num("123456789", dicionario, g_index);

  free(dicionario);
  return (0);
}

void processar_linha(char *linha, t_dicionario *dicionario, size_t *g_index)
{
  char	extenso[100];
  unsigned long long numero;
  char	number_ext[100];

  dividir_linha(linha, &numero, extenso, number_ext);
  dicionario[*g_index].numero = numero;
  int j = 0;
  int	k = 0;
  while (extenso[j] != '\0')
  {
    dicionario[*g_index].extenso[j] = extenso[j];
    j++;
  }
  while (number_ext[k] != '\0')
  {
    dicionario[*g_index].number_ext[k] = number_ext[k];
    k++;
  }
  dicionario[*g_index].extenso[j] = '\0';
  dicionario[*g_index].number_ext[k] = '\0';
  (*g_index)++;
}

void dividir_linha(char *linha, unsigned long long *numero, char *extenso, char *number_ext)
{
  int	i = 0;
  int	k = 0;

  *numero = 0;
  while (linha[i] != ':' && linha[i] != '\0')
  {
    *numero = *numero * 10 + (linha[i] - '0');
    number_ext[k++] = linha[i];
    i++;
  }
  if (linha[i] == ':')
    i++;
  int j = 0;
  while (linha[i] != '\0')
  {
    extenso[j++] = linha[i++];
  }
  extenso[j] = '\0';
}

void	break_num(char *str, t_dicionario *dicionario, size_t *g_index)
{
  unsigned long long	num = 0;
  unsigned long long	num_f = 0;
  unsigned long long	result = 0;
  unsigned long long	divisor = 1000000000000000000;
  int i = 0;


  if (ft_strlen(str) <= 19 && *str != '\0')
  {
	while (str[i] != '\0')
	{
		num = num * 10 + (str[i] - '0');
		i++;
    }
  }
  while (num / divisor == 0)
  {
	  divisor /= 1000;
  }
  while (num != 0)
  {
		result = num / divisor;
		ft_print_number(result, dicionario, g_index);
		result = divisor;
		ft_print_number(result, dicionario, g_index);
		num_f = num % divisor;

		if (ft_intlen(num_f) == 3)
		{
			result = num_f / 100;
			ft_print_number(result, dicionario, g_index);
			result = 100;
			ft_print_number(result, dicionario, g_index);
			num_f = num_f % 100;

		}
		else if (ft_intlen(num_f) == 2 && ((num_f / 10) > 20))
		{
			result = num_f / 10;
			ft_print_number(result, dicionario, g_index);
			result = 10;
			ft_print_number(result, dicionario, g_index);
			num_f = num_f % 10;
		}
		else if (ft_intlen(num_f) == 2 && ((num_f / 10) < 20))
		{
			result = num_f;
			ft_print_number(result, dicionario, g_index);
		}
		else if (ft_intlen(num_f) == 1)
		{
			result = num_f;
			ft_print_number(result, dicionario, g_index);
		}
		else
		{
			ft_search(num_f, dicionario, g_index);
			write(1, dicionario[*g_index].extenso, ft_strlen(dicionario[*g_index].extenso));
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

void	ft_print_number(unsigned long long result, t_dicionario *dicionario, size_t *g_index)
{
  ft_search(result, dicionario, g_index);
  write(1, dicionario[*g_index].extenso, ft_strlen(dicionario[*g_index].extenso));
  write(1, " ", 1);
  *g_index = 0;
}

unsigned int	ft_strlen(char *str)
{
  int	i = 0;

  while (str[i] != '\0')
  {
	i++;
  }
  return (i);
}

int	ft_intlen(int nbr)
{
  int	i = 0;

  while (nbr != 0)
  {
	nbr /= 10;
	i++;
  }
  return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro-hm <pedro-hm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 17:31:44 by pedro-hm          #+#    #+#             */
/*   Updated: 2024/07/28 19:30:59 by pedro-hm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_dicionario
{
	unsigned long long numero;
	char extenso[100];
	char number_ext[100];
} t_dicionario;

size_t g_index;

void	processar_linha(char *linha, t_dicionario *dicionario, size_t *g_index);
int	ft_strlen(char *str);
void	break_num(char *str, t_dicionario *dicionario, size_t *g_index);
void	ft_print_number(unsigned long long result, t_dicionario *dicionario, size_t *g_index);
void	ft_search(unsigned long long result, t_dicionario *dicionario, size_t *g_index);
void	dividir_linha(char *linha, unsigned long long *numero, char *extenso, char *number_ext);
int	ft_intlen(int nbr);
int	ft_atoi(const char *str);




int main(int argc, char *argv[])
{
	int fd;
	ssize_t bytes_read;
	char buffer[4098];
	char *linha;
	t_dicionario *dicionario;
	char *linha_inicio;

	fd = 0;
	if (!argv[1] && argc == 2)
	{
		write(1, "Escreva um número\n", 20);
		return (1);
	}
	else if (!(argv[1] || argv[2]) && argc == 3)
	{
		write(1, "Passe um dicionário e escreva um número\n", 43);
		return (1);
	}

	if (argc == 2)
		fd = open("/nfs/homes/pedro-hm/rush-02/numbers.dict", O_RDONLY);
	else if (argc == 3)
		fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		write(1, "Não foi possível abrir o arquivo\n", 34);
		return (1);
	}
	dicionario = (t_dicionario *)malloc(100 * sizeof(t_dicionario));
	if (dicionario == NULL)
	{
		write(1, "Falha ao alocar memória\n", 25);
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
		write(1, "Erro ao ler o arquivo\n", 22);

	close(fd);
	if (argc == 2)
		break_num(argv[1], dicionario, &g_index);
	if (argc == 3)
		break_num(argv[2], dicionario, &g_index);


	free(dicionario);
	write(1, "\n", 1);
	return (0);
}

void processar_linha(char *linha, t_dicionario *dicionario, size_t *g_index)
{
	char extenso[100];
	unsigned long long numero;
	char number_ext[100];

	dividir_linha(linha, &numero, extenso, number_ext);
	dicionario[*g_index].numero = numero;
	int j = 0;
	int k = 0;
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
	int i = 0;
	int k = 0;

	*numero = 0;
	while (linha[i] != ':' && linha[i] != '\0')
	{
		*numero = *numero * 10 + (linha[i] - '0');
		number_ext[k++] = linha[i];
		i++;
	}
	number_ext[k] = '\0';
	if (linha[i] == ':')
		i++;
	int j = 0;
	while (linha[i] != '\0')
	{
		extenso[j++] = linha[i++];
	}
	extenso[j] = '\0';
}

void break_num(char *str, t_dicionario *dicionario, size_t *g_index)
{
	unsigned long long num_f = 1ULL;
	unsigned long long num = 0ULL;
	unsigned long long result = 0ULL;
	unsigned long long divisor = 1000000000000000000ULL;
	int							i = 0;
	while (str[i] != '\0')
	{
		num = num * 10 + (str[i] - '0');
		i++;
    }
	if (num == 0)
	{
		result = num;
		ft_print_number(result, dicionario, g_index);
		return ;
	}

	while (num / divisor == 0)
	{
		divisor /= 1000;
	}
	while (num != 0)
	{
		result = num / divisor;
		num = num % divisor;
		num_f = result;

		if (ft_intlen(num_f) == 3)
		{
			result = num_f / 100;
			ft_print_number(result, dicionario, g_index);
			result = 100;
			ft_print_number(result, dicionario, g_index);
			num_f = num_f % 100;
		}

		if (num_f < 20)
		{
			if (num_f != 0)
			{
				result = num_f;
				ft_print_number(result, dicionario, g_index);
			}
		}
		else
		{
			result = (num_f / 10) * 10;
			ft_print_number(result, dicionario, g_index);
			num_f = num_f % 10;
			if (num_f != 0)
			{
				result = num_f;
				ft_print_number(result, dicionario, g_index);
			}
		}

		if (divisor != 1)
		{
			result = divisor;
			ft_print_number(result, dicionario, g_index);
			divisor /= 1000;
		}
	}
}

void ft_search(unsigned long long result, t_dicionario *dicionario, size_t *g_index)
{
	*g_index = 0; // Reiniciando g_index antes da busca
	while (*g_index < 100 && dicionario[*g_index].numero != result)
	{
		(*g_index)++;
	}
}

void ft_print_number(unsigned long long result, t_dicionario *dicionario, size_t *g_index)
{
	ft_search(result, dicionario, g_index);
	if (*g_index < 100) // Verificando se o número foi encontrado
	{
		write(1, dicionario[*g_index].extenso, ft_strlen(dicionario[*g_index].extenso));
		// write(1, " ", 1);
	}
}

int ft_strlen(char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int ft_intlen(int nbr)
{
	int i = 0;

	if (nbr == 0)
		return 1;

	while (nbr != 0)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	int	res;

	res = 0;
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t' ||
			*str == '\v' || *str == '\f' || *str == '\r'))
		++str;
	if (*str == '-' || *str == '+')
	{
		write(STDOUT_FILENO, "Escreva um número positivo\n", 20);
		return (0);
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		++str;
	}
	return (res);
}

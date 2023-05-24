#include "../incs/minishell.h"

// Count how commands we will have, first 1D array
int find_commands_nb(char *str, t_Error *error)
{
	int commands;
	int i;

	i = 0;
	commands = 0;
	while (str[i])
	{
		if(str[i] && str[i+1] && str[i] == '>' && str[i+1] == '>')
		{
			commands++;
			i += 2;
		}
		else if(str[i] && str[i + 1] && str[i] == '<' && str[i+1] == '<')
		{
			commands++;
			i += 2;
		}
		else if(str[i] == '|' || str[i] == '>' || str[i] == '<')
		{
			if(i > 0 && (str[i - 1] == '>' || str[i - 1] == '<'))
			{
				error->error_str = "zsh: parse error near `|'\n";
				return (-1);
			}
			i++;
		}
		else
			i++;
	}
	return(commands);
}

// Return every command to run inside a 2D array
char **parse_rdline(char	*str, t_Error *error)
{
	unsigned int string_size;
	unsigned int commands_nb;
	//int i;
	//char **commands;


	string_size = ft_strlen(str);
	if(!string_size)
		return(0);
	commands_nb = find_commands_nb(str, error);
	//printf("@debug - total number of commands = %d\n", commands_nb);
	(void)commands_nb;
	//commands = (char *)malloc(sizeof(char *) * (commands_nb + 1));
	
	// i = 0;
	// while (i < commands_nb)
	// {
	// }
	

	//return(commands);
	return(NULL);
}
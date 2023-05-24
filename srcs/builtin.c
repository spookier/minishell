#include "../incs/minishell.h"


// TO DO: change options[0]
int run_echo(char **str)
{
	int i;
	int flag;

	flag = 0;
	i = 0;
	if(ft_strcmp(str[0], "-n") == 0)
	{
		flag = 1;
		i++;
	}
	while (str[i])
	{
		if((flag == 0 && i != 0) || (flag == 1 && i != 1))
			printf(" ");
		printf("%s", str[i]);
		i++;
	}
	return(flag);
}

int run_command(t_data *data, char *command, char **options)
{
	if(ft_strcmp(command, "echo") == 0)
	{
		if(run_echo(options) == 0)
		{
			printf("\n");
		}
		data->exit = 0;
	}
	return(0);
}
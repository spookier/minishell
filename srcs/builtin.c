#include "../incs/minishell.h"

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

int run_pwd()
{
	char *pwd;

	if((pwd = getcwd(NULL, 0)) == NULL)
	{
		// TO DO: error message
		return(-1);
	}
	printf("%s\n", pwd);
	free(pwd);
	return(0);
}

int run_command(t_data *data, char *command, char **options)
{
	if(ft_strcmp(command, "echo") == 0)
	{
		if(run_echo(options) == 0)
			printf("\n");
		//data->exit = 0;
	}
	else if(ft_strcmp(command, "pwd") == 0)
	{
		run_pwd();
		//data->exit = 0;
	}
	else if(ft_strcmp(command, "cd") == 0)
	{
		if(chdir(options[0]) != 0)
		{
			printf("cd fail\n");
	        return (-1);
		}
		//data->exit = 0;
	}
	else if(ft_strcmp(command, "export") == 0)
	{
		// TO DO: export
		//data->exit = 0;
	}
	else if(ft_strcmp(command, "unset") == 0)
	{
		// TO DO: unset
		//data->exit = 0;
	}
	else if(ft_strcmp(command, "env") == 0)
	{
		// TO DO: env
		//data->exit = 0;
	}
	else if(ft_strcmp(command, "exit") == 0)
	{
		// TO DO: exit
		//data->exit = 0;
	}
	return(0);
}
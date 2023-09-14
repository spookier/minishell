#include "../../incs/minishell.h"

void exit_builtin(t_data *cmd)
{
    int exit_status;
    
    exit_status = 0;
    if (cmd->option[0])
        exit_status = ft_atoi(cmd->option[0]);
    exit(exit_status);
}

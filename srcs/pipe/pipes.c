#include "../../include/minishell.h"

static int     count_pipe (t_cmd *cmd)
{
    int i;

    i = 0;
    while (cmd)
    {
        ++i;
        cmd = cmd->next;
    }
    return (i);
}

void    p_father(t_cmd *cmd)
{
    int i;

    i = 0;
    while (i < (count_pipe(cmd)))
    {
        wait(NULL);
        i++;
    }
}

void     p_child(t_env *envp, t_cmd *cmd)
{
    int     i;
    int     pipes[2];
    pid_t   pid;

    i = -1;
    while (++i < count_pipe(cmd))
    {
        pipe(pipes);
        pid = fork();
        if (pid == 0) 
        {
            if (i != 0)
                dup2(cmd->finalfdin, STDIN_FILENO);
            if ((i + 1) != count_pipe(cmd))
                dup2(pipes[1], cmd->fd_out);
            close(pipes[0]);
            close(pipes[1]);
            dup2(pipes[0], cmd->fd_in);
            dup2(pipes[1], cmd->fd_out);
            //printf("fd_in: %d, fd_out: %d finalfdin:%d fdinaldout: %d\n", cmd->fd_in, cmd->fd_out, cmd->finalfdin, cmd->finalfdout);
            if ((!cmd->infile  || !cmd->outfile))
            {
                if(execve(cmd->bin, cmd->arg, envp->tab) == -1)
                {
                    //printf("2: fd_in: %d, fd_out: %d finalfdin:%d fdinaldout: %d\n", cmd->fd_in, cmd->fd_out, cmd->finalfdin, cmd->finalfdout);
                    ft_exit(envp, cmd);
                }
            }

            exit(0);
        }

        close(pipes[0]);
        close(pipes[1]);
        dup2(pipes[0], cmd->finalfdin);
    }
}

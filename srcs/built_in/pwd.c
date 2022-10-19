/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opassin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 03:21:16 by opassin           #+#    #+#             */
/*   Updated: 2022/10/19 05:59:18 by opassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

/*
 * PWD  		: print Working Directory 
 * Type 		: integer
 * Parametre	: aucun
 * Valeur de retour:  errno en cas d'erreur, zero en cas de succes;
 */
int		pwd(void)
{
	char	buff[PATH_MAX];

	if (getcwd(buff, sizeof(buff)) == NULL)
	{
		printf("error: %s", strerror(errno));
		return (errno);
	}
	else
		printf("%s\n", buff);
	return (0);
}

/*
* update_pwd	: update the value of PWD
* Type			: void
* Parametre		: environnement, chaine de caracteres
* Valeur de retour	: aucune
*/

void	update_pwd(t_env *env, char *path)
{

}


/*
* update_oldpwd	: update the vaelue of OLDPWD
* Type			: void
* Parametre		: chaine de caracteres
* Valeur de retour	: aucune
*/

void	update_oldpwd(t_env *env, char *path)
{
	update_pwd(env, path);
}

/*
 * CD		: Change Directory
 * Type		: integer
 * Parametre	: chaine de caractere (path)
 * Valeur de retour : -1 en cas d'erreur, zero en cas de succes
 */
int		cd(char *path, t_env *env)
{
	if (path && chdir(path) != 0)
	{
		printf("cd: %s", path);
		perror(":");
		return (-1);
	}
	if (path == NULL || path[0] == '-')
	{
		// recuperer le $PWD de l'env
		// mettre le $OLDPWD au $PWD
		// mettre le $PWD au $HOME
		// chdir($HOME)
		// return (0)
		update_cd(env, "OLDPWD");
		update_cd(env, "PWD");
		change_path(path);
	}
	else 
	{
		// on recupere le path
		// mettre le $OLDPWD au $PWD
		// mettre le $PWD au path
		// chdir(path)
		update_cd(env, "OLDPWD");
		update_cd(env, "PWD");
		//change to HOME
	}
	return (0);
}

/*
 * is_n_opt : check les arguments
 * Type        : integer
 * Parametre : chaine de caracteres
 * Valeur de retrour : 0 en cas d'erreur (FALSE), 1 en cas de success (TRUE)
 */
int            is_n_opt(char *str)
{
    int        i;

    i = 0;
    if (str[i] != '-')
      return (0);
    else
    {
        while (str[++i])
        {
            if (str[i] != 'n')
                return (0);
        }
    }
    return (1);
}

/*
 * echo        : write arguments to standard output
 * Type        : integer
 * Parametre : double tableau de caracteres,
 la premiere case etant reserver
 on recoit ++arg en parametre
 * Valeur de retour : 1 en cas d'erreur, 0 en cas de succes
 */
int        echo(char **arg)
{
    int        nflag;

    nflag = 0;
    while (is_n_opt(*(++arg)))// tant que option on boucle
        nflag = 1;
    while (*arg != NULL)
        printf("%s", *arg++);//print la chaine
    if (!nflag)
        printf("\n");
    return (0);
}

int        main(void)
{
	pwd();
    return (0);
}

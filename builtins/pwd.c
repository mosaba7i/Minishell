/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsabah <malsabah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:37:54 by malsabah          #+#    #+#             */
/*   Updated: 2026/02/12 12:58:39 by malsabah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void pwd(void)
{
    char *cwd;
    
    cwd = getcwd(NULL, 0);
    printf("%s\n", cwd);
    free(cwd);
}

// for testing only
/*int main(void)
{
    // cc pwd.c
    pwd();
}*/

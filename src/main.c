/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrusco <bbrusco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 17:50:02 by bbrusco           #+#    #+#             */
/*   Updated: 2022/07/10 17:51:38 by bbrusco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**g_env = NULL;

int main(int argc, char **argv)
{
    char *str;

    if (argc != 1 && argv)
        return (ft_err_print("Error: invalid argument"));
    if (ft_init_env()) //  инициализируем двумерный массив для переменных окружения
        return (ft_err_print("Error: environment variables - not enough memory")); 
    signal(SIGQUIT, SIG_IGN); // игнорируем сигнал выхода
    while (1)
    {
        str = readline(BEGIN(49, 34)"Myshell $ "CLOSE);
        if (str == NULL)
        {
            free(str);
            return (1);
        }
        if (ft_strlen(str) > 0)
            add_history(str);

        if (ft_strncmp("env", str, 3) == 0) //   Проверка структуры переменных окружения
            ft_print_env(g_env);

        //Блок обработки
        free(str);
    }
    ft_free_all();
    return (0);
}

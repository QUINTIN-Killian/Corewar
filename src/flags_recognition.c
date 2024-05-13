/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** args_functions
*/

#include "../include/corewar.h"

int is_a_flag(char **args, int i)
{
    if (my_strcmp(args[i], "-a") == 0 && i + 1 < my_strlen_array(args)
    && my_str_isnum(args[i + 1])) {
        return convert_str_in_int(args[i + 1]) >= 0;
    }
    return 0;
}

int is_n_flag(char **args, int i)
{
    return my_strcmp(args[i], "-n") == 0 && i + 1 < my_strlen_array(args) &&
    my_str_isnum(args[i + 1]);
}

int is_dump_flag(char **args, int i)
{
    return my_strcmp(args[i], "-dump") == 0 && i + 1 < my_strlen_array(args) &&
    my_str_isnum(args[i + 1]);
}

int is_correct_file(char **args, int i)
{
    FILE *fd;

    if (my_strlen(args[i]) < 5 || my_strcmp(&(args[i][my_strlen(args[i]) - 4]),
    ".cor") != 0)
        return 0;
    fd = fopen(args[i], "r");
    if (fd == NULL)
        return 0;
    fclose(fd);
    return 1;
}

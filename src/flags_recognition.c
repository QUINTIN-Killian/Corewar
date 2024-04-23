/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** args_functions
*/

#include "../include/corewar.h"

int is_a_flag(char **args, int i)
{
    int mem;

    if (my_strcmp(args[i], "-a") == 0 && i + 1 < my_strlen_array(args) &&
    my_strncmp(args[i + 1], "0x", 2) == 0 && my_strlen(args[i + 1]) > 2
    && my_str_ishex(&(args[i + 1][2]))) {
        mem = convert_hex_in_int(&(args[i + 1][2]));
        return mem >= 1 && mem <= MEM_SIZE;
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

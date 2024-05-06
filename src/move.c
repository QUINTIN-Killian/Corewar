/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** move
*/

#include "../include/corewar.h"

int move_pc_general(char *coding_byte, int nb_params)
{
    int ans = 0;

    for (int i = 0; i < nb_params; i++) {
        if (my_strncmp(&(coding_byte[i * 2]), "01", 2) == 0) {
            ans++;
            continue;
        }
        if (my_strncmp(&(coding_byte[i * 2]), "10", 2) == 0) {
            ans += 4;
            continue;
        }
        ans += 2;
    }
    return ans;
}

int move_pc_index(char *coding_byte, int nb_params)
{
    int ans = 0;

    for (int i = 0; i < nb_params; i++) {
        if (my_strncmp(&(coding_byte[i * 2]), "01", 2) == 0) {
            ans++;
            continue;
        }
        ans += 2;
    }
    return ans;
}

void set_carry(champion_t *champion, int value)
{
    if (value == 0)
        champion->carry = 0;
    else
        champion->carry = 1;
}

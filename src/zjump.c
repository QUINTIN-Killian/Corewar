/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** zjump
*/

#include "../include/corewar.h"

static void exec_zjmp_forward(champion_t *champion)
{
    int distance = champion->instructions->parameters[0] - 3;
    instructions_t *node = champion->instructions->next;

    while (node != NULL && distance > 0) {
        distance -= node->nb_bytes;
        node = node->next;
    }
    champion->instructions = node;
}

static void exec_zjmp_backward(champion_t *champion)
{
    int distance = 0xffff - champion->instructions->parameters[0] + 1;
    instructions_t *node = champion->instructions->prev;

    while (node != NULL && distance > 0) {
        distance -= node->nb_bytes;
        node = node->prev;
    }
    champion->instructions = node;
}

void exec_zjmp(champion_t *champion)
{
    int distance;

    if (!champion->carry || champion->instructions->parameters[0] == 0)
        return;
    champion->PC = champion->PC + champion->instructions->parameters[0] %
    IDX_MOD;
    if (champion->instructions->parameters[0] <= 0xffff / 2) 
        return exec_zjmp_forward(champion);
    exec_zjmp_backward(champion);
}

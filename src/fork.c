/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** fork
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/corewar.h"

void exec_fork(champion_t *champion, corewar_t *corewar)
{
    int value1 = 0;
    int adress = 0;

    value1 = champion->instructions->parameters[0];
    adress = champion->PC + value1 %IDX_MOD;
    duplicate_champion(corewar, champion->id, adress);
    // move_instruction_head(champion);
}

champion_t *find_champion(corewar_t *corewar, int id)
{
    champion_t *current = corewar->champions;

    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void duplicate_champion(corewar_t *corewar, int id, int adress)
{
    champion_t *original = find_champion(corewar, id);
    champion_t *new_champion = (champion_t *)malloc(sizeof(champion_t));

    if (original == NULL) {
        return;
    }
    new_champion->carry = original->carry;
    new_champion->cycle_live = original->cycle_live;
    new_champion->instructions = original->instructions;
    new_champion->is_alive = original->is_alive;
    new_champion->id = original->id;
    new_champion->magic_number = original->magic_number;
    new_champion->timeout = original->timeout;
    new_champion->registers = original->registers;
    new_champion->head = adress;
    new_champion->prog_size = original->prog_size;
    strncpy(new_champion->name, original->name, 128);
    strncpy(new_champion->comment, original->comment, 2048);
    new_champion->next = original->next;
    original->next = new_champion;
}

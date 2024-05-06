/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** ldi
*/

#include "../include/corewar.h"

static int get_param_lldi(corewar_t *corewar, champion_t *champion, int i,
    int *pc)
{
    int res = 0;
    char *bin = convert_int_in_bin(get_memory_cell(
    corewar, champion->PC + 1)->value_int);

    if (my_strncmp(&(bin[i]), "01", 2) == 0) {
        res = champion->registers[get_memory_cell(
        corewar, *pc)->value_int];
        *pc += 1;
    } else {
        res = combine_bytes(2, get_memory_cell(
        corewar, *pc)->value_int, get_memory_cell(
        corewar, *pc + 1)->value_int);
        *pc += 2;
    }
    free(bin);
    return res;
}

void exec_lldi(corewar_t *corewar, champion_t *champion)
{
    int pc = champion->PC + 2;
    int param1 = get_param_lldi(corewar, champion, 0, &pc);
    int param2 = get_param_lldi(corewar, champion, 2, &pc);
    int s = combine_bytes(IND_SIZE,
    get_memory_cell(corewar, champion->PC + param1)->value_int,
    get_memory_cell(corewar, (champion->PC + param1) + 1)->value_int)
    + param2;

    champion->registers[get_memory_cell(corewar, pc)->value_int] =
    combine_bytes(REG_SIZE,
    get_memory_cell(corewar, (champion->PC + s))->value_int,
    get_memory_cell(corewar, (champion->PC + s) + 1)->value_int,
    get_memory_cell(corewar, (champion->PC + s) + 2)->value_int,
    get_memory_cell(corewar, (champion->PC + s) + 3)->value_int);
    champion->PC = cycle_coords(champion->PC + (pc - champion->PC + 1));
    set_carry(champion,
    champion->registers[get_memory_cell(corewar, pc)->value_int]);
    champion->timeout = 50;
}

/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** ldi
*/

#include "../include/corewar.h"

static int get_param_ldi(corewar_t *corewar, champion_t *champion, int i,
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

static void set_ldi(corewar_t *corewar, champion_t *champion, int s, int pc)
{
    champion->registers[get_memory_cell(corewar, pc)->value_int] =
    combine_bytes(REG_SIZE,
    get_memory_cell(corewar, (champion->PC + s % IDX_MOD))->value_int,
    get_memory_cell(corewar, (champion->PC + s % IDX_MOD) + 1)->value_int,
    get_memory_cell(corewar, (champion->PC + s % IDX_MOD) + 2)->value_int,
    get_memory_cell(corewar, (champion->PC + s % IDX_MOD) + 3)->value_int);
}

void exec_ldi(corewar_t *corewar, champion_t *champion)
{
    int pc = champion->PC + 2;
    int param1 = get_param_ldi(corewar, champion, 0, &pc);
    int param2 = get_param_ldi(corewar, champion, 2, &pc);
    int s = param1 + param2;
    char *bin = convert_int_in_bin(get_memory_cell(
    corewar, champion->PC + 1)->value_int);

    if (get_parameter_type(bin, 1) == T_IND)
        s = combine_bytes(IND_SIZE, get_memory_cell(corewar, champion->PC +
        param1 % IDX_MOD)->value_int, get_memory_cell(corewar, (champion->PC +
        param1 % IDX_MOD) + 1)->value_int) + param2;
    free(bin);
    set_ldi(corewar, champion, s, pc);
    champion->PC = cycle_coords(champion->PC + (pc - champion->PC + 1));
    set_carry(champion,
    champion->registers[get_memory_cell(corewar, pc)->value_int]);
    champion->timeout = 25;
}

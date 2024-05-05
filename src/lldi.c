/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** ldi
*/

#include "../include/corewar.h"

void set_carry(champion_t *champion, int new)
{
    if (new == 0) {
        champion->carry = 0;
    } else {
        champion->carry = 1;
    }
}

int set_value(champion_t *champion, int start, int parameter)
{
    int value = 0;

    if (my_strncmp(&(champion->instructions->coding_byte[start]),
    "01", 2) == 0) {
        value =
        champion->registers[champion->instructions->parameters[parameter]];
    } else {
        value = champion->instructions->parameters[parameter];
    }
    return value;
}

int lldi_bin(corewar_t *corewar, cell_t *temp, int adress)
{
    int val = 0;
    int new = 0;

    for (int i = 0; i < REG_SIZE; i++) {
        temp = get_memory_cell(corewar, adress);
        new += convert_hex_in_int(temp->value);
        val = set_val(i);
        if (val != -1)
            new = new << val;
    }
    return new;
}

void exec_lldi(corewar_t *corewar, champion_t *champion)
{
    int value1 = 0;
    int value2 = 0;
    int adress = 0;
    int s = 0;
    int new = 0;
    cell_t *temp;

    value1 = set_value(champion, 0, 0);
    value2 = set_value(champion, 2, 1);
    adress = champion->PC + value1;
    temp = get_memory_cell(corewar, adress);
    s = convert_hex_in_int(temp->value) + value2;
    adress = champion->PC + s;
    new = lldi_bin(corewar, temp, adress);
    champion->registers[champion->instructions->parameters[3]] = new;
    set_carry(champion, new);
    move_instruction_head(champion);
}

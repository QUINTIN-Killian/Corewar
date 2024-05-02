/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** ldi
*/
#include "include/corewar.h"
//PC + value1 % IDX_MOD
// + value2 à la cell de cette adresse
// la somme s'apelle S 
// REG_SIZE lu depuis l'adresse PC + S % IDX_MOD et le copient dans le register (last parameter est le register)

void exec_ldi(corewar_t *corewar, champion_t *champion)
{
    int value1 = 0;
    int value2 = 0;
    int adress = 0;
    int s = 0;
    int new = 0;
    int val = 0;
    cell_t temp;

    if (my_strncmp(&(champion->instructions->coding_byte[0]), "01", 2) == 0) {
        value1 = champion->registers[champion->instructions->parameters[0]];
    } else {
        value1 = champion->instructions->parameters[0];
    }
    if (my_strncmp(&(champion->instructions->coding_byte[2]), "01", 2) == 0) {
        value2 = champion->registers[champion->instructions->parameters[1]];
    } else {
        value2 = champion->instructions->parameters[1];
    }
    adress = champion->PC + value1 % IDX_MOD;
    temp = get_memory_cell(corewar, adress);
    s = temp.value + value2;
    adress = champion->PC + s % IDX_MOD;
    for (int i = 0 ; i < REG_SIZE; i++) {
        temp = get_memory_cell(corewar, adress);
        new += convert_hex_in_int(temp.value);
        val = set_val(i);
        if (val != -1)
            new << val;
    }
    champion->registers[champion->instructions->parameters[3]] = new;
    if (new == 0) {
        champion->carry = 0;
    } else {
        champion->carry = 1;
    }
}
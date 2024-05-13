/*
** EPITECH PROJECT, 2024
** B-CPE-200-LYN-2-1-corewar-elie.chardin
** File description:
** champions_handling
*/

#include "../include/corewar.h"

static int tab_int_len(int *tab)
{
    int ans = 0;

    if (tab == NULL)
        return 0;
    while (tab[ans] != -1)
        ans++;
    return ans;
}

int *realloc_int_plus_one(int *tab)
{
    int *ans;

    if (tab == NULL) {
        ans = malloc(sizeof(int) * 2);
        ans[1] = -1;
        return ans;
    }
    ans = malloc(sizeof(int) * (tab_int_len(tab) + 2));
    ans[tab_int_len(tab) + 1] = -1;
    for (int i = 0; i < tab_int_len(tab); i++)
        ans[i + 1] = tab[i];
    free(tab);
    return ans;
}

int is_nb_already_in_tab(int *tab, int nb)
{
    if (tab == NULL)
        return 0;
    for (int i = 0; tab[i] != -1; i++)
        if (tab[i] == nb)
            return 1;
    return 0;
}

int get_nb_champions(champion_t **champions)
{
    champion_t *node = *champions;
    int *ids = malloc(sizeof(int));
    int ans = 0;

    ids[0] = -1;
    while (node != NULL) {
        if (!is_nb_already_in_tab(ids, node->id)) {
            ids = realloc_int_plus_one(ids);
            ids[0] = node->id;
        }
        node = node->next;
    }
    ans = tab_int_len(ids);
    free(ids);
    return ans;
}

static int *dup_registers(int *registers)
{
    int *new_registers = malloc(REG_SIZE * (REG_NUMBER + 1));

    for (int i = 0; i < REG_NUMBER + 1; i++)
        new_registers[i] = registers[i];
    return new_registers;
}

static void init_clone(champion_t *new_champion, champion_t *node)
{
    new_champion->fd = NULL;
    new_champion->magic_number = node->magic_number;
    my_strncpy(new_champion->name, node->name, 128);
    new_champion->name[128] = '\0';
    new_champion->prog_size = node->prog_size;
    my_strncpy(new_champion->comment, node->comment, 2048);
    new_champion->comment[2048] = '\0';
    new_champion->cycle_live = -1;
    new_champion->carry = node->carry;
    new_champion->PC = node->PC;
    new_champion->head_instruction_ref = NULL;
    new_champion->id = node->id;
    new_champion->instructions = NULL;
    new_champion->is_alive = node->is_alive;
    new_champion->registers = dup_registers(node->registers);
    new_champion->timeout = node->timeout;
    new_champion->next = node->next;
    node->next = new_champion;
}

champion_t *duplicate_champion(champion_t **champions, champion_t *ref)
{
    champion_t *node = *champions;
    champion_t *new_champion;

    while (node != NULL) {
        if (node == ref) {
            new_champion = malloc(sizeof(champion_t));
            init_clone(new_champion, node);
            return new_champion;
        }
        node = node->next;
    }
    return NULL;
}

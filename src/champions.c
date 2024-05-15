/*
** EPITECH PROJECT, 2024
** B-CPE-200-LYN-2-1-corewar-elie.chardin
** File description:
** champions_handling
*/

#include "../include/corewar.h"

static int *create_registers(void)
{
    int *registers = malloc(REG_SIZE * (REG_NUMBER + 1));

    for (int i = 0; i < REG_NUMBER + 1; i++)
        registers[i] = 0;
    return registers;
}

champion_t *create_champion(corewar_t *corewar, char *filename)
{
    champion_t *champion = malloc(sizeof(champion_t));

    corewar->nb_champions++;
    champion->cycle_live = -1;
    champion->carry = 1;
    champion->registers = create_registers();
    champion->magic_number = 0;
    champion->name[0] = '\0';
    champion->prog_size = 0;
    champion->comment[0] = '\0';
    champion->timeout = 0;
    champion->is_alive = 1;
    champion->id = corewar->id;
    champion->head = corewar->start_mem;
    champion->fd = fopen(filename, "r");
    champion->next = corewar->champions;
    champion->instructions = NULL;
    corewar->id = -1;
    corewar->start_mem = -1;
    return champion;
}

static void del_node(champion_t *node)
{
    delete_instructions_list(&node->instructions);
    if (node->registers != NULL)
        free(node->registers);
    if (node->fd != NULL)
        fclose(node->fd);
    free(node);
}

void destroy_champion_node_by_id(champion_t **champions, int id)
{
    champion_t *node = *champions;
    champion_t *tmp;

    if (node == NULL)
        return;
    if (node->id == id) {
        *champions = node->next;
        del_node(node);
        return;
    }
    while (node->next != NULL) {
        if (node->next->id == id) {
            tmp = node->next;
            node->next = node->next->next;
            del_node(tmp);
            return;
        }
        node = node->next;
    }
}

static champion_t *get_next_correct_champion(champion_t *ref)
{
    champion_t *node = ref;

    while (node != NULL && node->id == ref->id)
        node = node->next;
    return node;
}

champion_t *destroy_all_champions_node_by_ref(champion_t **champions,
    champion_t *ref)
{
    champion_t *node = *champions;
    champion_t *ans = get_next_correct_champion(ref);
    champion_t *tmp = NULL;

    while (node != NULL && node->id == ref->id) {
        *champions = node->next;
        del_node(node);
        node = *champions;
    }
    while (node->next != NULL) {
        if (node->next->id == ref->id) {
            tmp = node->next;
            node->next = node->next->next;
            del_node(tmp);
            continue;
        }
        node = node->next;
    }
    return ans;
}

void delete_champions_list(champion_t **champions)
{
    champion_t *current = *champions;
    champion_t *next;

    while (current != NULL) {
        next = current->next;
        del_node(current);
        current = next;
    }
    *champions = NULL;
}

champion_t *rev_champions(champion_t **champions)
{
    champion_t *p = NULL;
    champion_t *c = *champions;
    champion_t *n;

    while (c != NULL) {
        n = c->next;
        c->next = p;
        p = c;
        c = n;
    }
    return p;
}

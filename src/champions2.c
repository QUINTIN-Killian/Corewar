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

static int *realloc_int_plus_one(int *tab)
{
    int *ans;

    if (tab == NULL) {
        ans = malloc(sizeof(int) * 2);
        ans[1] = -1;
        return ans;
    }
    ans = malloc(sizeof(int) * (tab_int_len(tab) + 2));
    ans[tab_int_len(tab) + 1] = -1;
    for (int i = 1; i < tab_int_len(tab) + 2; i++)
        ans[i] = tab[i];
    free(tab);
    return ans;
}

static int is_nb_already_in_tab(int *tab, int nb)
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
    int *ids = NULL;
    int ans = 0;

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

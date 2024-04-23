/*
** EPITECH PROJECT, 2024
** B-CPE-200-LYN-2-1-corewar-elie.chardin
** File description:
** champions_handling
*/

#include "../include/corewar.h"

void change_cellule(champion_t *previous, champion_t *current,
    champion_t **liste)
{
    if (previous == NULL) {
        *liste = current->next;
    } else {
        previous->next = current->next;
    }
}

void delete_by_id(champion_t **liste, int id)
{
    champion_t *current = *liste;
    champion_t *previous = NULL;

    while (current != NULL) {
        if (current->id == id) {
            change_cellule(previous, current, liste);
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

void display_champs_infos(champion_t *list)
{
    while (list != NULL) {
        printf("ID: %d, Timeout: %d, Statut: %d\n",
            list->id, list->timeout, list->is_alive);
        list = list->next;
    }
}

void delete_list(champion_t **liste)
{
    champion_t *current = *liste;
    champion_t *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *liste = NULL;
}

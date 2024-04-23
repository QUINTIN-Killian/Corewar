/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** extraction
*/

#include "../include/corewar.h"

void extract_header(champion_t **champions)
{
    champion_t *node = *champions;

    while (node != NULL) {
        fread(&(node->magic_number), sizeof(unsigned int), 1, node->fd);
        node->magic_number = rev_int(node->magic_number);
        fread(&(node->name), sizeof(char), PROG_NAME_LENGTH, node->fd);
        node->name[PROG_NAME_LENGTH] = '\0';
        fread(&(node->prog_size), sizeof(unsigned long), 1, node->fd);
        node->prog_size = rev_long(node->prog_size);
        fread(&(node->comment), sizeof(char), COMMENT_LENGTH, node->fd);
        node->comment[COMMENT_LENGTH] = '\0';
        node = node->next;
    }
}

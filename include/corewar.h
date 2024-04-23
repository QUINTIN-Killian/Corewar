/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** corewar
*/

#ifndef COREWAR_H_
    #define COREWAR_H_
    #include "my.h"
    #include "op.h"

typedef struct instructions_s {
    char *current_instruction;
    char **instructions;
    int nb_parameters;
} instructions_t;

typedef struct champion_s {
    FILE *fd;
    int id;
    int timeout;
    int is_alive;
    int start_mem;
    int magic_number;
    char name[PROG_NAME_LENGTH + 1];
    long prog_size;
    char command[COMMENT_LENGTH + 1];
    instructions_t *instructions;
    struct champion_s *next;
} champion_t;

void change_cellule(champion_t *previous, champion_t *current,
    champion_t **liste);
void delete_by_id(champion_t **liste, int id);
void display_champs_infos(champion_t *list);
void delete_list(champion_t **liste);

#endif /* !COREWAR_H_ */

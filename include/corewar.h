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
    int mnemonic;
    char *coding_byte;
    char *instruction;
    char **parameters;
    int nb_parameters;
    int nb_bytes;
    struct instructions_s *next;
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
    char comment[COMMENT_LENGTH + 1];
    struct champion_s *next;
    instructions_t *instructions;
} champion_t;

typedef struct corewar_s {
    int id;
    int start_mem;
    int nb_turns;
    int nb_champions;
    champion_t *champions;
} corewar_t;

//endian.c :
unsigned int rev_int(unsigned int nbr);
unsigned long rev_long(unsigned long nbr);

//extraction.c :
void extract_header(champion_t **champions);
int extract_args(int ac, char **av, corewar_t *corewar);

//error_handling.c :
int is_enough_champions(int ac, char **av);
int is_enough_correct_champions(corewar_t *corewar);
int unique_champions(champion_t **champions);

//flag_recognition.c :
int is_a_flag(char **args, int i);
int is_n_flag(char **args, int i);
int is_dump_flag(char **args, int i);
int is_correct_file(char **args, int i);

//functions.c :
int convert_hex_in_int(char *hex);
int get_max_champion_id(champion_t **champions);
int my_str_ishex(char *str);
void give_champions_id(champion_t **champions);
void del_incorrect_magic_number(corewar_t *corewar, champion_t **champions);

//champions.c :
champion_t *create_champion(corewar_t *corewar, char *filename);
void destroy_champion_node_by_id(champion_t **champions, int id);
void display_champs_infos(champion_t **champions);
void delete_list(champion_t **champions);
champion_t *rev_champions(champion_t **champions);

#endif /* !COREWAR_H_ */

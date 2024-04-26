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
    int id;
    int mnemonic;
    char *instruction;
    int nb_cycles;
    char *coding_byte;
    int nb_parameters;
    char **parameters;
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
int extract_args(int ac, char **av, corewar_t *corewar);
void extract_header(champion_t **champions);
void extract_body(champion_t **champions);

//error_handling.c :
int is_enough_champions(int ac, char **av);
int is_enough_correct_champions(corewar_t *corewar);

//flag_recognition.c :
int is_a_flag(char **args, int i);
int is_n_flag(char **args, int i);
int is_dump_flag(char **args, int i);
int is_correct_file(char **args, int i);

//functions.c :
int get_max_champion_id(champion_t **champions);
void set_champions_infos(corewar_t *corewar, champion_t **champions);
void del_incorrect_magic_number(corewar_t *corewar, champion_t **champions);
char *convert_int_in_bin(int nb);

//champions.c :
champion_t *create_champion(corewar_t *corewar, char *filename);
void destroy_champion_node_by_id(champion_t **champions, int id);
void display_champions_infos(champion_t **champions);
void delete_champions_list(champion_t **champions);
champion_t *rev_champions(champion_t **champions);

//instructions.c :
instructions_t *create_instruction(instructions_t *next);
void destroy_instruction_node_by_id(instructions_t **instructions, int id);
void display_instructions_infos(instructions_t **instructions);
void delete_instructions_list(instructions_t **instructions);
instructions_t *rev_instructions(instructions_t **instructions);

//instructions2.c :
int set_instruction(instructions_t *node);

#endif /* !COREWAR_H_ */

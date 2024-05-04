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
    #define PC head

typedef struct cell_s {
    char *value;
    int value_int;
    int id_owner;
} cell_t;

typedef struct instructions_s {
    int id;
    int mnemonic;
    char *instruction;
    int nb_cycles;
    char *coding_byte;
    int nb_parameters;
    int *parameters;
    int nb_bytes;
    struct instructions_s *prev;
    struct instructions_s *next;
} instructions_t;

typedef struct champion_s {
    int carry;
    int cycle_live;
    int *registers;
    FILE *fd;
    int id;
    int timeout;
    int is_alive;
    int head;
    int magic_number;
    char name[PROG_NAME_LENGTH + 1];
    long prog_size;
    char comment[COMMENT_LENGTH + 1];
    struct champion_s *next;
    instructions_t *instructions;
    instructions_t *head_instruction_ref;
} champion_t;

typedef struct corewar_s {
    int id;
    int start_mem;
    int nb_turns;
    int nb_champions;
    int turn_id;
    champion_t *champions;
    cell_t **memory;
} corewar_t;

//writing.c :
void write_instructions_in_memory(corewar_t *corewar, champion_t **champions);

//endian.c :
unsigned short rev_short(unsigned short nbr);
unsigned int rev_int(unsigned int nbr);
unsigned long rev_long(unsigned long nbr);

//extraction.c :
int extract_args(int ac, char **av, corewar_t *corewar);
void extract_header(champion_t **champions);
void extract_body(champion_t **champions);

//parameters_extraction.c :
int get_nb_parameters(char *coding_byte);
void extract_parameters(instructions_t *instruction, FILE *fd);

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
void set_double_linked_list(champion_t **champions);
void move_instruction_head(champion_t *champion);

//main_loop.c :
void main_loop(champion_t **champions, corewar_t *corewar);

//memory.c :
void create_memory(corewar_t *corewar);
void print_memory(corewar_t *corewar);
void destroy_memory(corewar_t *corewar);

//add.c :
void exec_add(champion_t *champion);

//aff.c :
void exec_aff(champion_t *champion);

//and.c :
void exec_and(champion_t *champion);

//instruction_execution.c :
void instruction_execution(corewar_t *corewar, champion_t *champion,
    instructions_t *instruction);

//zjmp.c :
void exec_zjmp(champion_t *champion);

//live.c :
void exec_live(champion_t *champion);

//or.c :
void exec_or(champion_t *champion);

//sub.c :
void exec_sub(champion_t *champion);

//xor.c :
void exec_xor(champion_t *champion);

//st.c :
void exec_st(champion_t *champion, corewar_t *corewar);

//sti.c :
void exec_sti(champion_t *champion, corewar_t *corewar);

//ld.c :
int set_val(int i);
void exec_ld(champion_t *champion, corewar_t *corewar);

//lld.c :
void exec_lld(champion_t *champion, corewar_t *corewar);

//ldi.c :
void exec_ldi(corewar_t *corewar, champion_t *champion);

//lldi.c :
void set_carry(champion_t *champion, int new);
int set_value(champion_t *champion, int start, int parameter);
void exec_lldi(corewar_t *corewar, champion_t *champion);

//conversions.c :
int convert_hex_in_int(char *hex);
char *convert_int_in_bin(int nb);
char *convert_int_in_hex(int nb);
int convert_bin_in_int(char *bin);

// memory_cell.c :
cell_t *create_tmp_cell(int id_owner, int value_int);
cell_t *get_memory_cell(corewar_t *corewar, int coords);
int set_memory_cell(corewar_t *corewar, cell_t *new_cell, int coords,
    int nb_bytes);

#endif /* !COREWAR_H_ */

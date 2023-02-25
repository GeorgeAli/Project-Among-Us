/**************************************************
 *                                                *
 * file: among_us.h                               *
 *                                                *
 *                                                *
 * @Author  Antonios Peris                        *
 * @Version 20-10-2020                            *
 * @email   csdp1196@csd.uoc.gr                   *
 *                                                *
 * @brief   Header file for the needs of cs-240   *
 * project 2020, with the structures and function *
 * prototypes                                     * 
 *                                                *
 **************************************************
 */

#ifndef __AMONG_US_H_
#define __AMONG_US_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/**
 * Structure defining a node of the players double linked list
 * tree
 */
struct Players
{
    int pid;                      /*Player's identifier*/
    int is_alien;                 /*Alien flag*/
    int evidence;                 /*Amount of evidence*/
    struct Players *prev;         /*Pointer to the previous node*/
    struct Players *next;         /*Pointer to the next node*/
    struct Tasks *tasks_head;     /*Pointer to the head of player's task list*/
    struct Tasks *tasks_sentinel; /*Pointer to the sentinel of player's task list*/
};

/**
 * Structure defining a node of the tasks sorted linked list
 */
struct Tasks
{
    int tid;            /*Task's identifier*/
    int difficulty;     /*Task's difficulty*/
    struct Tasks *next; /*Pointer to the next node*/
};

struct Head_GL
{
    int tasks_count[3]; /*Count of tasks*/
    struct Tasks *head; /*Pointer to the head of general list*/
};
struct Head_Completed_Task_Stack
{
    int count;          /*Count of completed tasks*/
    struct Tasks *head; /*Pointer to the top element of the stack*/
};

/* Global variable, pointer to the head of the players list */
struct Players *players_head;

/* Global variable, pointer to the head of the tasks list */
struct Head_GL *tasks_head;

/* Global variable, pointer to the top of the completed task's stack */
struct Head_Completed_Task_Stack *tasks_stack;

int initialize();

int register_player(int pid, int is_alien);

int insert_task(int tid, int difficulty);

int distribute_tasks();

int implement_task(int pid, int difficulty);

int eject_player(int pid);

int witness_eject(int pid, int pid_a, int number_of_witnesses);

int sabbotage(int pid, int number_of_tasks);

int vote(int pid, int vote_evidence);

int give_work();

int Terminate();

int print_players();

int print_tasks();

int print_stack();

int print_double_list();

int free_all(void);

void pushPlayers(Players **head, int pid, int is_alien);

void pushTasks(Head_GL **head, int tid_new, int difficulty_new);

void printPlayerList(Players *node);

void printTaskList(Head_GL *node);

void sort(Tasks **head_ref, Tasks *sentinel, Tasks *new_node);

Tasks *last_element(Tasks **head_ref);

Tasks *Remove(Players *player, Tasks *task);

void push_stack(Head_Completed_Task_Stack **head_ref, Tasks *t);

Tasks *Pop(Head_Completed_Task_Stack *h);

void print_evidence();

#endif /* __AMONG_US_H_ */
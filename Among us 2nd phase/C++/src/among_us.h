/**************************************************
 *                                                *
 * file: among_us.h                               *
 *                                                *
 *                                                *
 * @Author  Skerdi Basha                          *
 * @Version 1-12-2020                             *
 * @email   sbash@csd.uoc.gr                      *
 *                                                *
 * @brief   Header file for the needs of CS-240   *
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
 * Structure defining a node of the players double linked tree
 */
struct Player
{
    int pid;                /*Player's identifier*/
    int is_alien;           /*Alien flag*/
    int evidence;           /*Amount of evidence*/
    struct Player *parrent; /*Pointer to the parent node*/
    struct Player *lc;      /*Pointer to the left child node*/
    struct Player *rc;      /*Pointer to the right child node*/
    struct Task *tasks;     /*Pointer to the head of player's task tree*/
};

/**
 * Structure defining a node of the tasks sorted tree
 */
struct Task
{
    int tid;         /*Task's identifier*/
    int difficulty;  /*Task's difficulty*/
    int lcnt;        /*Node's left child's node counter*/
    struct Task *lc; /*Pointer to the left child node*/
    struct Task *rc; /*Pointer to the right child node*/
};

struct HT_Task
{
    int tid;              /*Task's identifier*/
    int difficulty;       /*Task's difficulty*/
    struct HT_Task *next; /*Pointer to the next node*/
};

struct General_Tasks_HT
{
    int count;              /*Count of tasks*/
    struct HT_Task **tasks; /*General tasks hash table*/
};

struct Completed_Tasks_PQ
{
    int size;              /*Count of completed tasks*/
    struct HT_Task *tasks; /*Completed tasks priority queue*/
};

unsigned int max_tasks_g; /* Max number of tasks */
unsigned int max_tid_g;   /* Max task tid */

/* Primes for your universal hashing implementation */
extern unsigned int primes_g[650];

/* Global variable, pointer to the head of the players tree */
struct Player *players_tree;

/* Global variable, pointer to the head of the tasks tree */
struct General_Tasks_HT general_tasks_ht;

/* Global variable, pointer to the top of the completed task's priority queue */
struct Completed_Tasks_PQ *completed_tasks_pq;

/**
 * @brief Optional function to initialize data structures that 
 *        need initialization
 *
 * @return 1 on success
 *         0 on failure
 */
int initialize();

/**
 * @brief Register Player
 *
 * @param pid The player's id
 *
 * @param is_alien The variable that decides if he is an alien or not
 * @return 1 on success
 *         0 on failure
 */
int register_player(int pid, int is_alien);

/**
 * @brief Insert Task in the general task hash table
 *
 * @param tid The task id
 * 
 * @param difficulty The difficulty of the task
 *
 * @return 1 on success
 *         0 on failure
 */
int insert_task(int tid, int difficulty);

/**
 * @brief Distribute Tasks to the players
 * @return 1 on success
 *         0 on failure
 */
int distribute_tasks();

/**
 * @brief Implement Task
 *
 * @param pid The player's id
 *
 * @param tid The task's tid
 *
 * @return 1 on success
 *         0 on failure
 */
int implement_task(int pid, int tid);

/**
 * @brief Eject Player
 * 
 * @param pid_1 The ejected player's id
 *
 * @param pid_2 The crewmates id
 *
 * @return 1 on success
 *         0 on failure
 */
int eject_player(int pid_1, int pid_2);

/**
 * @brief Witness Eject Player
 *
 * @param pid_1 The ejected player's id
 * 
 * @param pid_2 The crewmate's pid
 *
 * @param pid_a The alien's pid
 * 
 * @param number_of_witnesses The number of witnesses
 *
 * @return 1 on success
 *         0 on failure
 */
int witness_eject(int pid_1, int pid_2, int pid_a, int number_of_witnesses);

/**
 * @brief Sabotage
 *
 * @param number_of_tasks The number of tasks to be sabotaged
 *
 * @param pid The player's id
 * 
 * @return 1 on success
 *         0 on failure
 */
int sabotage(int number_of_tasks, int pid);

/**
 * @brief Vote
 *
 * @param pid_1 The suspicious player's id
 *
 * @param pid_2 The crewmate's pid
 * 
 * @param vote_evidence The vote's evidence
 *
 * @return 1 on success
 *         0 on failure
 */
int vote(int pid_1, int pid_2, int vote_evidence);

/**
 * @brief Give Away Work
 *
 * @param pid_1 The existing crewmate's id
 *
 * @param pid_2 The new crewmate's pid
 *
 * @return 1 on success
 *         0 on failure
 */
int give_work(int pid_1, int pid_2);

/**
 * @brief Terminate
 *
 * @return 1 on success
 *         0 on failure
 */
int Terminate();

/**
 * @brief Print Players
 *
 * @return 1 on success
 *         0 on failure
 */
int print_players();

/**
 * @brief Print Tasks
 *
 * @return 1 on success
 *         0 on failure
 */
int print_tasks();

/**
 * @brief Print Priority Queue
 *
 * @return 1 on success
 *         0 on failure
 */
int print_pq();

/**
 * @brief Print Players & Task tree
 *
 * @return 1 on success
 *         0 on failure
 */
int print_double_tree();

/**
 * @brief Free resources
 *
 * @return 1 on success
 *         0 on failure
 */

int free_all(void);

//My functions
//------------------------------------------------------------------------------------------

Player *Insert_Players(Player *root, int pid, int is_alien);

void print_PT(Player *root);

int HashFunction(int tid);

Task *Insert_Task_to_Player(Task *player_task_tree_root);

void Inorder(Player *players_tree);

Task *TaskProvider();

void print_PN(Player *root, int choice);

void print_PTasks(Task *root);

Player *SearchPT(Player *root, int pid);

Task *DeletePTask(Task *root, int tid);

void fix_lcnt(Task *root, int tid);

int count_nodes(Task *root);

void push_PQ(Task *task_to_push);

Task *pop_PQ();

void GetTT(Task *root, Task **Player_task_tree);

Player *Delete_Player(Player *players_tree, int pid);

void fix_parent(Player *root, Player *prev);

Task *makeBST(Task **final_array, int begin, int end);

void Find_max_evidence(Player *players_tree, int evidence);

Task **Get_Final_array(Task **final_array, Task **P1_task_tree, Task **P2_task_tree, int P1_index, int P2_index);

void GetPT(Player *root, Player **Player_tree);

int count_player_nodes(Player *root);

Task *Insert_Given_Task_to_Player(Task *root, Task *task_to_insert);

void find_predecessor(Player *root, int pid, Player **predecessor);

void find_succesor(Player *root, int pid, Player **succesor);

int Find_player_place(Player *root, int pid, int STOP);

void Find_max_pid(Player *players_tree, int pid);

void Find_min_pid(Player *players_tree, int pid);

bool check_if_task_exists(Task *task);

Player *get_max_players(Player *root);

Player *get_max_aliens(Player *root);

#endif /* __AMONG_US_H_ */
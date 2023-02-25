/***************************************************************
 *                                                             *
 * file: main.cpp                                              *
 *                                                             *
 * @Author  Skerdi Basha                         		   	   *
 * @Version 1-12-2020                             			   *
 * @email   sbash@csd.uoc.gr                                   *
 *                                                             *
 * @brief   Main function and implemetantion of among_us.h     *
 *          for the needs of CS-240 project 2020               *
 *                                                             *
 ***************************************************************
 */
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <iostream>
 // Used only for ceil, hope it is ok.
#include <cmath>
#include "among_us.h"

using namespace std;

// I know that my delete sometimes does not delete a node in the tree, resulting in a copy of a player's tasks
// This is why the tesfiles cant result in a win or loss.

int a, b, max_prime, flag = 0, player_count = 0, alien_count = 0, chain = 0, count = 1,
chain_count = 0, STOP = 0, PQflag = 0, PQend = 0, PQbegin = 0, task_count = 0, P_index = 0;
;
Player* sentinel = new Player();
HT_Task* current_task = NULL;
Player* max_evidence = NULL;
Player* max_pid = NULL;
Player* min_pid = NULL;

unsigned int primes_g[650] = {
	179,
	181,
	191,
	193,
	197,
	199,
	211,
	223,
	227,
	229,
	233,
	239,
	241,
	251,
	257,
	263,
	269,
	271,
	277,
	281,
	283,
	293,
	307,
	311,
	313,
	317,
	331,
	337,
	347,
	349,
	353,
	359,
	367,
	373,
	379,
	383,
	389,
	397,
	401,
	409,
	419,
	421,
	431,
	433,
	439,
	443,
	449,
	457,
	461,
	463,
	467,
	479,
	487,
	491,
	499,
	503,
	509,
	521,
	523,
	541,
	547,
	557,
	563,
	569,
	571,
	577,
	587,
	593,
	599,
	601,
	607,
	613,
	617,
	619,
	631,
	641,
	643,
	647,
	653,
	659,
	661,
	673,
	677,
	683,
	691,
	701,
	709,
	719,
	727,
	733,
	739,
	743,
	751,
	757,
	761,
	769,
	773,
	787,
	797,
	809,
	811,
	821,
	823,
	827,
	829,
	839,
	853,
	857,
	859,
	863,
	877,
	881,
	883,
	887,
	907,
	911,
	919,
	929,
	937,
	941,
	947,
	953,
	967,
	971,
	977,
	983,
	991,
	997,
	1009,
	1013,
	1019,
	1021,
	1031,
	1033,
	1039,
	1049,
	1051,
	1061,
	1063,
	1069,
	1087,
	1091,
	1093,
	1097,
	1103,
	1109,
	1117,
	1123,
	1129,
	1151,
	1153,
	1163,
	1171,
	1181,
	1187,
	1193,
	1201,
	1213,
	1217,
	1223,
	1229,
	1231,
	1237,
	1249,
	1259,
	1277,
	1279,
	1283,
	1289,
	1291,
	1297,
	1301,
	1303,
	1307,
	1319,
	1321,
	1327,
	1361,
	1367,
	1373,
	1381,
	1399,
	1409,
	1423,
	1427,
	1429,
	1433,
	1439,
	1447,
	1451,
	1453,
	1459,
	1471,
	1481,
	1483,
	1487,
	1489,
	1493,
	1499,
	1511,
	1523,
	1531,
	1543,
	1549,
	1553,
	1559,
	1567,
	1571,
	1579,
	1583,
	1597,
	1601,
	1607,
	1609,
	1613,
	1619,
	1621,
	1627,
	1637,
	1657,
	1663,
	1667,
	1669,
	1693,
	1697,
	1699,
	1709,
	1721,
	1723,
	1733,
	1741,
	1747,
	1753,
	1759,
	1777,
	1783,
	1787,
	1789,
	1801,
	1811,
	1823,
	1831,
	1847,
	1861,
	1867,
	1871,
	1873,
	1877,
	1879,
	1889,
	1901,
	1907,
	1913,
	1931,
	1933,
	1949,
	1951,
	1973,
	1979,
	1987,
	1993,
	1997,
	1999,
	2003,
	2011,
	2017,
	2027,
	2029,
	2039,
	2053,
	2063,
	2069,
	2081,
	2083,
	2087,
	2089,
	2099,
	2111,
	2113,
	2129,
	2131,
	2137,
	2141,
	2143,
	2153,
	2161,
	2179,
	2203,
	2207,
	2213,
	2221,
	2237,
	2239,
	2243,
	2251,
	2267,
	2269,
	2273,
	2281,
	2287,
	2293,
	2297,
	2309,
	2311,
	2333,
	2339,
	2341,
	2347,
	2351,
	2357,
	2371,
	2377,
	2381,
	2383,
	2389,
	2393,
	2399,
	2411,
	2417,
	2423,
	2437,
	2441,
	2447,
	2459,
	2467,
	2473,
	2477,
	2503,
	2521,
	2531,
	2539,
	2543,
	2549,
	2551,
	2557,
	2579,
	2591,
	2593,
	2609,
	2617,
	2621,
	2633,
	2647,
	2657,
	2659,
	2663,
	2671,
	2677,
	2683,
	2687,
	2689,
	2693,
	2699,
	2707,
	2711,
	2713,
	2719,
	2729,
	2731,
	2741,
	2749,
	2753,
	2767,
	2777,
	2789,
	2791,
	2797,
	2801,
	2803,
	2819,
	2833,
	2837,
	2843,
	2851,
	2857,
	2861,
	2879,
	2887,
	2897,
	2903,
	2909,
	2917,
	2927,
	2939,
	2953,
	2957,
	2963,
	2969,
	2971,
	2999,
	3001,
	3011,
	3019,
	3023,
	3037,
	3041,
	3049,
	3061,
	3067,
	3079,
	3083,
	3089,
	3109,
	3119,
	3121,
	3137,
	3163,
	3167,
	3169,
	3181,
	3187,
	3191,
	3203,
	3209,
	3217,
	3221,
	3229,
	3251,
	3253,
	3257,
	3259,
	3271,
	3299,
	3301,
	3307,
	3313,
	3319,
	3323,
	3329,
	3331,
	3343,
	3347,
	3359,
	3361,
	3371,
	3373,
	3389,
	3391,
	3407,
	3413,
	3433,
	3449,
	3457,
	3461,
	3463,
	3467,
	3469,
	3491,
	3499,
	3511,
	3517,
	3527,
	3529,
	3533,
	3539,
	3541,
	3547,
	3557,
	3559,
	3571,
	3581,
	3583,
	3593,
	3607,
	3613,
	3617,
	3623,
	3631,
	3637,
	3643,
	3659,
	3671,
	3673,
	3677,
	3691,
	3697,
	3701,
	3709,
	3719,
	3727,
	3733,
	3739,
	3761,
	3767,
	3769,
	3779,
	3793,
	3797,
	3803,
	3821,
	3823,
	3833,
	3847,
	3851,
	3853,
	3863,
	3877,
	3881,
	3889,
	3907,
	3911,
	3917,
	3919,
	3923,
	3929,
	3931,
	3943,
	3947,
	3967,
	3989,
	4001,
	4003,
	4007,
	4013,
	4019,
	4021,
	4027,
	4049,
	4051,
	4057,
	4073,
	4079,
	4091,
	4093,
	4099,
	4111,
	4127,
	4129,
	4133,
	4139,
	4153,
	4157,
	4159,
	4177,
	4201,
	4211,
	4217,
	4219,
	4229,
	4231,
	4241,
	4243,
	4253,
	4259,
	4261,
	4271,
	4273,
	4283,
	4289,
	4297,
	4327,
	4337,
	4339,
	4349,
	4357,
	4363,
	4373,
	4391,
	4397,
	4409,
	4421,
	4423,
	4441,
	4447,
	4451,
	4457,
	4463,
	4481,
	4483,
	4493,
	4507,
	4513,
	4517,
	4519,
	4523,
	4547,
	4549,
	4561,
	4567,
	4583,
	4591,
	4597,
	4603,
	4621,
	4637,
	4639,
	4643,
	4649,
	4651,
	4657,
	4663,
	4673,
	4679,
	4691,
	4703,
	4721,
	4723,
	4729,
	4733,
	4751,
	4759,
	4783,
	4787,
	4789,
	4793,
	4799,
	4801,
	4813,
	4817,
	4831,
	4861,
	4871,
	4877,
	4889,
	4903,
	4909,
	4919,
	4931,
	4933,
	4937,
	4943,
	4951,
	4957,
	4967,
	4969,
	4973,
	4987,
	4993,
	4999,
	5003,
	5009,
	5011,
	5021,
	5023,
	5039,
	5051,
	5059,
	5077,
	5081,
	5087,
	5099,
	5101,
	5107,
	5113,
	5119,
	5147,
	5153,
	5167,
	5171,
	5179,
};

/**
 * @brief Optional function to initialize data structures that
 *        need initialization
 *
 * @return 1 on success
 *         0 on failure
 */
int initialize() {
	a = -1;
	b = -1;
	max_prime = 0;
	general_tasks_ht.tasks = new HT_Task * [max_tasks_g];
	for (unsigned int i = 0; i < max_tasks_g; i++) {
		general_tasks_ht.tasks[i] = NULL;
	}
	general_tasks_ht.count = 1;
	sentinel->evidence = 0;
	sentinel->is_alien = 0;
	sentinel->pid = -1;
	sentinel->parrent = NULL;
	sentinel->rc = NULL;
	sentinel->lc = NULL;
	sentinel->tasks = NULL;
	players_tree = sentinel;
	completed_tasks_pq = new Completed_Tasks_PQ();
	completed_tasks_pq->size = 0;
	completed_tasks_pq->tasks = new HT_Task[max_tasks_g];
	return 1;
}

/**
 * @brief Register Player
 *
 * @param pid The player's id
 *
 * @param is_alien The variable that decides if he is an alien or not
 * @return 1 on success
 *         0 on failure
 */
int register_player(int pid, int is_alien) {
	player_count += 1;
	if (is_alien == 1) {
		alien_count += 1;
	}
	if (flag == 0) {
		players_tree = Insert_Players(players_tree, pid, is_alien);
		flag = 1;
	}
	else {
		Insert_Players(players_tree, pid, is_alien);
	}
	print_players();
	cout << endl;
	return 1;
}

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
int insert_task(int tid, int difficulty) {
	task_count += 1;
	general_tasks_ht.count += 1;
	if (a == -1 || b == -1) {
		for (int i = 0; i < 650; i++) {
			if (primes_g[i] - 1 >= max_tid_g) {
				max_prime = primes_g[i];
				break;
			}
		}
		a = (rand() % (max_prime - 1) + 1);
		b = (rand() % max_prime);
	}
	int hashValue = HashFunction(tid);
	HT_Task* temp_task = new HT_Task();
	temp_task->tid = tid;
	temp_task->difficulty = difficulty;
	temp_task->next = NULL;
	if (general_tasks_ht.tasks[hashValue] == NULL) {
		general_tasks_ht.tasks[hashValue] = temp_task;
		temp_task->next = NULL;
	}
	else {
		temp_task->next = general_tasks_ht.tasks[hashValue]->next;
		general_tasks_ht.tasks[hashValue]->next = temp_task;
	}
	print_tasks();
	return 1;
}

/**
 * @brief Distribute Tasks to the players
 * @return 1 on success
 *         0 on failure
 */
int distribute_tasks() {
	current_task = general_tasks_ht.tasks[chain];
	for (int i = 0; (unsigned)i < max_tasks_g / player_count + 1; i++) {
		STOP = 0;
		Inorder(players_tree);
	}
	count = 1;
	print_double_tree();
	return 1;
}

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
int implement_task(int pid, int tid) {
	Player* root = players_tree;
	Player* player_to_implement = new Player;
	player_to_implement = SearchPT(root, pid);
	player_to_implement->tasks = DeletePTask(player_to_implement->tasks, tid);
	count = 1;
	if (player_to_implement->tasks != NULL) {
		fix_lcnt(player_to_implement->tasks, player_to_implement->tasks->tid);
	}
	print_double_tree();
	return 1;
}

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
int eject_player(int pid_1, int pid_2) {
	int P1_index = 0, P2_index = 0;
	Task** P1_task_tree = NULL;
	Task** P2_task_tree = NULL;
	Player* P1 = SearchPT(players_tree, pid_1);
	Player* P2 = SearchPT(players_tree, pid_2);
	Task** final_array = NULL;
	if (P1->is_alien != 1) {
		player_count -= 1;
		P1_index = count_nodes(P1->tasks);
		if (P1_index != 0) {
			P1_task_tree = new Task * [P1_index];
		}
		else {
			P1_task_tree = NULL;
		}
		P_index = 0;
		GetTT(P1->tasks, P1_task_tree);
	}
	else {
		alien_count -= 1;
	}

	if (P2->is_alien != 1) {
		P2_index = count_nodes(P2->tasks);
		if (P2_index != 0) {
			P2_task_tree = new Task * [P2_index];
		}
		else {
			P2_task_tree = NULL;
		}
		P_index = 0;
		GetTT(P2->tasks, P2_task_tree);
	}
	Delete_Player(players_tree, P1->pid);
	fix_parent(players_tree, NULL);

	final_array = Get_Final_array(final_array, P1_task_tree, P2_task_tree, P1_index, P2_index);

	P2->tasks = makeBST(final_array, 0, P1_index + P2_index - 1);

	if (P2->tasks != NULL) {
		fix_lcnt(P2->tasks, P2->tasks->tid);
	}

	count = 1;
	print_double_tree();
	return 1;
}

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
int witness_eject(int pid_1, int pid_2, int pid_a, int number_of_witnesses) {
	int P1_index = 0, P2_index = 0;
	Task** P1_task_tree = NULL;
	Task** P2_task_tree = NULL;
	Player* P1 = SearchPT(players_tree, pid_1);
	Player* P2 = SearchPT(players_tree, pid_2);
	Task** final_array = NULL;
	if (P1->is_alien != 1) {
		player_count -= 1;
		P1_index = count_nodes(P1->tasks);
		if (P1_index != 0) {
			P1_task_tree = new Task * [P1_index];
		}
		else {
			P1_task_tree = NULL;
		}
		P_index = 0;
		GetTT(P1->tasks, P1_task_tree);
	}
	else {
		alien_count -= 1;
	}

	if (P2->is_alien != 1) {
		P2_index = count_nodes(P2->tasks);
		if (P2_index != 0) {
			P2_task_tree = new Task * [P2_index];
		}
		else {
			P2_task_tree = NULL;
		}
		P_index = 0;
		GetTT(P2->tasks, P2_task_tree);
	}
	Delete_Player(players_tree, P1->pid);
	fix_parent(players_tree, NULL);

	final_array = Get_Final_array(final_array, P1_task_tree, P2_task_tree, P1_index, P2_index);

	P2->tasks = makeBST(final_array, 0, P1_index + P2_index - 1);

	if (P2->tasks != NULL) {
		fix_lcnt(P2->tasks, P2->tasks->tid);
	}

	Player* allien = SearchPT(players_tree, pid_a);
	allien->evidence = number_of_witnesses;
	count = 1;
	print_PN(players_tree, 1);
	return 1;
}

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
int sabotage(int number_of_tasks, int pid) {
	int i = 0;
	Player* P1 = SearchPT(players_tree, pid);
	P_index = 0;
	Find_player_place(players_tree, P1->pid, 0);
	int times = 0;
	Player* predecessor = NULL;
	Player* succesor = NULL;
	min_pid = NULL;
	max_pid = NULL;
	Find_max_pid(players_tree, 0);
	Find_min_pid(players_tree, 0);
	times = floor((float)number_of_tasks / 2);
	Player* root = P1;
	if (root->pid == min_pid->pid) {
		predecessor = max_pid;
	}
	for (i = times; i > 0; i--) {
		if (root->is_alien != -1) {
			find_predecessor(players_tree, root->pid, &predecessor);
			root = predecessor;
			if (root->pid == min_pid->pid) {
				predecessor = max_pid;
			}
		}
	}
	times = number_of_tasks - times;
	if (root->pid == max_pid->pid) {
		succesor = min_pid;
	}
	for (i = times; i > 0; i--) {
		if (root->is_alien != -1) {
			if (completed_tasks_pq->size == 0) {
				count = 1;
				print_double_tree();
				return 1;
			}
			Task* task_to_insert = pop_PQ();
			if (root->tasks == NULL) {
				root->tasks = Insert_Given_Task_to_Player(root->tasks, task_to_insert);
			}
			else {
				Insert_Given_Task_to_Player(root->tasks, task_to_insert);
			}
			fix_lcnt(root->tasks, root->tasks->tid);
			STOP = 0;
			find_succesor(players_tree, root->pid, &succesor);
			root = succesor;
			if (root->pid == max_pid->pid) {
				succesor = min_pid;
			}
		}
	}
	count = 1;
	print_double_tree();
	return 1;
}

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
int vote(int pid_1, int pid_2, int vote_evidence) {
	int P1_index = 0, P2_index = 0;
	Task** P1_task_tree = NULL;
	Task** P2_task_tree = NULL;
	Player* voted = SearchPT(players_tree, pid_1);
	voted->evidence = vote_evidence;
	max_evidence = players_tree;
	Find_max_evidence(players_tree, 0);
	Player* P1 = max_evidence;
	Player* P2 = SearchPT(players_tree, pid_2);
	Task** final_array = NULL;
	if (P1->is_alien != 1) {
		player_count -= 1;
		P1_index = count_nodes(P1->tasks);
		if (P1_index != 0) {
			P1_task_tree = new Task * [P1_index];
		}
		else {
			P1_task_tree = NULL;
		}
		P_index = 0;
		GetTT(P1->tasks, P1_task_tree);
	}
	else {
		alien_count -= 1;
	}

	if (P2->is_alien != 1) {
		P2_index = count_nodes(P2->tasks);
		if (P2_index != 0) {
			P2_task_tree = new Task * [P2_index];
		}
		else {
			P2_task_tree = NULL;
		}
		P_index = 0;
		GetTT(P2->tasks, P2_task_tree);
	}
	Delete_Player(players_tree, P1->pid);
	fix_parent(players_tree, NULL);

	final_array = Get_Final_array(final_array, P1_task_tree, P2_task_tree, P1_index, P2_index);

	P2->tasks = makeBST(final_array, 0, P1_index + P2_index - 1);

	if (P2->tasks != NULL) {
		fix_lcnt(P2->tasks, P2->tasks->tid);
	}

	count = 1;
	print_PN(players_tree, 1);
	return 1;
}

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
int give_work(int pid_1, int pid_2) {
	Task* p1_task_tree = NULL;
	Insert_Players(players_tree, pid_2, 0);
	fix_parent(players_tree, NULL);
	Player* p1 = SearchPT(players_tree, pid_1);
	Player* p2 = SearchPT(players_tree, pid_2);
	if (p1 != NULL) {
		p1_task_tree = p1->tasks;
	}
	int max_nodes = 0;
	while (p1_task_tree != NULL) {
		max_nodes += p1_task_tree->lcnt;
		p1_task_tree = p1_task_tree->rc;
	}
	int i = 0;
	Task* BST_1 = NULL;
	Task* BST_2 = NULL;
	Task* prev_1 = NULL;
	Task* prev_2 = NULL;
	Task* prev_main = NULL;

	while (p1_task_tree != NULL && i < max_nodes) {
		if (i + p1_task_tree->lcnt + 1 < max_nodes) {
			if (BST_1 == NULL) {
				BST_1 = p1_task_tree;
				prev_1 = p1_task_tree;
			}
			else {
				prev_1->rc = p1_task_tree;
				prev_1 = p1_task_tree;
			}

			if (BST_2 == NULL && i + p1_task_tree->lcnt + 1 == max_nodes) {
				BST_2 = p1_task_tree->rc;
			}
			i = i + p1_task_tree->lcnt + 1;
			prev_main = p1_task_tree;
			p1_task_tree = p1_task_tree->rc;
			prev_main->rc = NULL;
		}
		else if (i + p1_task_tree->lcnt + 1 > max_nodes) {
			if (BST_2 == NULL) {
				BST_2 = p1_task_tree;
				prev_2 = p1_task_tree;
			}
			else {
				prev_2->rc = p1_task_tree;
				prev_2 = p1_task_tree;
			}
			prev_main = p1_task_tree;
			p1_task_tree = p1_task_tree->rc;
			prev_main->rc = NULL;
		}
		else {
			p1->tasks = BST_1;
			p2->tasks = BST_2;
			break;
		}
	}
	count = 1;
	print_double_tree();
	return 1;
}

/**
 * @brief Terminate
 *
 * @return 1 on success
 *         0 on failure
 */
int Terminate() {
	get_max_aliens(players_tree);
	get_max_players(players_tree);
	if (alien_count > player_count) {
		cout << "Aliens Win!" << endl;
	}
	else if (alien_count == 0 || completed_tasks_pq->size == task_count) {
		cout << "Crewmates Win!" << endl;
	}
	else {
		cout << "Nobody won...?" << endl;
	}
	return 1;
}

/**
 * @brief Print Players
 *
 * @return 1 on success
 *         0 on failure
 */
int print_players() {
	cout << "Players = ";
	print_PT(players_tree);
	cout << endl;
	return 1;
}

/**
 * @brief Print Tasks
 *
 * @return 1 on success
 *         0 on failure
 */
int print_tasks() {
	for (unsigned int i = 0; i < max_tasks_g; i++) {
		cout << "Index " << i << ": ";
		if (general_tasks_ht.tasks[i] != NULL) {
			HT_Task* temp = general_tasks_ht.tasks[i];
			while (temp != NULL) {
				cout << "<" << temp->tid << "," << temp->difficulty << ">";
				temp = temp->next;
			}
			free(temp);
		}
		else {
			cout << "-";
		}
		cout << endl;
	}
	return 1;
}

/**
 * @brief Print Priority Queue
 *
 * @return 1 on success
 *         0 on failure
 */
int print_pq() {
	HT_Task* priority_queue = completed_tasks_pq->tasks;
	cout << "Completed Tasks = ";
	if (PQbegin != PQend) {
		int i;
		for (i = PQbegin; i < PQend; i++) {
			cout << "<" << priority_queue[i].tid << ", " << priority_queue[i].difficulty << "> ";
		}
		cout << endl;
	}
	else {
		cout << "-" << endl;
	}
	return 1;
}

/**
 * @brief Print Players & Task tree
 *
 * @return 1 on success
 *         0 on failure
 */
int print_double_tree() {
	print_PN(players_tree, 0);
	return 1;
}

/**
 * @brief Free resources
 *
 * @return 1 on success
 *         0 on failure
 */

int free_all(void) {
	return 1;
}

//My functions
//------------------------------------------------------------------------------------------

// Inserts a player into the PT(players tree)
Player* Insert_Players(Player* root, int pid, int is_alien) {
	if (root->pid == -1) {
		Player* new_player = new Player();
		new_player->is_alien = is_alien;
		new_player->pid = pid;
		new_player->evidence = 0;
		new_player->parrent = NULL;
		new_player->tasks = NULL;
		new_player->lc = sentinel;
		new_player->rc = sentinel;
		return new_player;
	}

	if (pid > root->pid) {
		Player* temp_rc = Insert_Players(root->rc, pid, is_alien);
		root->rc = temp_rc;
		temp_rc->parrent = root;
	}
	else {
		Player* temp_lc = Insert_Players(root->lc, pid, is_alien);
		root->lc = temp_lc;
		temp_lc->parrent = root;
	}
	return root;
}

// Prints the PT(players tree)
void print_PT(Player* root) {
	if (root->pid != -1) {
		print_PT(root->lc);
		cout << "<" << root->pid << ":" << root->is_alien << "> ";
		print_PT(root->rc);
	}
}

// Sets up a print for Players number in tree and their task
void print_PN(Player* root, int choice) {
	if (root->pid == -1) {
		return;
	}
	print_PN(root->lc, choice);
	if (choice == 0) {
		cout << "Player " << count++ << " = ";
	}
	else if (choice == 1) {
		cout << "<Player " << count++ << ", " << root->evidence << "> =";
	}

	if (root->is_alien == 1) {
		cout << " alien";
	}
	else if (root->tasks == NULL) {
		cout << " -";
	}
	else {
		if (count >= player_count + 1 + alien_count) {
			count = 0;
		}
		print_PTasks(root->tasks);
	}
	cout << endl;
	print_PN(root->rc, choice);
}

// Prints player's tasks
void print_PTasks(Task* root) {
	if (root == NULL)
		return;

	print_PTasks(root->lc);
	cout << " <" << root->tid << ", " << root->difficulty << "> ";
	print_PTasks(root->rc);
}

// Thats my HashFunction
int HashFunction(int tid) {
	return ((a * tid + b) % max_prime) % max_tasks_g;
}

// Inserts a given task to a given player's task tree
Task* Insert_Given_Task_to_Player(Task* root, Task* task_to_insert) {
	if (root == NULL) {
		return task_to_insert;
	}

	if (task_to_insert->tid > root->tid) {
		Task* temp_rc = Insert_Given_Task_to_Player(root->rc, task_to_insert);
		root->rc = temp_rc;
	}
	else {
		Task* temp_lc = Insert_Given_Task_to_Player(root->lc, task_to_insert);
		root->lc = temp_lc;
	}
	return root;
}

// Inserts a task from the hash table to a given player's task tree
Task* Insert_Task_to_Player(Task* root) {
	int count;
	Task* prev = root;
	Task* task_to_insert = TaskProvider();
	if ((unsigned)chain >= max_tasks_g) {
		return NULL;
	}
	int tid = task_to_insert->tid;
	Task* p = NULL;
	while (1) {
		if (root == NULL) {
			count = 0;
			root = task_to_insert;
			root->lcnt = count;
			return root;
		}
		if (prev->tid > tid) {
			prev->lcnt += 1;
			p = prev->lc;
			if (p == NULL) {
				count = 0;
				p = task_to_insert;
				p->lcnt = count;
				prev->lc = p;
				return root;
			}
		}
		if (prev->tid < tid) {
			p = prev->rc;
			if (p == NULL) {
				count = 0;
				p = task_to_insert;
				p->lcnt = count;
				prev->rc = p;
				return root;
			}
		}
		prev = p;
	}
}

// Returns tasks from player's task tree
Task* TaskProvider() {
	Task* temp = new Task();
	general_tasks_ht.count -= 1;
	while (1) {
		if (current_task != NULL) {
			temp->lcnt = 0;
			temp->difficulty = current_task->difficulty;
			temp->tid = current_task->tid;
			current_task = current_task->next;
			chain_count += 1;
			return temp;
		}
		else {
			chain += 1;
			current_task = general_tasks_ht.tasks[chain];
			chain_count = 0;
			while (current_task == NULL && (unsigned)chain < max_tasks_g) {
				chain += 1;
				current_task = general_tasks_ht.tasks[chain];
			}
		}
		if ((unsigned)chain >= max_tasks_g) {
			return NULL;
		}
	}
	return temp;
}

// Inorder traversal of players tree. Also calls Insert_Task_to_Player
void Inorder(Player* root)

{
	while (STOP == 1) {
		return;
	}
	if (root->pid == -1) {
		return;
	}
	Inorder(root->lc);
	if (STOP == 1) {
		return;
	}
	if (root->is_alien != 1) {
		if (root->tasks == NULL) {
			root->tasks = Insert_Task_to_Player(root->tasks);
		}
		else {
			Insert_Task_to_Player(root->tasks);
			if ((unsigned)chain >= max_tasks_g) {
				STOP = 1;
			}
		}
	}
	Inorder(root->rc);
}

// Returns a pointer of a player whose pid/evidence we searched for. If choice == 0 -> we are searching for the pid, else if choice == 1-> we are searching for the evidence.
Player* SearchPT(Player* root, int search_object) {
	if (root->pid == -1)
		return NULL;
	if (root->pid == search_object)
		return root;

	if (root->pid < search_object)
		return SearchPT(root->rc, search_object);

	return SearchPT(root->lc, search_object);
	return NULL;
}

// Deletes a task from the player's tree and calls push_PQ(priority queue) for it
Task* DeletePTask(Task* root, int tid) {
	if (root == NULL) {
		return NULL;
	}
	else if (tid < root->tid) {
		root->lc = DeletePTask(root->lc, tid);
	}
	else if (tid > root->tid) {
		root->rc = DeletePTask(root->rc, tid);
	}
	else {
		if (root->lc == NULL) {
			Task* temp = root->rc;
			push_PQ(root);
			delete root;
			return temp;
		}
		else if (root->rc == NULL) {
			Task* temp = root->lc;
			push_PQ(root);
			delete root;
			return temp;
		}
		else {
			Task* temp = root->rc;
			while (temp->lc != NULL) {
				temp = temp->lc;
			}
			root->tid = temp->tid;
			root->difficulty = temp->difficulty;
			push_PQ(root);
			root->rc = DeletePTask(root->rc, temp->tid);
		}
	}
	return root;
}

// Deletes a player from the players_tree
Player* Delete_Player(Player* players_tree, int pid) {
	if (players_tree->pid == -1) {
		return NULL;
	}
	else if (pid < players_tree->pid) {
		players_tree->lc = Delete_Player(players_tree->lc, pid);
	}
	else if (pid > players_tree->pid) {
		players_tree->rc = Delete_Player(players_tree->rc, pid);
	}
	else {
		if (players_tree->lc->pid == -1) {
			Player* temp = players_tree->rc;
			free(players_tree);
			return temp;
		}
		else if (players_tree->rc->pid == -1) {
			Player* temp = players_tree->lc;
			free(players_tree);
			return temp;
		}
		else {
			Player* temp = players_tree->rc;
			while (temp->pid != -1 && temp->lc->pid != -1) {
				temp = temp->lc;
			}
			players_tree->pid = temp->pid;
			players_tree->is_alien = temp->is_alien;
			players_tree->evidence = temp->evidence;
			players_tree->tasks = NULL;
			players_tree->rc = Delete_Player(players_tree->rc, temp->pid);
		}
	}
	return players_tree;
}

// Fixes the lcnt int of player's task tree, tid = root's tid
void fix_lcnt(Task* root, int tid) {
	if (root == NULL) {
		return;
	}
	if (root->tid == tid) {
		fix_lcnt(root->rc, tid);
	}
	fix_lcnt(root->lc, tid);
	root->lcnt = count_nodes(root->lc);
	fix_lcnt(root->rc, tid);
}

// Fixes the parent node of player's tree
void fix_parent(Player* root, Player* prev) {
	if (root->pid == -1) {
		return;
	}
	root->parrent = prev;
	fix_parent(root->lc, root);
	fix_parent(root->rc, root);
}

// Counts nodes in BST
int count_nodes(Task* root) {
	if (root == NULL) {
		return 0;
	}
	return 1 + count_nodes(root->lc) + count_nodes(root->rc);
}

// Pushes completed tasks into the PQ(priority queue)
void push_PQ(Task* task_to_push) {
	if (check_if_task_exists(task_to_push)) {
		HT_Task* priority_queue = completed_tasks_pq->tasks;
		PQend += 1;
		completed_tasks_pq->size += 1;
		if ((unsigned)PQend < max_tasks_g) {
			if (PQend == 0 && PQbegin == 0) {
				priority_queue[0].difficulty = task_to_push->difficulty;
				priority_queue[0].tid = task_to_push->tid;
				priority_queue[0].next = NULL;
			}
			else {
				int i, j;
				for (i = 0; i <= PQend; i++) {
					if (task_to_push->difficulty >= priority_queue[i].difficulty) {
						for (j = PQend + 1; j > i; j--) {
							priority_queue[j] = priority_queue[j - 1];
						}
						priority_queue[i].difficulty = task_to_push->difficulty;
						priority_queue[i].tid = task_to_push->tid;
						priority_queue[i].next = NULL;
						return;
					}
				}
				priority_queue[i].difficulty = task_to_push->difficulty;
				priority_queue[i].tid = task_to_push->tid;
				priority_queue[i].next = NULL;
			}
		}
	}
}

// Pops the first element in the PQ(priority queue)
Task* pop_PQ() {
	HT_Task* priority_queue = completed_tasks_pq->tasks;
	if (PQend != 0) {
		completed_tasks_pq->size -= 1;
		HT_Task to_delete = priority_queue[PQbegin];
		if (PQbegin == PQend) {
			PQbegin = 0;
			PQend = 0;
		}
		else {
			PQbegin += 1;
		}
		Task* temp = new Task();
		temp->tid = to_delete.tid;
		temp->difficulty = to_delete.difficulty;
		temp->lc = NULL;
		temp->rc = NULL;
		temp->lcnt = 0;
		return temp;
	}
	else {
		return NULL;
	}
}

// Transforms the task tree of a player into an array
void GetTT(Task* root, Task** Player_task_tree) {
	if (root == NULL)
		return;

	GetTT(root->lc, Player_task_tree);
	Player_task_tree[P_index] = root;
	P_index += 1;
	GetTT(root->rc, Player_task_tree);
}

// Makes a BST out of an array
Task* makeBST(Task** final_array, int begin, int end) {
	if (begin > end || final_array == NULL) {
		return NULL;
	}
	int mid = (begin + end) / 2;
	Task* root = new Task();
	root->tid = final_array[mid]->tid;
	root->difficulty = final_array[mid]->difficulty;
	root->lc = NULL;
	root->rc = NULL;
	root->lcnt = 0;
	root->lc = makeBST(final_array, begin, mid - 1);
	root->rc = makeBST(final_array, mid + 1, end);
	return root;
}

// Inorder traversal of BST to find max evidence player.
void Find_max_evidence(Player* players_tree, int evidence) {
	if (players_tree->pid == -1)
		return;

	Find_max_evidence(players_tree->lc, evidence);
	if (players_tree->evidence > evidence) {
		max_evidence = players_tree;
		evidence = players_tree->evidence;
	}
	Find_max_evidence(players_tree->rc, evidence);
}

// Inorder traversal of BST to find max pid player.
void Find_max_pid(Player* players_tree, int pid) {
	Player* current = players_tree;
	while (current->rc->pid != -1)
		current = current->rc;

	max_pid = current;
	return;
}

// Inorder traversal of BST to find min pid player.
void Find_min_pid(Player* players_tree, int pid) {
	Player* current = players_tree;
	while (current->lc->pid != -1)
		current = current->lc;

	min_pid = current;
	return;
}

// Merges 2 arrays into one
Task** Get_Final_array(Task** final_array, Task** P1_task_tree, Task** P2_task_tree, int P1_index, int P2_index) {
	final_array = new Task * [P1_index + P2_index];
	int i = 0, j = 0, z = 0;

	if (P1_task_tree == NULL && P2_task_tree == NULL) {
		final_array = NULL;
	}
	else if (P1_task_tree == NULL) {
		while (j < P2_index) {
			final_array[z] = P2_task_tree[j];
			j++;
			z++;
		}
	}
	else if (P2_task_tree == NULL) {
		while (i < P1_index) {
			final_array[z] = P1_task_tree[i];
			i++;
			z++;
		}
	}
	else {
		while (i < P1_index && j < P2_index) {
			if (P1_task_tree[i] < P2_task_tree[j]) {
				final_array[z] = P1_task_tree[i];
				i += 1;
			}
			else {
				final_array[z] = P2_task_tree[j];
				j += 1;
			}
			z += 1;
		}

		while (j < P2_index) {
			final_array[z] = P2_task_tree[j];
			j++;
			z++;
		}

		while (i < P1_index) {
			final_array[z] = P1_task_tree[i];
			i++;
			z++;
		}
	}
	return final_array;
}

// Counts all the nodes in the players tree
int count_player_nodes(Player* root) {
	if (root->pid == -1) {
		return 0;
	}
	return 1 + count_player_nodes(root->lc) + count_player_nodes(root->rc);
}

// Find the predecessor of player with pid
void find_predecessor(Player* root, int pid, Player** predecessor) {
	if (root->pid == -1)
		return;

	find_predecessor(root->lc, pid, predecessor);

	if (root && root->pid < pid) {
		*predecessor = root;
	}

	find_predecessor(root->rc, pid, predecessor);
}

// Find the succesor of player with pid
void find_succesor(Player* root, int pid, Player** succesor) {
	if (root->pid == -1 || STOP == 1)
		return;

	find_succesor(root->lc, pid, succesor);

	if (STOP == 1) {
		return;
	}
	if (root->pid > pid && root->pid != -1) {
		*succesor = root;
		STOP = 1;
		return;
	}
	find_succesor(root->rc, pid, succesor);
	if (STOP == 1) {
		return;
	}
}

// Find player's place in inorder traversal
int Find_player_place(Player* root, int pid, int STOP) {
	if (root->pid == -1 || STOP == 1)
		return 0;

	Find_player_place(root->lc, pid, STOP);

	if (root->pid != pid) {
		P_index += 1;
	}
	else {
		STOP = 1;
		return 0;
	}

	Find_player_place(root->rc, pid, STOP);
	return 0;
}

bool check_if_task_exists(Task* task) {
	for (int i = PQbegin; i < PQend; i++) {
		if (completed_tasks_pq->tasks[i].tid == task->tid) {
			return false;
		}
	}
	return true;
}

Player* get_max_players(Player* root) {
	if (root->pid == -1)
		return NULL;

	get_max_players(root->lc);
	if (root->is_alien != 1) {
		player_count += 1;
	}
	get_max_players(root->rc);
	return NULL;
}

Player* get_max_aliens(Player* root) {
	if (root->pid == -1)
		return NULL;

	get_max_aliens(root->lc);
	if (root->is_alien == 1) {
		alien_count += 1;
	}
	get_max_aliens(root->rc);
	return NULL;
}
//------------------------------------------------------------------------------------------

#define BUFFER_SIZE 1024 /* Maximum length of a line in input file */

/* Uncomment the following line to enable debugging prints
 * or comment to disable it */
#define DEBUG
#ifdef DEBUG
#define DPRINT(...) fprintf(stderr, __VA_ARGS__);
#else /* DEBUG */
#define DPRINT(...)
#endif /* DEBUG */

 /**
  * @brief The main function
  *
  * @param argc Number of arguments
  * @param argv Argument vector
  *
  * @return 0 on success
  *         1 on failure
  */
int main(int argc, char** argv) {
	FILE* fin = NULL;
	char buff[BUFFER_SIZE], event = '\0';

	/* Check command buff arguments */
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <input_file> <>\n", argv[0]);
		return EXIT_FAILURE;
	}

	/* Open input file */
	if ((fin = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "\n Could not open file: %s\n", argv[1]);
		perror("Opening test file\n");
		return EXIT_FAILURE;
	}

	// Read max enemy soldiers' number
	fgets(buff, BUFFER_SIZE, fin);
	sscanf(buff, "%d", &max_tasks_g);
	DPRINT("Max number of tasks: %d\n", max_tasks_g)

		// Read max enemy soldiers' ID
		fgets(buff, BUFFER_SIZE, fin);
	sscanf(buff, "%d", &max_tid_g);
	DPRINT("Max task tid: %d\n", max_tid_g)

		/* Initializations */
		initialize();

	/* Read input file buff-by-buff and handle the events */
	while (fgets(buff, BUFFER_SIZE, fin)) {

		DPRINT("\n>>> Event: %s", buff);

		switch (buff[0]) {

			/* Comment */
		case '#':
			break;

			/* Register Player
			 * P <pid> <is_alien> */
		case 'P':
		{
			int pid;
			int is_alien;
			sscanf(buff, "%c %d %d", &event, &pid, &is_alien);
			DPRINT("%c %d %d\n", event, pid, is_alien);

			if (register_player(pid, is_alien)) {
				DPRINT("P %d %d succeeded\n", pid, is_alien);
			}
			else {
				fprintf(stderr, "P %d %d failed\n", pid, is_alien);
			}

			break;
		}

		/* Insert Task
		 * T <tid> <difficulty>  */
		case 'T':
		{
			int tid, difficulty;

			sscanf(buff, "%c %d %d", &event, &tid, &difficulty);
			DPRINT("%c %d %d\n", event, tid, difficulty);

			if (insert_task(tid, difficulty)) {
				DPRINT("%c %d %d succeded\n", event, tid, difficulty);
			}
			else {
				fprintf(stderr, "%c %d %d failed\n", event, tid, difficulty);
			}

			break;
		}

		/* Distribute Tasks
		 * D */
		case 'D':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (distribute_tasks()) {
				DPRINT("%c succeeded\n", event);
			}
			else {
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Implement Task
		 * I <pid> <tid> */
		case 'I':
		{
			int pid, tid;

			sscanf(buff, "%c %d %d", &event, &pid, &tid);
			DPRINT("%c %d %d \n", event, pid, tid);

			if (implement_task(pid, tid)) {
				DPRINT("%c %d %d succeeded\n", event, pid, tid);
			}
			else {
				fprintf(stderr, "%c %d %d failed\n", event, pid, tid);
			}

			break;
		}

		/* Eject Player
		 * E <pid_1> <pid_2>*/
		case 'E':
		{
			int pid_1, pid_2;

			sscanf(buff, "%c %d %d", &event, &pid_1, &pid_2);
			DPRINT("%c %d %d\n", event, pid_1, pid_2);

			if (eject_player(pid_1, pid_2)) {
				DPRINT("%c %d %d succeeded\n", event, pid_1, pid_2);
			}
			else {
				fprintf(stderr, "%c %d %d failed\n", event, pid_1, pid_2);
			}

			break;
		}

		/* Witness Ejection
		 * W <pid> <pid_a> <number_of_witnesses>
		 */
		case 'W':
		{
			int pid_1, pid_2, pid_a, number_of_witnesses;

			sscanf(buff, "%c %d %d %d %d", &event, &pid_1, &pid_2, &pid_a, &number_of_witnesses);
			DPRINT("%c %d %d %d %d\n", event, pid_1, pid_2, pid_a, number_of_witnesses);

			if (witness_eject(pid_1, pid_2, pid_a, number_of_witnesses)) {
				DPRINT("%c %d %d %d %d succeded\n", event, pid_1, pid_2, pid_a, number_of_witnesses);
			}
			else {
				fprintf(stderr, "%c %d %d %d %d failed\n", event, pid_1, pid_2, pid_a, number_of_witnesses);
			}

			break;
		}

		/* Sabotage
		 * S <number_of_tasks> <pid> */
		case 'S':
		{
			int number_of_tasks, pid;

			sscanf(buff, "%c %d %d\n", &event, &number_of_tasks, &pid);
			DPRINT("%c %d %d\n", event, number_of_tasks, pid);

			if (sabotage(number_of_tasks, pid)) {
				DPRINT("%c %d %d succeeded\n", event, number_of_tasks, pid);
			}
			else {
				fprintf(stderr, "%c %d %d failed\n", event, number_of_tasks, pid);
			}

			break;
		}

		/* Vote
		 * V <pid_1> <pid_2> <vote_evidence> */
		case 'V':
		{
			int pid_1, pid_2, vote_evidence;

			sscanf(buff, "%c %d %d %d\n", &event, &pid_1, &pid_2, &vote_evidence);
			DPRINT("%c %d %d %d\n", event, pid_1, pid_2, vote_evidence);

			if (vote(pid_1, pid_2, vote_evidence)) {
				DPRINT("%c %d %d %d succeeded\n", event, pid_1, pid_2, vote_evidence);
			}
			else {
				fprintf(stderr, "%c %d %d %d failed\n", event, pid_1, pid_2, vote_evidence);
			}

			break;
		}

		/* Give Away Work
		 * G <pid_1> <pid_2> */
		case 'G':
		{
			int pid_1, pid_2;

			sscanf(buff, "%c %d %d", &event, &pid_1, &pid_2);
			DPRINT("%c %d %d\n", event, pid_1, pid_2);

			if (give_work(pid_1, pid_2)) {
				DPRINT("%c %d %d succeeded\n", event, pid_1, pid_2);
			}
			else {
				fprintf(stderr, "%c %d %d failed\n", event, pid_1, pid_2);
			}

			break;
		}

		/* Terminate
		 * F */
		case 'F':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (Terminate()) {
				DPRINT("%c succeeded\n", event);
			}
			else {
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Print Players
		 * X */
		case 'X':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (print_players()) {
				DPRINT("%c succeeded\n", event);
			}
			else {
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Print Tasks
		 * Y */
		case 'Y':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (print_tasks()) {
				DPRINT("%c succeeded\n", event);
			}
			else {
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Print Priority Queue
		 * Z */
		case 'Z':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (print_pq()) {
				DPRINT("%c succeeded\n", event);
			}
			else {
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Print Players & Tasks tree
		 * F */
		case 'U':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);
			count = 1; //sry
			if (print_double_tree()) {
				DPRINT("%c succeeded\n", event);
			}
			else {
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Empty line */
		case '\n':
			break;

			/* Ignore everything else */
		default:
			DPRINT("Ignoring buff: %s \n", buff);

			break;
		}
	}

	free_all();
	return (EXIT_SUCCESS);
}
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <iostream>
#include "among_us.h"

using namespace std;

int Total_Tasks = 0, player_count = 0, alien_count = 0;

// Every function I made is added to the end
// Events that share the same functions as G are not woking after the 2nd test file. I suspect that the sort function is not working as intendeed.

int initialize() {
	Players* p = new Players;
	p->pid = -1;
	p->is_alien = -1;
	p->evidence = -1;
	p->next = NULL;
	p->prev = NULL;
	players_head = p;
	Head_GL* h = new Head_GL;
	tasks_head = h;
	Head_Completed_Task_Stack* stack = new Head_Completed_Task_Stack;
	stack->count = 0;
	tasks_stack = stack;
	return 1;
}

int register_player(int pid, int is_alien) {
	pushPlayers(&players_head, pid, is_alien);
	printPlayerList(players_head);
	return 1;
}

int insert_task(int tid, int difficulty) {
	pushTasks(&tasks_head, tid, difficulty);
	printTaskList(tasks_head);
	return 1;
}

int distribute_tasks() {
	Players* p = players_head->next;
	Players* reseter = players_head->next;
	Tasks* t = tasks_head->head;
	int i, cnt = 0;
	for (i = 0; i < Total_Tasks; i++) {
		if (cnt == player_count) {
			p = reseter;
			cnt = 0;
		}
		if (p->is_alien != 1 && p->tasks_head == p->tasks_sentinel) {
			Tasks* ft = new Tasks;
			ft->tid = t->tid;
			ft->difficulty = t->difficulty;
			p->tasks_head = ft;
			ft->next = p->tasks_sentinel;
			p->tasks_sentinel->next = p->tasks_head;
			cnt += 1;
			p = p->next;
			t = t->next;
		}
		else {
			Tasks* nt = new Tasks;
			Tasks* ft = new Tasks;
			ft->tid = t->tid;
			ft->difficulty = t->difficulty;
			nt = p->tasks_head;
			p->tasks_head = ft;
			ft->next = nt;
			cnt += 1;
			p = p->next;
			t = t->next;
		}
	}
	p = reseter;
	for (i = 0; i < player_count; i++) {
		Players* dummy = new Players;
		dummy->tasks_head = nullptr;
		Tasks* current = p->tasks_head;
		Tasks* last;
		while (current != p->tasks_sentinel) {
			Tasks* next = current->next;
			sort(&dummy->tasks_head, nullptr, current);
			current = next;
		}
		if (last->tid != -1) {
			Tasks* t = new Tasks;
			last = last_element(&dummy->tasks_head);
			t->tid = -1;
			t->difficulty = 0;
			last->next = t;
			p->tasks_head = dummy->tasks_head;
			p->tasks_sentinel = last->next;
			p = p->next;
		}
	}
	print_double_list();
	return 1;
}

int implement_task(int pid, int difficulty) {
	Players* test_p = players_head->next;
	Players* p;
	Tasks* removed;
	int i, flag = 0, is_p = 0;
	for (i = 0; i < player_count; i++) {
		if (test_p->pid == pid) {
			p = test_p;
			is_p = 1;
		}
		else {
			test_p = test_p->next;
		}
	}
	if (is_p == 1) {
		Tasks* t = p->tasks_head;
		while (t != p->tasks_sentinel) {
			if (t->difficulty == difficulty) {
				removed = Remove(p, t);
				push_stack(&tasks_stack, removed);
				flag = 1;
				break;
			}
			t = t->next;
		}
		if (flag != 1) {
			Tasks* current = new Tasks;
			Tasks* t = p->tasks_head;
			int max = 0;
			if (t != p->tasks_sentinel) {
				while (t != p->tasks_sentinel) {
					if (t->difficulty > max) {
						max = t->difficulty;
						current = t;
					}
					t = t->next;
				}
				cout << current->tid << endl;
				removed = Remove(p, current);
				push_stack(&tasks_stack, removed);
			}
			else {
				return 0;
			}
		}
		print_double_list();
		return 1;
	}
	else {
		return 0;
	}
}

int eject_player(int pid) {
	Players* p = players_head->next;
	Players* to_delete = new Players;
	Players* min_p = new Players;
	int i, task_count = 0, min, flag = 0;
	for (i = 0; i < player_count; i++) {
		Tasks* counter = p->tasks_head;
		if (p->pid == pid) {
			to_delete = p;
		}
		while (counter != p->tasks_sentinel) {
			counter = counter->next;
			task_count += 1;
		}
		if (flag == 0) {
			min = task_count;
			min_p = p;
			flag = 1;
		}
		if (task_count < min) {
			min_p = p;
			min = task_count;
		}
		task_count = 0;
		p = p->next;
	}
	Tasks* remove = new Tasks;
	Tasks* head = to_delete->tasks_head;
	if (head != to_delete->tasks_sentinel) {
		remove = Remove(to_delete, to_delete->tasks_head);
	}
	if (min_p->tasks_head == min_p->tasks_sentinel) {
		Tasks* new_node = new Tasks;
		new_node->tid = remove->tid;
		new_node->difficulty = remove->difficulty;
		new_node->next = min_p->tasks_head;
		min_p->tasks_head = new_node;
	}
	else {
		sort(&min_p->tasks_head, min_p->tasks_sentinel, remove);
	}
	player_count -= 1;
	print_double_list();
	return 1;
}

int witness_eject(int pid, int pid_a, int number_of_witnesses) {
	Players* p = players_head->next;
	Players* to_eject = new Players;
	while (p != players_head) {
		if (p->pid == pid_a) {
			p->evidence += number_of_witnesses;
		}
		if (p->pid == pid) {
			to_eject = p;
		}
		p = p->next;
	}
	p = players_head->next;
	int i, task_count = 0, flag = 0, min;
	Players* min_p = new Players;
	for (i = 0; i < player_count; i++) {
		Tasks* counter = p->tasks_head;
		while (counter != p->tasks_sentinel) {
			counter = counter->next;
			task_count += 1;
		}
		if (flag == 0) {
			min = task_count;
			min_p = p;
			flag = 1;
		}
		if (task_count < min) {
			min_p = p;
			min = task_count;
		}
		task_count = 0;
		p = p->next;
	}
	Tasks* remove = new Tasks;
	Tasks* head = to_eject->tasks_head;
	if (head != to_eject->tasks_sentinel) {
		remove = Remove(to_eject, to_eject->tasks_head);
	}
	if (min_p->tasks_head == min_p->tasks_sentinel) {
		Tasks* new_node = new Tasks;
		new_node->tid = remove->tid;
		new_node->difficulty = remove->difficulty;
		new_node->next = min_p->tasks_head;
		min_p->tasks_head = new_node;
	}
	else {
		sort(&min_p->tasks_head, min_p->tasks_sentinel, remove);
	}
	free(p);
	print_evidence();
	return 1;
	return 1;
}

int sabbotage(int pid, int number_of_tasks) {
	Head_Completed_Task_Stack* h = tasks_stack;
	Tasks* poped = new Tasks;
	Players* p = players_head;
	int i, j, c = 0;
	for (j = 0; j < player_count; j++) {
		if (p->pid != pid) {
			p = p->next;
		}
	}
	c = number_of_tasks / 2;
	for (j = 0; j < c; j++) {
		p = p->prev;
	}
	for (i = 0; i < number_of_tasks; i++) {
		poped = Pop(h);
		if (poped != NULL) {
			sort(&p->tasks_head, p->tasks_sentinel, poped);
		}
		else {
			free(poped);
			return 0;
			break;
		}
		p = p->next;
	}
	print_double_list();
	return 1;
}

int vote(int pid, int vote_evidence) {
	Players* p = players_head->next;
	while (p != players_head) {
		if (p->pid == pid) {
			p->evidence = vote_evidence;
			break;
		}
		else {
			p = p->next;
		}
	}
	p = players_head->next;
	int max = 0, i, task_count = 0, flag = 0, min;
	Players* max_p = new Players;
	Players* min_p = new Players;
	while (p != players_head) {
		if (p->evidence > max) {
			max = p->evidence;
			max_p = p;
		}
		p = p->next;
	}
	for (i = 0; i < player_count; i++) {
		Tasks* counter = p->tasks_head;
		while (counter != p->tasks_sentinel) {
			counter = counter->next;
			task_count += 1;
		}
		if (flag == 0) {
			min = task_count;
			min_p = p;
			flag = 1;
		}
		if (task_count < min) {
			min_p = p;
			min = task_count;
		}
		task_count = 0;
		p = p->next;
	}
	Tasks* remove = new Tasks;
	Tasks* head = max_p->tasks_head;
	if (head != max_p->tasks_sentinel) {
		remove = Remove(max_p, max_p->tasks_head);
	}
	if (min_p->tasks_head == min_p->tasks_sentinel) {
		Tasks* new_node = new Tasks;
		new_node->tid = remove->tid;
		new_node->difficulty = remove->difficulty;
		new_node->next = min_p->tasks_head;
		min_p->tasks_head = new_node;
	}
	else {
		sort(&min_p->tasks_head, min_p->tasks_sentinel, remove);
	}
	if (max_p->is_alien == 1) {
		alien_count -= 1;
	}
	else {
		player_count -= 1;
	}
	print_evidence();
	return 1;
}

int give_work() {
	Players* p = players_head->next;
	Players* max_p = new Players;
	Players* min_p = new Players;
	int i, task_count = 0, min, max = 0, flag = 0;
	for (i = 0; i < player_count; i++) {
		Tasks* counter = p->tasks_head;
		while (counter != p->tasks_sentinel) {
			task_count += 1;
			counter = counter->next;
		}
		if (flag == 0) {
			min = task_count;
			min_p = p;
			flag = 1;
		}
		if (task_count > max) {
			max_p = p;
			max = task_count;
		}
		if (task_count < min) {
			min_p = p;
			min = task_count;
		}
		task_count = 0;
		p = p->next;
		free(counter);
	}
	i = 0;
	max = max / 2;
	Tasks* remove = new Tasks;
	Tasks* t = max_p->tasks_head;
	while (i < max) {
		remove = Remove(max_p, t);
		if (min_p->tasks_head == min_p->tasks_sentinel) {
			Tasks* new_node = new Tasks;
			new_node->tid = remove->tid;
			new_node->difficulty = remove->difficulty;
			new_node->next = min_p->tasks_head;
			min_p->tasks_head = new_node;
		}
		else {
			sort(&min_p->tasks_head, min_p->tasks_sentinel, remove);
		}
		i += 1;
	}
	print_double_list();
	return 1;
}

int Terminate() {
	Head_Completed_Task_Stack* h = tasks_stack;
	if (alien_count >= player_count) {
		cout << "Aliens win." << endl;
		;
	}
	else if (alien_count == 0 || h->count == Total_Tasks) {
		cout << "CrewMates win." << endl;
	}
	else {
		cout << "Noone won yet" << endl;
	}
	return 1;
}

int print_players() {
	Players* p = players_head->next;
	cout << "Players : ";
	while (p != players_head) {
		cout << "<" << p->pid << "," << p->is_alien << ">"
			<< " ";
		p = p->next;
	}
	cout << endl;
	return 1;
}

int print_tasks() {
	Tasks* t = tasks_head->head;
	cout << "List_Tasks : ";
	while (t != NULL) {
		cout << "<" << t->tid << "," << t->difficulty << ">"
			<< " ";
		t = t->next;
	}
	cout << endl;
	return 1;
}

int print_stack() {
	Head_Completed_Task_Stack* h = tasks_stack;
	cout << "Stack_Tasks : ";
	for (int i = 0; i < h->count; i++) {
		cout << "<" << h->head->tid << "," << h->head->difficulty << ">"
			<< " ";
	}
	cout << endl;
	return 1;
}

int print_double_list() {
	Players* p = players_head->next;
	int i, j;
	for (i = 0; i < player_count + alien_count; i++) {
		Tasks* nt = p->tasks_head;
		j = 0;
		if (p->is_alien == 1 || nt == p->tasks_sentinel || nt == NULL) {
			cout << "Player" << i + 1 << " = " << 0 << endl;
		}
		else {
			while (nt != p->tasks_sentinel) {
				if (j == 0) {
					cout << "Player" << i + 1 << " = <" << nt->tid << "," << nt->difficulty << ">";
				}
				else {
					cout << ",<" << nt->tid << "," << nt->difficulty << ">";
				}
				if (nt->next == p->tasks_sentinel) {
					cout << endl;
				}
				nt = nt->next;
				j += 1;
			}
		}

		p = p->next;
	}
	return 1;
}

int free_all(void) {
	return 1;
}

// My functions:

void pushPlayers(Players** head, int pid_new, int is_alien_new) {
	Players* p = new Players;
	if (is_alien_new != 1) {
		player_count += 1;
		Tasks* t = new Tasks;
		t->tid = -1;
		t->difficulty = 0;
		p->tasks_sentinel = t;
		p->tasks_head = p->tasks_sentinel;
		p->tasks_sentinel->next = p->tasks_head;
	}
	else {
		alien_count += 1;
	}
	p->pid = pid_new;
	p->is_alien = is_alien_new;
	cout << is_alien_new << endl;
	p->evidence = 0;
	if ((*head)->next == NULL) {
		(*head)->next = p;
		(*head)->prev = p;
		p->prev = (*head);
		p->next = (*head);
	}
	else {
		Players* np = new Players;
		np = (*head)->next;
		np->prev = p;
		p->next = np;
		p->prev = (*head);
		(*head)->next = p;
	}
}

void pushTasks(Head_GL** tasks_head, int tid_new, int difficulty_new) {
	Head_GL* hp = (*tasks_head);
	Tasks* t = new Tasks;
	t->tid = tid_new;
	t->difficulty = difficulty_new;
	Total_Tasks += 1;
	if (difficulty_new == 1) {
		hp->tasks_count[0] += 1;
	}
	else if (difficulty_new == 2) {

		hp->tasks_count[1] += 1;
	}
	else if (difficulty_new == 3) {

		hp->tasks_count[2] += 1;
	}
	if (Total_Tasks != 1) {
		Tasks* current = hp->head;
		while (current->next != NULL && current->next->difficulty < t->difficulty) {

			current = current->next;
		}
		t->next = current->next;
		current->next = t;
	}
	else {

		hp->head = t;
		t->next = NULL;
	}
}

void printPlayerList(Players* head) {
	Players* p = new Players;
	p = head->next;
	cout << "Players = ";
	while (p != head) {
		cout << "<" << p->pid << ":" << p->is_alien << ">";
		p = p->next;
	}
	cout << endl;
}

void printTaskList(Head_GL* tasks_head) {
	Head_GL* h = tasks_head;
	Tasks* t = h->head;
	cout << "Tasks = ";
	while (t != NULL) {
		cout << "<" << t->tid << ":" << t->difficulty << ">";
		t = t->next;
	}
	cout << endl;
}

void sort(Tasks** head_ref, Tasks* sentinel, Tasks* new_node) {
	Tasks* current = new Tasks;
	if ((*head_ref) == sentinel || (*head_ref)->difficulty >= new_node->difficulty) {
		cout << "0" << endl;
		new_node->next = *head_ref;
		*head_ref = new_node;
	}
	else {
		cout << "1" << endl;
		current = *head_ref;
		while (current->next != sentinel && current->next->difficulty < new_node->difficulty) {
			current = current->next;
		}
		cout << "2" << endl;
		new_node->next = current->next;
		current->next = new_node;
	}
}

Tasks* last_element(Tasks** head_ref) {
	Tasks* current = (*head_ref);
	while (current->next != NULL) {
		current = current->next;
	}
	return current;
}

Tasks* Remove(Players* p, Tasks* t) {
	Tasks* task_to_return = new Tasks;
	if (p->tasks_head == t) {
		if (t->next == p->tasks_sentinel) {
			task_to_return = t;
			p->tasks_head = p->tasks_sentinel;
			free(t);
		}
		else {
			task_to_return = t;
			p->tasks_head = t->next;
			free(t);
		}
	}
	else {
		Tasks* tmp = p->tasks_head;
		while (tmp->next != p->tasks_sentinel && tmp->next != t) {
			tmp = tmp->next;
		}
		task_to_return = t;
		tmp->next = tmp->next->next;
		free(t);
	}
	return task_to_return;
}

void push_stack(Head_Completed_Task_Stack** head_ref, Tasks* t) {
	Head_Completed_Task_Stack* h = (*head_ref);
	h->count += 1;
	Tasks* current = h->head;
	if (current->next == NULL) {
		h->head = t;
		t->next = NULL;
	}
	else {
		Tasks* tmp = new Tasks;
		tmp->tid = t->tid;
		tmp->difficulty = t->difficulty;
		tmp->next = current;
		h->head = tmp;
	}
	(*head_ref) = h;
}

Tasks* Pop(Head_Completed_Task_Stack* h) {
	Tasks* t = h->head;
	if (t->next != NULL) {
		h->head = t->next;
	}
	else {
		h->head = NULL;
		t = NULL;
	}
	h->count -= 1;
	return t;
}

void print_evidence() {
	Players* np = players_head->next;
	int i = 0;
	while (np != players_head) {
		cout << "<Player " << i + 1 << "," << np->evidence << "> = ";
		if (np->is_alien == 1 || np->tasks_head == np->tasks_sentinel) {
			cout << 0;
		}
		else {
			Tasks* t = np->tasks_head;
			while (t != np->tasks_sentinel) {
				cout << "<" << t->tid << "," << t->difficulty << ">";
				t = t->next;
			}
		}
		cout << endl;
		np = np->next;
		i += 1;
	}
}

//---------------------------------------------------------------------------------------
#define BUFFER_SIZE 1024 /* Maximum length of a line in input file */

/* Uncomment the following line to enable debugging prints
 * or comment to disable it */
#define DEBUG
#ifdef DEBUG
#define DPRINT(...) fprintf(stderr, __VA_ARGS__);
#else /* DEBUG */
#define DPRINT(...)
#endif /* DEBUG */

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

	/* Initializations */
	initialize();

	/* Read input file buff-by-buff and handle the events */
	while (fgets(buff, BUFFER_SIZE, fin)) {

		DPRINT("\n>>> Event: %s", buff);

		switch (buff[0]) {

			/* Comment */
		case '#':
			break;

			/* Register player
				 * P <pid><is_alien> */
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

		/* Insert task
			 * T <tid><difficulty>  */
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
			 * I <pid> <difficulty> */
		case 'I':
		{
			int pid, difficulty;

			sscanf(buff, "%c %d %d", &event, &pid, &difficulty);
			DPRINT("%c %d %d \n", event, pid, difficulty);

			if (implement_task(pid, difficulty)) {
				DPRINT("%c %d %d succeeded\n", event, pid, difficulty);
			}
			else {
				fprintf(stderr, "%c %d %d failed\n", event, pid, difficulty);
			}

			break;
		}

		/* Eject Player
			 * E <pid>*/
		case 'E':
		{
			int pid;

			sscanf(buff, "%c %d", &event, &pid);
			DPRINT("%c %d\n", event, pid);

			if (eject_player(pid)) {
				DPRINT("%c %d succeeded\n", event, pid);
			}
			else {
				fprintf(stderr, "%c %d failed\n", event, pid);
			}

			break;
		}

		/* Witness Ejection
			 * W <pid> <pid_a> <number_of_witnesses>
			 */
		case 'W':
		{
			int pid, pid_a, number_of_witnesses;

			sscanf(buff, "%c %d %d %d", &event, &pid, &pid_a, &number_of_witnesses);
			DPRINT("%c %d %d %d\n", event, pid, pid_a, number_of_witnesses);

			if (witness_eject(pid, pid_a, number_of_witnesses)) {
				DPRINT("%c %d %d %d succeded\n", event, pid, pid_a, number_of_witnesses);
			}
			else {
				fprintf(stderr, "%c %d %d %d failed\n", event, pid, pid_a, number_of_witnesses);
			}

			break;
		}

		/* Sabbotage
			 * S <number_of_tasks><pid> */
		case 'S':
		{
			int pid, number_of_tasks;

			sscanf(buff, "%c %d %d\n", &event, &number_of_tasks, &pid);
			DPRINT("%c %d %d\n", event, number_of_tasks, pid);

			if (sabbotage(pid, number_of_tasks)) {
				DPRINT("%c %d %d succeeded\n", event, number_of_tasks, pid);
			}
			else {
				fprintf(stderr, "%c %d %d failed\n", event, number_of_tasks, pid);
			}

			break;
		}

		/* Vote
			 * V <pid> <vote_evidence> */
		case 'V':
		{
			int pid, vote_evidence;

			sscanf(buff, "%c %d %d\n", &event, &pid, &vote_evidence);
			DPRINT("%c %d %d\n", event, pid, vote_evidence);

			if (vote(pid, vote_evidence)) {
				DPRINT("%c %d %d succeeded\n", event, pid, vote_evidence);
			}
			else {
				fprintf(stderr, "%c %d %d failed\n", event, pid, vote_evidence);
			}

			break;
		}

		/* Give Away Work
			 * G */
		case 'G':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (give_work()) {
				DPRINT("%c succeeded\n", event);
			}
			else {
				fprintf(stderr, "%c failed\n", event);
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
		/* Print Stack
			 * Z */
		case 'Z':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (print_stack()) {
				DPRINT("%c succeeded\n", event);
			}
			else {
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}
		/* Print Players & Tasks list
			 * U */
		case 'U':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (print_double_list()) {
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
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

struct student {
	char name[101];
	char id[101];
	float progGrade, EnGrade, mathGrade;
	float average;
};

struct node {
	struct student st;
	struct node *next;
};

int lenList(struct node *first) {
	int i;
	for(i = 0; first != NULL; first = first->next, i++);

	return i;
}

struct node *ave(struct node *first) {
	struct node *temp = first;

	if(first == NULL) {
		printf("\n\nlist is empty\n\n");
		printf("\n____________\n\n");

		return first;
	}

	for(; temp !=NULL; temp = temp->next) {
		temp->st.average = (temp->st.EnGrade + temp->st.mathGrade + temp->st.progGrade) / 3;
	}

	return first;
}

struct node *create() {
	struct node *temp = (struct node*)malloc(sizeof(struct node));
	char name[101], id[101];
	float proGrade, EnGrade, mathGrade;
	printf("\n\nname: ");
	gets(name);
	printf("\nID: ");
	gets(id);
	printf("\nprogramming grade:  ");
	scanf("%f", &proGrade);
	printf("\nEnglish grade: ");
	scanf("%f", &EnGrade);
	printf("\nmath grade: ");
	scanf("%f", &mathGrade);
	fflush(stdin);

	strcpy(temp->st.name, name);
	strcpy(temp->st.id, id);
	temp->st.EnGrade = EnGrade;
	temp->st.mathGrade = mathGrade;
	temp->st.progGrade= proGrade;
	temp->next = NULL;

	return temp;
}

struct node *addEnd(struct node *first, struct node *newNode) {
	struct node *temp = first;
	if(first == NULL) {
		printf("\n\nstudent added successfully.\n\n");
		printf("\n______________\n\n");

		return newNode;
	}

	for(; temp != NULL; temp = temp->next) {
		if((strcmp(temp->st.name, newNode->st.name) == 0) || (strcmp(temp->st.id, newNode->st.id) == 0)) {
			temp->st = newNode->st;
			printf("\n\nstudent added successfully.\n\n");
			printf("\n______________\n\n");
			return first;
		}
	}

	temp = first;

	for(; temp->next != NULL; temp = temp->next);
	temp->next = newNode;

	printf("\n\nstudent added successfully.\n\n");
	printf("\n______________\n\n");

	return first;
}

struct node *DeleteById(struct node *first, char id[]) {
	struct node *temp = first;

	if(first == NULL) {
		printf("\n\nlist is empty.\n\n");
		return first;
	}
	if(strcmp(first->st.id, id) == 0) {
		first = first->next;
		free(temp);
		printf("\n\nstudent deleted successfully.\n\n");
		printf("\n__________________\n\n");
		return first;
	}

	for(; temp->next != NULL; temp = temp->next) {
		if(strcmp(temp->next->st.id, id) == 0) {
			struct node *hold1 = temp->next;
			temp->next = temp->next->next;
			free(hold1);
			printf("\n\nstudent deleted successfully.\n\n");
			printf("\n__________________\n\n");
			return first;
		}
	}
	printf("\n\nno such student founded.\n\n");
	printf("\n__________________\n\n");

	return first;
}

struct node *sortBy_ave(struct node *first) {

	if(first == NULL) {
		printf("\n\nlist is empty.\n\n");
		return first;
	}

	struct node *temp_i, *temp_j;
	int i, j, len;
	len = lenList(first);

	for(i = 0, temp_i = first; i < len - 1; temp_i = temp_i->next, i++) {
		for(j = i + 1, temp_j = temp_i->next; j < len; temp_j = temp_j->next, j++) {
			if(temp_i->st.average > temp_j->st.average) {
				struct student hold = temp_i->st;
				temp_i->st = temp_j->st;
				temp_j->st = hold;
			}
		}
	}

	return first;
}

struct node *file(struct node *first) {
	struct node *temp = first;
	if(first ==NULL) {
		printf("\n\nlist is empty\n\n");
		return first;
	}
	for(; temp != NULL ; temp = temp->next) {
		char filename[101];
		strcpy(filename, temp->st.id);
		strcat(filename, ".txt");
		FILE *fp = fopen(filename, "w+");

		if(fp == NULL) {
			printf("\n\nerror opening file.\n\n");
			return first;
		}

		fprintf(fp, "student name: ");
		fputs(temp->st.name, fp);
		fprintf(fp, "\nid: ");
		fputs(temp->st.id, fp);
		fprintf(fp, "\nthe average: ");
		fprintf(fp, "%.2f", temp->st.average);
		fflush(stdin);

		fclose(fp);
		fp = NULL;
		filename[0] = '\0';
	}

	return first;
}

void showById(struct node *first, char input_id[]) {
	struct node *temp = first;

	if(first == NULL) {
		printf("\n\nlist is empty.\n\n");
		return;
	}
	for(; temp != NULL; temp = temp->next) {
		if(strcmp(input_id, temp->st.id) == 0) {
			printf("\n\nstudent name: %s\nID: %s\nEnglish grade: %.2f  _  Math grade: %.2f  _  programming grade: %.2f\naverage: %.2f\n", temp->st.name, temp->st.id, temp->st.EnGrade, temp->st.mathGrade, temp->st.progGrade, temp->st.average);
			printf("\n_____________\n\n");
			return;
		}
	}

	printf("\n\nstudent did not found.");
	printf("\n_____________\n\n");

}

int main() {
	struct node *first = NULL;

	while(1) {
		int option;
		printf("select from the menue:\n1.add\n2.Delete By Id\n3.Average and file\n4.Show info by Id(u should do 3 before 4)\n5.exit\n\n");
		printf("option: ");
		scanf("%d", &option);
		fflush(stdin);

		switch(option) {
			case 1: {
				first = addEnd(first, create());
				first = sortBy_ave(first);
				break;
			}
			case 2: {
				char input_id[101];
				printf("\n\nenter th id of the student that u wanna delete: ");
				gets(input_id);

				first = DeleteById(first, input_id);
				break;
			}
			case 3: {
				if(first == NULL) {
					printf("\n\nlist is empty.\n\n");
					break;
				}
				first = ave(first);
				first = sortBy_ave(first);
				first = file(first);


				printf("\nDone\n\n_____________\n\n");
				break;
			}
			case 4: {
				char input_id[101];
				printf("\n\nenter the id: ");
				gets(input_id);
				showById(first, input_id);
				break;
			}
			case 5: {
				printf("\n\nexiting the program...\n\n");
				if(first != NULL) {
					while(first != NULL) {
						struct node *temp = first;
						first = first->next;
						free(temp);
					}
				}
				return 0;
			}
			default:
				printf("\npls select from the menue\n\n");
		}
	}

	return 0;
}
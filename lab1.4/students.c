#include<stdio.h>
#define SIZE 10

struct Student {
	int ID;
	char name[50];
	int age;
};

void strcopy(volatile char *dest, volatile char *source) {
	char data;
	do {
		data = *dest++ = *source++;
	} while (data);
}

struct Student students[SIZE];
int s_index = 0;

void Add(struct Student student){
	students[s_index] = student;
	s_index++;
}

void List(struct Student students[SIZE]){
	int i;
	for(i=0;i<SIZE;i++){
		printf("Name: %s, age: %d", students[i].name, students[i].age);
	}
}

void StudentsMain(){
	struct Student student0;
	student0.ID = 0;
	strcopy(student0.name, "Juan");
	student0.age = 20;
	struct Student student1;
	student1.ID = 1;
	strcopy(student0.name, "Raymond");
	student1.age = 30;
	Add(student0);
	Add(student1);
}

int main(){
	
	return 0;
}

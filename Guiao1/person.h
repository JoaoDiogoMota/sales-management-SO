#define FILENAME "file pessoas"

typedef struct Person{
	char name[200];
	int age;
}Person;

//Creates a new person
int new_person(char* name,int age);

//Change a person's age
int person_change_age(char* name, int age);

//Change a person's age 
int person_change_age_v2(long pos,int age);

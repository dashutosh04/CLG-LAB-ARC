/*
2. Write a C program to assign values to each member of the following structure. Pass the populated structure to a function Using call-by-value and another
function using call-by-address and print the value of each member of the
structure
*/

#include<stdio.h>


struct dob {
    int d, m, y;
};

struct student_info {
    int roll;
    char name[50];
    float cgpa;
    struct dob age;
};

void val(struct student_info s) {
    printf("\nBy Value:\nRoll: %d, Name: %s, CGPA: %.2f, DOB: %d/%d/%d\n", 
           s.roll, s.name, s.cgpa, s.age.d, s.age.m, s.age.y);
}

void addr(struct student_info *s) {
    printf("\nBy Address:\nRoll: %d, Name: %s, CGPA: %.2f, DOB: %d/%d/%d\n", 
           s->roll, s->name, s->cgpa, s->age.d, s->age.m, s->age.y);
}


int main(){
	struct student_info stud_1;

	printf("Enter the roll_no: \n");
	scanf("%d",&stud_1.roll);

	printf("Enter the name: \n");
	scanf("%s", stud_1.name);

	printf("Enter the cgpa: \n");
	scanf("%f", &stud_1.cgpa);
	
	stud_1.age.d = 1;
	stud_1.age.m = 2;
	stud_1.age.y = 2000;
	
	printf("Populated Structure.. \n");
	val(stud_1);
	addr(&stud_1);
}

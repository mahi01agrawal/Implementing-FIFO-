#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include<string.h>

int main()
{
	int fd,fd4,fd_ts1,fd_ts2;

	//(fd) named pipe between student1 and teacher for question
	//(fd4) named pipe between student2 and teacher for question
	//(fd_ts) named pipe between teacher and student
	char * myfifo = "/tmp/myfifo";
	char * myfifo1="/tmp/myfifo1";
	char * myfifo3="/tmp/myfifo3";
	char * myfifo4="/tmp/myfifo4";


	// Creating the named file in read and write mode
	mkfifo(myfifo, 0666);
	mkfifo(myfifo1,0666);
	mkfifo(myfifo3,0666);
	mkfifo(myfifo4,0666);

	char arr1[80], arr2[18],arr3[80],arr4[80];
	//constrains to store questions fetched from a file, answers from the students
	int i=0;
	int mark1=0,mark2=0,n=0;
	//marks of the student
	char answer[20];
	while (1)
	{
		//opening file in read only modes
		fd = open(myfifo, O_WRONLY);
		fd4 = open(myfifo1,O_WRONLY);

		//reading question from the text file
		FILE *f = fopen("questions.txt", "r");
		int k=i*20;
		fseek(f, k, SEEK_SET);
		fgets(arr2, 18,f);
		i++;
		fclose(f);


		// Writing the data into student interaction pipe
		write(fd, arr2, strlen(arr2)+1);
		write(fd4,arr2, strlen(arr2)+1);
		close(fd);
		close(fd4);
		fd_ts1 = open(myfifo3,O_RDONLY);
		fd_ts2 = open(myfifo4,O_RDONLY);

		read(fd_ts1, arr3, 80);
		printf("Student1 %s\n", arr3);
		close(fd_ts1);
		FILE *st1 = fopen("student1answers.txt", "w");
		int l=i*10;
		//fseek(st1, l, SEEK_SET);

		fputs(arr3,st1);
		fclose(st1);


		read(fd_ts2, arr4, 80);
		printf("Student2 %s\n", arr4);
		close(fd_ts2);
		FILE *st2 = fopen("student2answers.txt", "w");

		//fseek(st2, l, SEEK_SET);
		fputs(arr4,st2);
		fclose(st2);


		//switch case for selecting answers for the selected questions

		switch(i){
case1:
strcpy(answer,"Delhi");
break;
case 2:
strcpy(answer,"Agra");
break;
case 3:
strcpy(answer,"Bangalore");
default:
strcpy(answer,"null");
}
    //comparing the answers and updating the marks

    if(strcmp(arr3,answer)==0)
    mark1++;
    else if(strcmp(arr4,answer)==0)
    mark2++;
    else
    n++;
    //updating the marks into file
    FILE *f1 = fopen("marks1.txt", "w");
		putw(n, f1);
		fclose(f1);
		}
		return 0;
		}

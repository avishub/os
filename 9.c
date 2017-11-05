
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct Student {
  int roll;
  char name[100];
  float percentage;
}Student;

char *file_path;

void write_student(Student student) {

    int fd = open(file_path, O_WRONLY|O_APPEND);

    if(fd<0) {
       printf("\nError while writing to database");
       exit(0);
    } else {
       write(fd, &student, sizeof(student));
       printf("\n Written successfully!");
    }
    close(fd);

}

void read_student() {
    Student student;   
    int fd = open(file_path, O_RDONLY);
    if(fd<0) {
       printf("\nError while reading file");
       exit(0);
    } else {
       while(read(fd, &student, sizeof(student)))     
       printf("\nName: %s\nRoll Number: %d\nPercentage: %f\n", student.name, student.roll, student.percentage);     
    }

    close(fd);
}
void delete_student(int rno) {
    char *tmp = "temp";
    int flag = 0;
    Student student;   
    
    int fd1 = open(file_path, O_RDONLY);
    int fd2 = open(tmp, O_CREAT|O_WRONLY);   
    
    if(fd1<0) {
       printf("\nError while reading file");
       exit(0);
    } else {
       while(read(fd1, &student, sizeof(student))) {
         if(!(student.roll == rno)) 
            write(fd2, &student, sizeof(student));
		else {
			printf("\nRoll number %d deleted Successfully...", rno);
			flag = 1;
		}
       }     
    }
   
    if(flag == 0)
      printf("\nRecord not found!");
      
    remove(file_path);
    rename(tmp,file_path);

    close(fd1);
    close(fd2);   
}
void update_student(int rno) {
    char *tmp = "temp";
    int flag = 0;
    Student student;   
    Student tempstud;
    
    int fd1 = open(file_path, O_RDONLY);
    int fd2 = open(tmp, O_CREAT|O_WRONLY);   
    
    if(fd1<0) {
       printf("\nError while reading file");
       exit(0);
    } else {
       while(read(fd1, &student, sizeof(student))) {
         if(!(student.roll == rno)) 
            write(fd2, &student, sizeof(student));
		 else {
			printf("\nEnter the Roll Number, Name and Percentage\n");
            scanf("%d%s%f", &tempstud.roll, tempstud.name, &tempstud.percentage);
            write(fd2, &tempstud, sizeof(tempstud));
			printf("\nRoll number %d updated Successfully...", rno);
			flag = 1;
		 }
       }     
    }
   
    if(flag == 0)
      printf("\nRecord not found!");
      
    remove(file_path);
    rename(tmp,file_path);

    close(fd1);
    close(fd2);   
}
void search_student(int rno) {
   
    Student student;   
    int fd1 = open(file_path, O_RDONLY);
    int flag = 0;
    if(fd1<0) {
       printf("\nError reading file");
       exit(0);
    } else {
       while(read(fd1, &student, sizeof(student))) {
         if(student.roll == rno) {
             printf("\nName: %s\nRoll Number: %d\nPercentage: %f\n", student.name, student.roll, student.percentage);
             flag = 1;
         }
       }     
    }
   
    if(flag == 0)
       printf("\nRecord not Found!");
   
    close(fd1);
}

int main()
{
  Student student;
  int ch;
  int fd, r;
  char dname[20];

 
  while(1) {
      printf("\n1. Create database \n2. Insert Record \n3. Read Record \n4. Delete Record \n5. Search Record \n6. Udpate Record \n7. Exit \n>>") ;
      scanf("%d", &ch);

    switch(ch) {
      case 1:
           if(file_path)
           {
             printf("Database already created!");
             break;
           }
           file_path = "student.txt";
           int fd = open(file_path, O_CREAT);
           if(fd<0) {
             printf("\nError creating database");
             exit(0);
           } else {
             printf("\nDatabase created successfully!\n");
           }
           close(fd);
           break;
      case 2:
          printf("\nEnter the Roll Number, Name and Percentage\n");
          scanf("%d%s%f", &student.roll, student.name, &student.percentage);
          write_student(student);
          break;
      case 3:
          read_student();       
          break;
      case 4:
          printf("\nEnter roll no:");
          scanf("%d", &r);
          delete_student(r);
          break;
      case 5:
          printf("\nEnter roll no:");
          scanf("%d", &r);
          search_student(r);
          break;
      case 6:
          printf("\nEnter roll no:");
          scanf("%d", &r);
          update_student(r);
          break;
      case 7:
          exit(0)    ;         
      default:
          printf("\nInvalid Choce!");
    }
  }
  return 0;
}

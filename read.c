#include <stdio.h>
 #include<string.h>
int main()
{
int i;
 FILE *fp;
    fp =fopen ("marks.txt", "r");
      i= getw(fp);
      int k=0;
      printf ("marks of student 1 %d",i-1);

      printf ("marks of student 2 %d",++k);

      fclose(fp);

    return 0;
    }

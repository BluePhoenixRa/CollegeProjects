/*########################################################
Rahul Prithu
CSCI395: Digital Forensics
Lab 4

Description: Reads a binary file and changes the contents.
########################################################*/

#include<stdio.h>
#include<math.h> 

int main()
{
FILE *file1, *file2;
char fileIn[40], fileOut[40];
unsigned char c=0;

printf("Enter Input File Name: \t");
gets(fileIn);
file1=fopen(fileIn,"rb"); 
printf("Enter Output File Name: \t");
gets(fileOut);
file2=fopen(fileOut,"wb"); 

while (!feof(file1)){
   fread(&c,1,1,file1);
	if(c==0x7E){
		c=0x7F;
		printf("Data Modified!\n"); }
   fwrite(&c,1,1,file2);
   }

 fclose(file1); 
 fclose(file2); 
 printf("File Copying Completed!\n Bye!\n");
 return 0;
}

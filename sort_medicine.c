/*	I Pledge my Honor that I have not cheated, and will not cheat, on this assignment - Si Dang
	The program is using structured data types and the selection_sort function to sort the input contents from
	a file and output the results to another file has the same name with the input file plus an extension .srt
	Goals of this program are for practicing reading and writting files (I/O) in C and structure data type.	
	The program was wittern by Si Dang #U25273656 
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 100 /*maximine 100 medicines*/
#define MONTH 6 /*6 months period*/

//structure tag
struct medicine{
	char name[MAXLINE];
	int unitsInStock;
	int sixmth[MONTH];
	int total;
}; 

//function declaration
void selection_sort(struct medicine meds[], int n);

//main function
int main(void)
{
	FILE *fileR; /*file read mode pointer*/
	FILE *fileW; /*file write mode pointer*/
	char flr[MAXLINE]; /*file read*/
	char flw[MAXLINE]; /*file write*/
	int count = 0, line = 1;
	int i, j;
	
	struct medicine meds[MAXLINE]; /*structure tag called*/
	
	//prompt users type the file name
	printf("Enter the file name: ");
	scanf("%s", flr);
	
	printf("\n");
	
	fileR = fopen(flr, "r"); /*open the user's file in read mode*/
	if(fileR == NULL)/*checking valid file name*/
	{
		printf("Error! File has not found!\n");
		return 1;
	}	
	
	sprintf(flw, "%s.srt", flr); /*add .srt extension*/
	
	fileW = fopen(flw, "w");/*open file write*/
	if(fileW == NULL)/*checking valid file name*/
	{
		printf("Error! File has not found!\n");
		return 1;
	}
	
	while(!feof(fileR))/*if it is not reaches the end of the file*/
	{
		fscanf(fileR, "%s%d", meds[count].name, &meds[count].unitsInStock); /*counts lines from file and gets contents*/
		meds[count].total = 0;
		for(i = 0; i < MONTH; i++)
		{
			fscanf(fileR, "%d", &meds[count].sixmth[i]);
			meds[count].total += meds[count].sixmth[i];
			
		}
		count++;
	}
	
	selection_sort(meds, count);/*selection_sort function called*/
	fprintf(fileW, "#\t\t Name\t       InStock    Jan     Feb     Mar     Apr     May     Jun    Total\n");/*write the result to file write*/
	
	for(i = 1; i < count; i++)
	{
		fprintf(fileW, "%d      %15s\t\t%d\t", line, meds[i].name, meds[i].unitsInStock); /*write the result to file write*/
		for(j = 0; j < MONTH; j++)
		{
			fprintf(fileW, "  %d\t", meds[i].sixmth[j]); /*write the result to file write*/
		}
		fprintf(fileW, "  %d\n", meds[i].total); /*write the result to file write*/
		line++;
	}
	
	fclose(fileR); /*close file read*/
	fclose(fileW); /*close file write*/
	
	printf("\nThe result has been written to file: %s.srt.\n", flr);
	return 0;	
}

//selection_sort function was given
void selection_sort(struct medicine meds[], int n)
{
	int i, largest = 0; 
	struct medicine temp;
	if (n == 1)
		return;
	for (i = 1; i < n; i++)
		if (meds[i].total > meds[largest].total)/*we sort by using total collumn*/
			largest = i;
	if (largest < n - 1) 
	{
		temp = meds[n-1];
		meds[n-1] = meds[largest];
		meds[largest] = temp;
	}
	selection_sort(meds, n - 1);
}

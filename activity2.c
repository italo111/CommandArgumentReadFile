/*
	Student Name: Italo Peirano
	
	PID: 5660995

	Program Description: This program receives a text file in the command line 
	arguments. if in the command line argument has a s_flag, it will order
	the text in aschii order. If there is also a c_flag, then the program will
	count the amount of words present in the text file. If there is also a f_flag
	with an argument called fname, the  it will display the number of instances
	the string fname is repeated on the text file.
	
	Affirmation of Originality: "I affirm that I wrote this program myself without
	any help from any other people or sources from the internet."	 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int debug = 0;

int main(int argc, char **argv)
{
	extern char *optarg; /* special variable that gets the argument of a flag */
	extern int optind; /* number of arguments not counting argv[0] */
	int c, err = 0; 
	int cflag = 0, sflag = 0, fflag = 0; /* control flags for processing */
	static char usage[] = "usage: mywords [-s] [-c] [-f fname] file\n";
	char * fname;
	FILE * ptrFile; /* poinyrt to the file */
	char text[1000]; /* store the file text in this variable */ 	
	int size;
	int count = 0;
	/*	
	"scf:" means: "s" we have an s_flag, with no argument
	"c" we have an c_flag, with no argument
	"f" we have an f_flag, ":" with argument for f_flag
	*/
	while ((c = getopt(argc, argv, "scf:")) != -1)
		switch (c) {
		case 'c':
			cflag = 1;
			break;
		case 's':
			sflag = 1;
			break;
		case 'f':
			fflag = 1;
			fname = optarg;
			break;
		case '?':
			err = 1;
			break;
		}
 
	 if ((optind+1) > argc) {	
		/* 
 		need at least one argument (change +1 to +2 for two, etc. as needeed).
		if a flag is missing its corresponding argument an error message prints.
		*/
		printf("optind = %d, argc=%d\n", optind, argc);
		fprintf(stderr, "%s: missing name\n", argv[0]);
		fprintf(stderr, usage, argv[0]);
		exit(1);
	}
	else if (err) {
		fprintf(stderr, usage, argv[0]);
		exit(1);
	}

	
	if (optind < argc)
		/* these are the arguments, after the flags with their arguments */
		/* in other words we process the filename  taken from command line */
		for ( ; optind < argc; optind++){
			printf("argument: \"%s\"\n", argv[optind]);
			/* get a pointer to the file called ptrFile*/
			ptrFile = fopen(argv[optind], "r"); /* r means read mode */
			
			if(ptrFile == NULL){
				printf("Error while openning the file\n");
				exit(1);
			}
			int j = 0;
			while(!feof(ptrFile)){
				/* fgetc() gets a character from pointer ptrFile */
				text[j++] = fgetc(ptrFile);				
			}	
			text[j] = '\0'; /* add end of file */
			int i;
			size = j-1;
		
		}
	

	else {
		printf("no arguments left to process\n");
	}
	/* Processing of the command argument */
	if(sflag ==1){
		/* sorting text */
		int i;
		int j;
		char temp;
		char text2[1000];
		strcpy(text2,text);
		int temp2 = 0;
		for(i = 0; i < size-1; i++){
			for(j = i+1; j < size && temp2 == 0; j++){
				if(text2[j] == ' '|| text2[j] == '\n'){	
				temp2 = 1; /* act like a break */
				}
				else{	
					if(text2[i] > text2[j]){
						temp = text2[i];
						text2[i] = text2[j];
						text2[j] = temp;
					}
				}
				
			}
			temp2 = 0;			
		}
		printf("The text in the file \"%s\" will be displayed in aschii code order: \n",argv[argc-1]);
		for(i = 0; i< size; i++){
			printf("%c",text2[i]);
		}
		printf("\n");
	}
	if(cflag == 1){
		/* count number of words */
		int i;
		int state = 0;
		for(i = 0; i < size; i++){
			if((text[i] != ' ' || text[i] != '\n' || text[i] != '\t' )&&(state == 0)){
				state = 1;
				count++;
			}
			else if((text[i] == ' ' || text[i] == '\n' || text[i] == '\t')&& (state == 1)){
				state = 0;
			}
		}
		printf("Number of words on the file \"%s\" = %d\n", argv[argc - 1],count);
	}
	
	if(fflag == 1){
		/* number of instances of the string fname */
		char * ptr1 = text;
		
		int length = strlen(fname);
		int countp = 0;
		if(length){
			while(ptr1 != NULL){
		
				ptr1 += length;
				/* returns a pointer to first instance of fname in ptr1 */
				ptr1 = strstr(ptr1,fname);  
				countp++;
			}
	
		printf("Number of instances of the word \"%s\"      = %d\n",fname,countp);
		}	

	}
	if(sflag == 0 && cflag == 0 && fflag == 0){
		int i;
		printf("Here is the text of the file \"%s\" :\n",argv[argc-1]);
		for(i = 0; i < size; i++){
			printf("%c",text[i]);
		}
		printf("\n");
	}
	exit(0);
}

// FILE        : encodeInput.c
// PROJECT     : Binary to Assembly/S-Record Converter
// PROGRAMMER  : Vu Quang Minh - 8905836
// FIRST VERSION : 12/2/2025
// DESCRIPTION : This file contains the main implementation for reading a binary file
//               or standard input and converting it into either Assembly format or
//               S-Record format based on user arguments.
#include "../inc/encodeInput.h"
#include "../inc/ASM.h"
#include "../inc/SREC.h"
int main(int argc,char*argv[]){
	char *inputFileName=NULL;
	char *outputFileName=NULL;
	int srecMode=0;
	FILE *fin=NULL;
	FILE *fout=NULL;
	char buffer[1024];
	int totalBytes=0;
	processArgument(argc,argv,&inputFileName,&outputFileName,&srecMode);
	if(inputFileName !=NULL){
		fin =fopen(inputFileName,"rb");
		if(!fin){
			perror("ERROR:Can't open input file");
			return 1;
		}
	}else{
		fin = stdin;
	}
	if(outputFileName!=NULL){
		fout = fopen(outputFileName,"w");
		if(!fout){
			perror("ERROR:Can't open output file");
			if(fclose(fin)!=0){// close the input file to prevent resource leaks
			perror("ERROR: Can't close input file");
			exit(1);
			}
			return 1;
		}
	}else{
		fout = stdout;
	}
	totalBytes=readFile(fin,buffer,totalBytes,sizeof(buffer));

	if(srecMode==1){
		generateSrec(fout,buffer,totalBytes);
	}else{
		for (int i = 0; i < totalBytes; i += 16) {
        int count = (totalBytes - i < 16) ? 
                    (totalBytes - i) : 16;
					generateAsm(fout,&buffer[i],count);
					}
	}
	if(fin !=stdin){
		if(fclose(fin)!=0){
		perror("ERROR:Can't close input file");
		return 1;
		}
	}
	if(fout !=stdout){
		if(fclose(fout)!= 0){
		perror("ERROR:Can't close output file");
		return 1;
		}
	}
	return 0;
}
// FUNCTION    : processArgument
// DESCRIPTION : Processes command-line arguments and extracts input and output file names
// PARAMETERS  : int argc - Number of command-line arguments
//               char *argv[] - Array of command-line arguments
//               char **inputFileName - Pointer to store input file name
//               char **outputFileName - Pointer to store output file name
//               int *srecMode - Flag indicating if S-Record mode is enabled
// RETURN      : NONE
void processArgument(int argc,char*argv[],char **inputFileName,char **outputFileName, int *srecMode){
	for(int i=1;i <argc;i++){
		if(argv[i][0]=='-'){
			switch (argv[i][1]){
				case 'i' :
					*inputFileName = &argv[i][2];
					break;
				case 'o' :
					*outputFileName =&argv[i][2];
					break;
				case 's' :
					if (strcmp(argv[i],"-srec")==0){
						*srecMode = 1;
					}
					else{
						printUsage();
						exit(1);
					}
					break;
				case 'h' :
					printUsage();
					exit(0);
				default:
					printUsage();
					exit(1);
			}
		}
		else{
			printUsage();
			exit(1);
		}
	}
	if (*inputFileName && !*outputFileName) {
        char *autoFileName = malloc(strlen(*inputFileName) + 6);  
        strcpy(autoFileName, *inputFileName);
        strcat(autoFileName, *srecMode ? ".srec" : ".asm");
        *outputFileName = autoFileName;
    }
}
// FUNCTION    : printUsage
// DESCRIPTION : Prints the usage instructions for the program
// PARAMETERS  : NONE
// RETURN      : NONE
void printUsage(){
	printf("Usage: encodeInput Read and output the result in standard output\n");
	printf("Usage: encodeInput -i<<inputFileName>> -o<<outputFileName>> -srec   Convert input file to output file as an S-Record\n");
	printf("Usage: encodeInput -h Show the usage statement and exit\n");
	printf("Usage: encodeInput -o<<outputFileName>>  take the piped standard input and format it into Assemble format and write it inside output file\n");
	printf("Usage: encodeInput -srec -i<<inputFileName>> Convert input file to S-Record format\n");
	printf("Usage: ls -l | encodeInput -o<<outputFileName>> -srec  take the piped standard input and format it into S-Record format and write it inside output file\n");
}
// FUNCTION    : readFile
// DESCRIPTION : Reads binary input from a file and stores it in a buffer
// PARAMETERS  : FILE *fin - Input file pointer
//               char *buffer - Buffer to store read data
//               int totalBytes - Current total bytes read
//               int bufferSize - Maximum buffer size
// RETURN      : int - Total bytes read
int readFile(FILE *fin,char *buffer,int totalBytes,int bufferSize){
	while(!feof(fin)){
		int readBytes =fread(&buffer[totalBytes],1,bufferSize,fin);
		if(readBytes<=0){
			break;
		}
		totalBytes+=readBytes;

		if(totalBytes >= bufferSize){
			break;
		}
	}
	return totalBytes;
}
#include "../inc/encodeInput.h"
int main(int argc,char*argv[]){
	char *inputFileName=NULL;
	char *outputFileName=NULL;
	int srecMode=1;
	FILE *fin=NULL;
	FILE *fout=NULL;
	char buffer[1024];
	int totalBytes;
	return 0;
}

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
					if (strcmp(argv[i],"-srec")){
						srecMode = 1;
					}
					else{
						printUsage();
						exit(1);
					}
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
}

void printUsage(){
	printf("Usage: encodeInput Read and output the result in standard output\n");
	printf("Usage: encodeInput -i<<inputFileName>> -o<<outputFileName>> -srec   Convert input file to output file as an S-Record\n");
	printf("Usage: encodeInput -h Show the usage statement and exit\n");
	printf("Usage: encodeInput -o<<outputFileName>>  take the piped standard input and format it into Assemble format and write it inside output file\n");
	printf("Usage: encodeInput -srec -i<<inputFileName>> Convert input file to S-Record format\n");
	printf("Usage: ls -l | encodeInput -o<<outputFileName>> -srec  take the piped standard input and format it into S-Record format and write it inside output file\n");
}
#include "../inc/encodeInput.h"
int main(int argc,char*argv[]){
	char *inputFileName=NULL;
	char *outputFileName=NULL;
	int srecMode=1;
	FILE *fin=NULL;
	FILE *fout=NULL;
	char buffer[1024];
	int totalBytes;
	processArgument(argc,argv,&inputFileName,&outputFileName,srecMode);
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
	totalBytes=readFile(fin,buffer,sizeof(buffer));

	if(srecMode==1){

	}
	if(fin !=stdin){
		if(fclose(fin)!=0){
		perror("ERROR:Can't close input file");
		return;
		}
	}
	if(fout !=stdout){
		if(fclose(fout)!= 0){
		perror("ERROR:Can't close output file");
		return;
		}
	}
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
	
}
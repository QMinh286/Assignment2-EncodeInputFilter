#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#pragma warning(disable:4996)
void processArgument(int argc,char*argv[],char **inputFileName,char **outputFileName, int *srecMode);
void printUsage();
int readFile(FILE *fin,char *buffer,int totalBytes,int bufferSize);
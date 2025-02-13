// Header File
// FILE		:encodeInput.h
// PROJECT	:encodeInput Ultility
// PROGRAMMER	:Vu Quang Minh-8905836
// FIRST VERSION:12/2/2025
// DESCRIPTION	:TThis is the header file for the encodeInput program. It contains
//             function prototypes for processing command-line arguments,
//              file handling, and utility functions for data conversion between
//              binary and various output formats (Assembly and S-Record).
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#pragma warning(disable:4996)

//PROTOTYPES
void processArgument(int argc,char*argv[],char **inputFileName,char **outputFileName, int *srecMode);
void printUsage();
int readFile(FILE *fin,char *buffer,int totalBytes,int bufferSize);
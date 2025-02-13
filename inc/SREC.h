#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#pragma warning(disable:4996)
#define NAME "MINH"
void generateSrec(FILE *fout,unsigned char* data,int totalBytes);
static unsigned char checkSum(unsigned char* data, int count) ;
//
 //file        ASM.h
 //PROJECT     encodeInput Utility
 //PROGRAMMER  Vu Quang Minh-8905836
 //DATE        12/2/2025
 //DESCRIPTION This header file contains the function prototype for generating
 //             assembly format output. The assembly format converts binary data
 //             into a series of dc.b (define constant byte) assembly instructions.
 //
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#pragma warning(disable:4996)
//PROTOTYPE
void generateAsm(FILE* fout, unsigned char* data, int count);
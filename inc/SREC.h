//
//FILE        SREC.h
//PROJECT     cryptoMagic Utility
//PROGRAMMER  Vu Quang Minh-8905836
//DATE        12/2/2025
//DESCRIPTION This header file contains function prototypes and definitions for
//              generating Motorola S-Record format output. S-Records are used in
//              embedded development for transferring data between systems and
//              programming EPROM devices.
//
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#pragma warning(disable:4996)
#define NAME "MINH"
void generateSrec(FILE *fout,unsigned char* data,int totalBytes);
static unsigned char checkSum(unsigned char* data, int count) ;
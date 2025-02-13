// FILE        : SREC.c
// PROJECT     : encodeInput
// PROGRAMMER  : Vu Quang Minh - 8905836
// FIRST VERSION :12/2/2025
// DESCRIPTION : This file contains the implementation of functions that
//               generate Motorola S-Record formatted output from binary data.
#include "../inc/SREC.h"
// FUNCTION    : generateSrec
// DESCRIPTION : Generates an S-Record formatted output from binary data
// PARAMETERS  : FILE *fout - Output file pointer where the S-Record is written
//               unsigned char *data - Input binary data buffer
//               int totalBytes - Total number of bytes in the input buffer
// RETURN      : NONE
void generateSrec(FILE *fout,unsigned char* data,int totalBytes){
    int address =0;
    int count =0;
    int nameLen = strlen(NAME);
    fprintf(fout,"S0%02X0000",nameLen+3);
    for(int i =0;i<nameLen;i++){
        fprintf(fout,"%02X",NAME[i]);
    }
    unsigned char headerSum = checkSum((unsigned char*)NAME,nameLen);
    fprintf(fout,"%02X",headerSum);
    fprintf(fout,"\n");

    for (int i = 0; i < totalBytes; i += 16) {
        int count = (totalBytes - i < 16) ? 
                    (totalBytes - i) : 16;
        
        
        fprintf(fout, "S1%02X%04X", count + 3, address);
        
        unsigned int sum = 0;  
        for (int j = 0; j < count; j++) {
            fprintf(fout, "%02X", data[i + j]);
            sum += data[i + j];
        }
        
        fprintf(fout, "%02X\n", ~(sum & 0xFF));
        
        address += count;
        count++;
    }

    fprintf(fout, "S503%04X%02X\n", count, ~(count & 0xFF));

    fprintf(fout, "S9030000FC\n");
}
// FUNCTION    : checkSum
// DESCRIPTION : Computes the checksum for a given data buffer
// PARAMETERS  : unsigned char *data - Pointer to the data buffer
//               int count - Number of bytes in the buffer
// RETURN      : unsigned char - Computed checksum
static unsigned char checkSum(unsigned char* data, int count) {
    unsigned int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += data[i];
    }
    return ~(sum & 0xFF);
}
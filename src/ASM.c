// FILE        : ASM.c
// PROJECT     : Assembly Data Generator
// PROGRAMMER  : Vu Quang Minh - 8905836
// FIRST VERSION :12/2/2025s
// DESCRIPTION : This file contains the implementation of a function that
//               generates assembly-formatted data statements from binary input.
#include "../inc/ASM.h"

// FUNCTION    : generateAsm
// DESCRIPTION : Generates an assembly data declaration (dc.b) for the given data
// PARAMETERS  : FILE *fout - Output file pointer where the assembly code is written
//               unsigned char *data - Input binary data buffer
//               int count - Number of bytes in the input buffer
// RETURN      : NONE
void generateAsm(FILE* fout, unsigned char* data, int count) {
    
    fprintf(fout, "dc.b\t");
    for (int i = 0; i < count; i++) {
        fprintf(fout, "$%02X", data[i]);
        if (i < count - 1) fprintf(fout, ", ");
    }
    fprintf(fout, "\n");
}
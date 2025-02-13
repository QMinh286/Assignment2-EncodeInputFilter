#include "../inc/ASM.h"
void writeAssemblyOutput(FILE* fout, unsigned char* data, int count) {
    
    fprintf(fout, "dc.b\t");
    for (int i = 0; i < count; i++) {
        fprintf(outFile, "$%02X", data[i]);
        if (i < count - 1) fprintf(fout, ", ");
    }
    fprintf(fout, "\n");
}
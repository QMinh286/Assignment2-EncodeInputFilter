#include "../inc/ASM.h"
void generateAsm(FILE *fin, FILE *fout) {
    char buffer[16];
    int bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), fin)) > 0) {
        fprintf(fout, "dc.b");
        for (int i = 0; i < bytes_read; i++) {
            fprintf(fout, " $%02X", buffer[i]);
            if (i < bytes_read - 1) fprintf(fout, ",");
        }
        fprintf(fout, "\n");
    }
}
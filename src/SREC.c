#include "../inc/SREC.h"

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

    for (i = 0; i < totalBytes; i += 16) {
        int count = (totalBytes - i < 16) ? 
                    (totalBytes - i) : 16;
        
        // Calculate record length (count + 2 address bytes + 1 checksum byte)
        fprintf(fout, "S1%02X%04X", count + 3, address);
        
        // Write data bytes
         sum = 0;  // Reset sum for checksum calculation
        for (int j = 0; j < count; j++) {
            fprintf(fout, "%02X", data[i + j]);
            sum += data[i + j];
        }
        
        // Print checksum
        fprintf(fout, "%02X\n", ~(sum & 0xFF));
        
        address += count;
        count++;
    }

    // Write S5 (record count) record
    fprintf(fout, "S503%04X%02X\n", count, ~(count & 0xFF));

    // Write S9 (end) record
    fprintf(fout, "S9030000FC\n");
}
static unsigned char checkSum(unsigned char* data, int count) {
    unsigned int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += data[i];
    }
    return ~(sum & 0xFF);
}
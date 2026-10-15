#include <stdio.h>
#include <stdlib.h>

const char b64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }

    FILE *fp = fopen(argv[1], "rb");

    // Looking at individual binary values
    unsigned char chunk[3];
    size_t bytes;

    while ((bytes = fread(chunk, 1, 3, fp)) > 0) {
        unsigned int block = 0;
        
        if (bytes == 3) {
            block = (chunk[0] << 16) | (chunk[1] << 8) | chunk[2];
            putchar(b64_table[(block >> 18) & 0x3F]);
            putchar(b64_table[(block >> 12) & 0x3F]);
            putchar(b64_table[(block >> 6)  & 0x3F]);
            putchar(b64_table[block         & 0x3F]);
        } 
        else if (bytes == 2) {
            block = (chunk[0] << 16) | (chunk[1] << 8);
            putchar(b64_table[(block >> 18) & 0x3F]);
            putchar(b64_table[(block >> 12) & 0x3F]);
            putchar(b64_table[(block >> 6)  & 0x3F]);
            putchar('=');
        } 
        else if (bytes == 1) {
            block = (chunk[0] << 16);
            putchar(b64_table[(block >> 18) & 0x3F]);
            putchar(b64_table[(block >> 12) & 0x3F]);
            putchar('=');
            putchar('=');
        }
    }

    fclose(fp);
    return 0;
}

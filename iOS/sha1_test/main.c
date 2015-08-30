#include <stdlib.h>
#include <stdio.h>
#include "lsh_benchmark.h"
#include "lsh160_generic.h"
#include "lsh256_generic.h"
#include "lsh512_generic.h"

void lsh_reference_benchmark(){
    printf("\nLSH Benchmark result:\n\n");

    lsh160_benchmark(160, 8);
    lsh160_benchmark(160, 64);
    lsh160_benchmark(160, 512);
    lsh160_benchmark(160, 1536);
    lsh160_benchmark(160, 4096);
    lsh160_benchmark(160, 1000000);

//    lsh256_benchmark(256, 8* 8);
//    lsh256_benchmark(256, 64* 8);
//    lsh256_benchmark(256, 576* 8);
//    lsh256_benchmark(256, 1536 * 8);
//    lsh256_benchmark(256, 4096 * 8);
//    lsh256_benchmark(256, 1000000*8);
    
    printf("End of Lsh Reference Benchmark");
    
    return;
}

void lsh_testvector(int maxhashbitlen, int hashbitlen){

	int i, k;
	
	int datalen; //the size of the message in bytes
	Byte data[256 * 4];
	Byte hash[64];
	int databitlen256[16] = { 0, 1, 2, 7, 8, 15, 16, 1023, 1024, 1025, 1024 * 2 - 1, 1024 * 2, 1024 * 2 + 1, 1024 * 3 - 1, 1024 * 3, 1024 * 3 + 1 };
	int databitlen512[16] = { 0, 1, 2, 7, 8, 15, 16, 2047, 2048, 2049, 2048 * 2 - 1, 2048 * 2, 2048 * 2 + 1, 2048 * 3 - 1, 2048 * 3, 2048 * 3 + 1 };

	for (i = 0; i < 256 * 4; ++i)
		data[i] = (u8)i;

    if (maxhashbitlen == 160){
            printf("\nTest Vector for LSH-%d-%d\n\n", maxhashbitlen, hashbitlen);
            for (i = 0; i < 16; i++) {
                printf("\nInput Message Length in Bits:%d\n", databitlen256[i]);
                printf("\nInput Message:\n");
                datalen = (databitlen256[i] / 8) + ((databitlen256[i] & 0x7) ? 1 : 0);
                for (k = 0; k < datalen; k++) {
                    printf("%02x", data[k]);
                    if ((k % 64) == 63) printf("\n");
                }
                printf("\n");
                
                Hash160(hashbitlen, data, databitlen256[i], hash);
                printf("\nHash Value:\n");
                for (k = 0; k<hashbitlen / 8; k++)
                    printf("%02x", hash[k]);
                printf("\n\n");
            }
    }
    else
        if (maxhashbitlen == 256){
		if ((hashbitlen == 224) || (hashbitlen == 256)){
			printf("\nTest Vector for LSH-%d-%d\n\n", maxhashbitlen, hashbitlen);
			for (i = 0; i < 16; i++) {
				printf("\nInput Message Length in Bits:%d\n", databitlen256[i]);
				printf("\nInput Message:\n");
				datalen = (databitlen256[i] / 8) + ((databitlen256[i] & 0x7) ? 1 : 0);
				for (k = 0; k < datalen; k++) {
					printf("%02x", data[k]);
					if ((k % 64) == 63) printf("\n");
				}
				printf("\n");

				Hash256(hashbitlen, data, databitlen256[i], hash);
				printf("\nHash Value:\n");
				for (k = 0; k<hashbitlen / 8; k++)
					printf("%02x", hash[k]);
				printf("\n\n");
			}
		}

		else{
			printf("Invalid hashbitlen.\n");
			return;
		}
	}

	else if (maxhashbitlen == 512){
		if ((hashbitlen == 224) || (hashbitlen == 256) || (hashbitlen == 384) || (hashbitlen == 512)){
			printf("\nTest Vector for LSH-%d-%d\n\n", maxhashbitlen, hashbitlen);
			for (i = 0; i < 16; i++) {
				printf("\nInput Message Length in Bits:%d\n", databitlen512[i]);
				printf("\nInput Message:\n");
				datalen = (databitlen512[i] / 8) + ((databitlen512[i] & 0x7) ? 1 : 0);
				for (k = 0; k < datalen; k++) {
					printf("%02x", data[k]);
					if ((k % 64) == 63) printf("\n");
				}
				printf("\n");

				Hash512(hashbitlen, data, databitlen512[i], hash);
				printf("\nHash Value:\n");
				for (k = 0; k<hashbitlen / 8; k++)
					printf("%02x", hash[k]);
				printf("\n\n");
			}

		}

		else{
			printf("Invalid hashbitlen.\n");
			return;
		}
	}

	else{
		printf("Invalid maxhashbitlen.\n");
	}

	return;
}

int main(){
//	lsh_testvector(512, 512);
//	lsh_testvector(256, 256);
    lsh_reference_benchmark();
//    lsh160_benchmark(160, 160);
//    lsh160_benchmark(160, 0x1000000);
//    lsh256_benchmark(256, 1000000);
//    lsh512_benchmark(512, 512);
}

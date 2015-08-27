#include <stdio.h>
#include <stdlib.h>

#include "lsh_benchmark.h"
#include "lsh160_generic.h"
#include "benchmark.h"

void lsh160_benchmark(int hashbitlen, int databitlen)
{
    unsigned int calibration, tMin = 0xFFFFFFFF, t0, t1;
    int i;
    int sample_count;
    
    unsigned char hashval160[32];
    unsigned char data[TEST_MESSAGE_SIZE];
    
    if ((databitlen & 0x7) || (databitlen > (TEST_MESSAGE_SIZE << 3))){
        printf("databitlen must be a multiple of 8 and less than %d\n", TEST_MESSAGE_SIZE << 3);
        return;
    }
    
    calibration = calibrate();
    
    printf("LSH-160-%d, %8d-bit messages: ", hashbitlen, databitlen);
    
    for(sample_count = 0; sample_count < TEST_MESSAGE_SAMPLE_COUNT; sample_count++)
    {
        tMin = 0xFFFFFFFF;
        
        for (i=0; i<TIMER_SAMPLE_CNT;i++)  /* calibrate the overhead for measuring time */
        {
            t0 = HiResTime();
            
            /*	function for test	*/
            //Hash256(256,data, databitlen, hashval256);
            Hash160(hashbitlen ,data, databitlen, hashval160);
            /*	function for test	*/
            
            t1 = HiResTime();
            
            if (tMin > t1 - t0 - calibration)       /* keep only the minimum time */
                tMin = t1 - t0 - calibration;
        }
    }
    printf("%7.2f cycles/byte\n", get_cpb(tMin, databitlen>>3));
}

//void lsh256_benchmark(int hashbitlen, int databitlen)
//{
//	unsigned int calibration, tMin = 0xFFFFFFFF, t0, t1;
//	int i;
//	int sample_count;	
//
//	unsigned char hashval256[32];
//	unsigned char data[TEST_MESSAGE_SIZE];
//	
//	if ((databitlen & 0x7) || (databitlen > (TEST_MESSAGE_SIZE << 3))){
//		printf("databitlen must be a multiple of 8 and less than %d\n", TEST_MESSAGE_SIZE << 3);
//		return;
//	}	
//
//	calibration = calibrate();
//
//	printf("LSH-256-%d, %8d-bit messages: ", hashbitlen, databitlen);
//
//	for(sample_count = 0; sample_count < TEST_MESSAGE_SAMPLE_COUNT; sample_count++)
//	{
//		tMin = 0xFFFFFFFF;
//
//		for (i=0; i<TIMER_SAMPLE_CNT;i++)  /* calibrate the overhead for measuring time */
//		{
//			t0 = HiResTime();
//
//			/*	function for test	*/				
//			//Hash256(256,data, databitlen, hashval256);
//			Hash256(hashbitlen ,data, databitlen, hashval256);
//			/*	function for test	*/
//
//			t1 = HiResTime();
//
//			if (tMin > t1 - t0 - calibration)       /* keep only the minimum time */
//					tMin = t1 - t0 - calibration;
//		}
//	}
//	printf("%7.2f cycles/byte\n", get_cpb(tMin, databitlen>>3));
//
//}
//
//
//void lsh512_benchmark(int hashbitlen, int databitlen)
//{
//	unsigned int calibration, tMin = 0xFFFFFFFF, t0, t1;
//	int i;
//	int sample_count;
//
//	unsigned char hashval512[64];
//	unsigned char data[TEST_MESSAGE_SIZE];
//
//	if ((databitlen & 0x7) || (databitlen > (TEST_MESSAGE_SIZE << 3))){
//		printf("databitlen must be a multiple of 8 and less than %d\n", TEST_MESSAGE_SIZE << 3);
//		return;
//	}
//
//	calibration = calibrate();
//
//	printf("LSH-512-%d, %8d-bit messages: ",hashbitlen, databitlen);
//
//	for (sample_count = 0; sample_count < TEST_MESSAGE_SAMPLE_COUNT; sample_count++)
//	{
//		tMin = 0xFFFFFFFF;
//
//		for (i = 0; i<TIMER_SAMPLE_CNT; i++)  /* calibrate the overhead for measuring time */
//		{
//			t0 = HiResTime();
//
//			/*	function for test	*/
//			//Hash512(512, data, databitlen, hashval512);
//			Hash512(hashbitlen, data, databitlen, hashval512);
//			/*	function for test	*/
//
//			t1 = HiResTime();
//
//			if (tMin > t1 - t0 - calibration)       /* keep only the minimum time */
//				tMin = t1 - t0 - calibration;
//		}
//	}
//	printf("%7.2f cycles/byte\n", get_cpb(tMin, databitlen >> 3));
//
//}
//



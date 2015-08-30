///*
// * hmac_test.c
// *
// * Version 1.0.0
// *
// * Written by Aaron D. Gifford <me@aarongifford.com>
// *
// * Copyright 1998, 2000 Aaron D. Gifford.  All rights reserved.
// *
// * Redistribution and use in source and binary forms, with or without
// * modification, are permitted provided that the following conditions
// * are met:
// * 1. Redistributions of source code must retain the above copyright
// *    notice, this list of conditions and the following disclaimer.
// * 2. Redistributions in binary form must reproduce the above copyright
// *    notice, this list of conditions and the following disclaimer in the
// *    documentation and/or other materials provided with the distribution.
// * 3. Neither the name of the copyright holder nor the names of contributors
// *    may be used to endorse or promote products derived from this software
// *    without specific prior written permission.
// * 
// * THIS SOFTWARE IS PROVIDED BY THE AUTHOR(S) AND CONTRIBUTORS ``AS IS'' AND
// * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR(S) OR CONTRIBUTORS BE LIABLE
// * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// * SUCH DAMAGE.
// */
//
///*
// * This program is just a test program for making sure that the HMAC-SHA1
// * library code correctly meets RFC 2202's test vectors.  Here's how I
// * compile it on my FreeBSD 4.0 system:
// *
// *   cc -o hmac_test hmac_test.c hmac_sha1.c sha1.c
// *
// * OR when using the version of SHA1 in FreeBSD's libmd(Eric A. Young's
// * implementation):
// *
// *   cc -o hmac_test hmac_test.c hmac_sha1.c -lmd
// *
// * Then run the test from the command line:
// *
// *   ./hmac_test
// */
//
//#include <stdio.h>
//#include <stdlib.h>
//
//#include "benchmark.h"
//#include "hmac_sha1.h"
//
//typedef struct _test_vector {
//	int		caseno;
//	int		keylen;
//	unsigned char	*key;
//	int		datalen;
//	unsigned char	*data;
//	unsigned char	*digest;
//} test_vector;
//
//unsigned char tolower_hmac(unsigned char c) {
//	if (c >= (unsigned char)'A' && c <= (unsigned char)'A')
//		return c + ((unsigned char)'a' - (unsigned char)'A');
//	return c;
//}
//
//unsigned char hexdigit(unsigned char c) {
//	c = tolower_hmac(c);
//	if (c >= (unsigned char)'a' && c <= (unsigned char)'f')
//		c += (10 - (unsigned char)'a');
//	else
//		c += (0 - (unsigned char)'0');
//	return c;
//}
//	
//unsigned char *hex2data(unsigned char *hex, int len) {
//	unsigned char	*data;
//	int		dl;
//	unsigned int	c;
//
//	/* Assume the hex data ALWAYS begins with "0x" */
//	hex += 2;
//
//	/* Allocate space... */
//	data = (unsigned char *)malloc(sizeof(unsigned char) * len);
//
//	for (dl = 0; dl < len; dl++) {
//		c = (unsigned int)hexdigit(*hex++) << 4;
//		c |= (unsigned int)hexdigit(*hex++);
//		data[dl] = (unsigned char)c;
//	}
//	
//	return data;
//}
//
//int main(void) {
//        int             i, p, j;
//        HMAC_SHA1_CTX   c;
//        unsigned char   md[HMAC_SHA1_DIGEST_LENGTH];
//        unsigned int    calibration, tMin = 0xFFFFFFFF, t0, t1;
//        double cpbcheck;
//	test_vector	tests;
//
//	/* Set up the test vectors from RFC 2202 */
////	tests[0].caseno = 1;
////	tests[0].key = (unsigned char*)"sha";
////	tests[0].keylen = 3;
////	tests[0].datalen = 8;
////	tests[0].digest = hex2data((unsigned char*)"0xb617318655057264e28bc0b6fb378c8ef146be00", 20);
////
////	tests[1].caseno = 2;
////	tests[1].keylen = 3;
////	tests[1].key = (unsigned char*)"sha";
////	tests[1].datalen =  64;
////	tests[1].digest = hex2data((unsigned char*)"0xeffcdf6ae5eb2fa2d27416d5f184df9c259a7c79", 20);
////
////	tests[2].caseno = 3;
////	tests[2].keylen = 3;
////	tests[2].key = (unsigned char*)"sha";
////	tests[2].datalen = 576;
////	tests[2].digest = hex2data((unsigned char*)"0x125d7342b9ac11cd91a39af48aa17b4f63f175d3", 20);
////
////	tests[3].caseno = 4;
////	tests[3].keylen = 3;
////	tests[3].key = (unsigned char*)"sha";
////	tests[3].datalen = 1536;
////	tests[3].digest = hex2data((unsigned char*)"0x4c9007f4026250c6bc8414f9bf50c86c2d7235da", 20);
////
////	tests[4].caseno = 5;
////	tests[4].keylen = 3;
////	tests[4].key = (unsigned char*)"sha";
////	tests[4].datalen = 4096;
////	tests[4].digest = hex2data((unsigned char*)"0x4c1a03424b55e07fe7f27be1d58bb9324a9a5a04", 20);
//
//	tests.caseno = 6;
//	tests.keylen = 3;
//	tests.key = (unsigned char*)"sha";
//	tests.datalen = 1000000;
//	tests.digest = hex2data((unsigned char*)"0xaa4ae5e15272d00e95705637ce8a3b55ed402112", 20);
//
////	tests[6].caseno = 7;
////	tests[6].keylen = 80;
////	tests[6].key = hex2data((unsigned char*)"0xaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 80);
////	tests[6].datalen = 73;
////	tests[6].data = (unsigned char*)"Test Using Larger Than Block-Size Key and Larger Than One Block-Size Data";
////	tests[6].digest = hex2data((unsigned char*)"0xe8e99d0f45237d786d6bbaa7965c7808bbff1a91", 20);
//
//    calibration= calibrate();
//	/* Now do the tests */
////	for (i = 0; i < 6; i++) {
//        tests.data= (unsigned char*)malloc(sizeof(unsigned char)*tests.datalen);
//        for(j=0; j<tests.datalen; j++) tests.data[j]=(unsigned char)(j%sizeof(unsigned char)*8);
//		printf("Test vector #%d:\n", tests.caseno);
//        
//        tMin = 0xFFFFFFFF;
//        for(j=0; j<50000; j++){
//            t0= HiResTime();
//            HMAC_SHA1_Init(&c);
//            /* Send the first 3 bytes of key */
//            HMAC_SHA1_UpdateKey(&c, tests.key, 3);
//            HMAC_SHA1_UpdateKey(&c, &(tests.key[3]), tests.keylen - 3);
//            HMAC_SHA1_EndKey(&c);
//            HMAC_SHA1_StartMessage(&c);
//            /* Send the first 7 bytes of data */
//            HMAC_SHA1_UpdateMessage(&c, tests.data, 7);
//            HMAC_SHA1_UpdateMessage(&c, &(tests.data[7]), tests.datalen - 7);
//            HMAC_SHA1_EndMessage(&(md[0]),&c);
//            t1= HiResTime();
//            if(tMin > t1-t0-calibration)
//                tMin= t1-t0-calibration;
//        }
//        
//        printf("%d byte length message :: %7.2f cpb\n", tests.datalen, get_cpb(tMin, tests.datalen>>3));
//        free(tests.data);
////        printf("Message Digest Was: \"0x");
////		for (p = 0; p < HMAC_SHA1_DIGEST_LENGTH; p++)
////			printf("%02x", (unsigned char)md[p]);
////		printf("\"\nExpected: \"0x");
////		for (p = 0; p < HMAC_SHA1_DIGEST_LENGTH; p++)
////			printf("%02x", (unsigned char)tests[i].digest[p]);
////		printf("\"\n");
////		for (p = 0; p < HMAC_SHA1_DIGEST_LENGTH; p++) {
////			if (tests[i].digest[p] != md[p]) {
////				printf("TEST FAILED (at byte %d)!!!\n", p);
////				printf("'0x%02x' != '0x%02x' apparently...\n", (unsigned char)tests[i].digest[p], (unsigned char)md[p]);
////				break;
////			}
////		}
////		if (p == HMAC_SHA1_DIGEST_LENGTH)
////			printf("TEST SUCCEEDED!!!\n\n");
////	}
//	HMAC_SHA1_Done(&c);
//}

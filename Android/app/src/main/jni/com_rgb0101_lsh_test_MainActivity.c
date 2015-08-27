#include "com_rgb0101_lsh_test_MainActivity.h"
//#include "benchmark.h"
#include "lsh160_generic.h"
//#include "lsh_benchmark.h"
#include "lsh_common.h"
#include "hmac_sha1.h"

#include <android/log.h>

#include <time.h>

#define DATASIZE 1000000

typedef struct _test_vector {
    int		caseno;
    int		keylen;
    unsigned char	*key;
    int		datalen;
    unsigned char	*data;
    unsigned char	*digest;
} test_vector;

unsigned char tolower_hmac(unsigned char c) {
    if (c >= (unsigned char)'A' && c <= (unsigned char)'A')
        return c + ((unsigned char)'a' - (unsigned char)'A');
    return c;
}

unsigned char hexdigit(unsigned char c) {
    c = tolower_hmac(c);
    if (c >= (unsigned char)'a' && c <= (unsigned char)'f')
        c += (10 - (unsigned char)'a');
    else
        c += (0 - (unsigned char)'0');
    return c;
}

unsigned char *hex2data(unsigned char *hex, int len) {
    unsigned char	*data;
    int		dl;
    unsigned int	c;

    /* Assume the hex data ALWAYS begins with "0x" */
    hex += 2;

    /* Allocate space... */
    data = (unsigned char *)malloc(sizeof(unsigned char) * len);

    for (dl = 0; dl < len; dl++) {
        c = (unsigned int)hexdigit(*hex++) << 4;
        c |= (unsigned int)hexdigit(*hex++);
        data[dl] = (unsigned char)c;
    }

    return data;
}


static double now_ms(void) {

    struct timespec res;
    clock_gettime(CLOCK_REALTIME, &res);
    return 1000.0 * res.tv_sec + (double) res.tv_nsec / 1e6;

}

void lsh_start(){
    unsigned char data[DATASIZE];
    unsigned char hash[32]= {0,};
    int i, j;
    double calibration, t0, t1,tMin;

    for(i=0; i<DATASIZE; i++) data[i]= (unsigned char)(i%(sizeof(unsigned char)*8));

    t0= now_ms();
    for(i=0; i<50000; i++){
        Hash160(160 ,data, 1000000, hash);
    }
    t1= now_ms();

    tMin= (t1-t0);
    tMin= tMin;
    __android_log_print(ANDROID_LOG_DEBUG, "LSH_TAG", "1MB message result : %7.2f\n", tMin);
}

void sha_start(){
    int             i, p, j;
    HMAC_SHA1_CTX   c;
    unsigned char   md[HMAC_SHA1_DIGEST_LENGTH];
    double t0, t1, tMin;
    double cpbcheck;
    test_vector	tests;

    tests.caseno = 6;
    tests.keylen = 3;
    tests.key = (unsigned char*)"sha";
    tests.datalen = 1000000;
    tests.digest = hex2data((unsigned char*)"0xaa4ae5e15272d00e95705637ce8a3b55ed402112", 20);

    /* Now do the tests */
        tests.data= (unsigned char*)malloc(sizeof(unsigned char)*tests.datalen);
        for(j=0; j<tests.datalen; j++) tests.data[j]=(unsigned char)(j%sizeof(unsigned char)*8);

        t0= now_ms();
        for(j=0; j<50000; j++){
            HMAC_SHA1_Init(&c);
            /* Send the first 3 bytes of key */
            HMAC_SHA1_UpdateKey(&c, tests.key, 3);
            HMAC_SHA1_UpdateKey(&c, &(tests.key[3]), tests.keylen - 3);
            HMAC_SHA1_EndKey(&c);
            HMAC_SHA1_StartMessage(&c);
            /* Send the first 7 bytes of data */
            HMAC_SHA1_UpdateMessage(&c, tests.data, 7);
            HMAC_SHA1_UpdateMessage(&c, &(tests.data[7]), tests.datalen - 7);
            HMAC_SHA1_EndMessage(&(md[0]),&c);
        }
        t1= now_ms();

    tMin= (t1-t0);
    tMin= tMin;
    __android_log_print(ANDROID_LOG_DEBUG, "LSH_TAG", "SHA-1 1MB message result : %7.2f\n", tMin);

        free(tests.data);
        //        printf("Message Digest Was: \"0x");
        //		for (p = 0; p < HMAC_SHA1_DIGEST_LENGTH; p++)
        //			printf("%02x", (unsigned char)md[p]);
        //		printf("\"\nExpected: \"0x");
        //		for (p = 0; p < HMAC_SHA1_DIGEST_LENGTH; p++)
        //			printf("%02x", (unsigned char)tests[i].digest[p]);
        //		printf("\"\n");
        //		for (p = 0; p < HMAC_SHA1_DIGEST_LENGTH; p++) {
        //			if (tests[i].digest[p] != md[p]) {
        //				printf("TEST FAILED (at byte %d)!!!\n", p);
        //				printf("'0x%02x' != '0x%02x' apparently...\n", (unsigned char)tests[i].digest[p], (unsigned char)md[p]);
        //				break;
        //			}
        //		}
        //		if (p == HMAC_SHA1_DIGEST_LENGTH)
        //			printf("TEST SUCCEEDED!!!\n\n");
    HMAC_SHA1_Done(&c);
}

JNIEXPORT void JNICALL Java_com_rgb0101_lsh_1test_MainActivity_lshstart (JNIEnv * env, jclass cls){
    lsh_start();
}
JNIEXPORT void JNICALL Java_com_rgb0101_lsh_1test_MainActivity_shastart (JNIEnv * env, jclass cls){
    sha_start();
}
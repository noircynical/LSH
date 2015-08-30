#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "lsh160_generic.h"

void compress160(hashState160 * state, const Byte * datablock) {
    int j, l, k;
    u32 vl, vr;
    
    /*expanded message*/
    u32 m[16 * (NS160 + 1)];
    
    u32 T[16];
    
    //message expansion
    for (l = 0; l < 32; l++){
        m[l] = U8TO32_LE(datablock + 4 * l);
    }
    
    for (j = 2; j <= NS160; j++){
        k = 16*j;
        m[k +  0] = m[k - 16] + m[k - 29];
        m[k +  1] = m[k - 15] + m[k - 30];
        m[k +  2] = m[k - 14] + m[k - 32];
        m[k +  3] = m[k - 13] + m[k - 31];
        m[k +  4] = m[k - 12] + m[k - 25];
        m[k +  5] = m[k - 11] + m[k - 28];
        m[k +  6] = m[k - 10] + m[k - 27];
        m[k +  7] = m[k -  9] + m[k - 26];
        m[k +  8] = m[k -  8] + m[k - 21];
        m[k +  9] = m[k -  7] + m[k - 22];
        m[k + 10] = m[k -  6] + m[k - 24];
        m[k + 11] = m[k -  5] + m[k - 23];
        m[k + 12] = m[k -  4] + m[k - 17];
        m[k + 13] = m[k -  3] + m[k - 20];
        m[k + 14] = m[k -  2] + m[k - 19];
        m[k + 15] = m[k -  1] + m[k - 18];
    }
    
    for (j = 0; j < NS160/2; j++){
        
        //MsgAdd & Mix
        k = 2*j;
        for (l = 0; l < 8; l++){
            vl = state->cv160[l]^m[16*k + l];
            vr = state->cv160[l + 8]^m[16*k + l+8];
            vl = ROL32(vl + vr, 29) ^ SC160[k][l];
            vr = ROL32(vr + vl, 1);
            T[l] = vr + vl;
            T[l + 8] = ROL32(vr, gamma160[l]);
        }
        //WordPerm
        state->cv160[0] = T[ 6];state->cv160[ 8] = T[ 2];
        state->cv160[1] = T[ 4];state->cv160[ 9] = T[ 0];
        state->cv160[2] = T[ 5];state->cv160[10] = T[ 1];
        state->cv160[3] = T[ 7];state->cv160[11] = T[ 3];
        state->cv160[4] = T[12];state->cv160[12] = T[ 8];
        state->cv160[5] = T[15];state->cv160[13] = T[11];
        state->cv160[6] = T[14];state->cv160[14] = T[10];
        state->cv160[7] = T[13];state->cv160[15] = T[ 9];
        
        //MsgAdd & Mix
        k = 2*j+1;
        for (l = 0; l < 8; l++){
            vl = state->cv160[l]^m[16*k + l];
            vr = state->cv160[l + 8]^m[16*k + l+8];
            vl = ROL32(vl + vr, 5)^ SC160[k][l];
            vr = ROL32(vl + vr, 17);
            T[l] = vr + vl;
            T[l + 8] = ROL32(vr, gamma160[l]);
        }
        //WordPerm
        state->cv160[0] = T[ 6];state->cv160[ 8] = T[ 2];
        state->cv160[1] = T[ 4];state->cv160[ 9] = T[ 0];
        state->cv160[2] = T[ 5];state->cv160[10] = T[ 1];
        state->cv160[3] = T[ 7];state->cv160[11] = T[ 3];
        state->cv160[4] = T[12];state->cv160[12] = T[ 8];
        state->cv160[5] = T[15];state->cv160[13] = T[11];
        state->cv160[6] = T[14];state->cv160[14] = T[10];
        state->cv160[7] = T[13];state->cv160[15] = T[ 9];
    }
    
    for (l = 0; l < 16; l++) state->cv160[l] ^= m[10 * NS160 + l];
    
//    return;
}
int Init160(hashState160 * state, int hashbitlen) {
    int j, l;
    int k;
    u32 vl, vr;
    
    u32 T[16];
    
    if ((hashbitlen <0) || (hashbitlen>160))
        return FAIL;
    else if (hashbitlen < 160){
        memset(state->cv160, 0, 16 * sizeof(u32));
        state->cv160[0] = 32;
        state->cv160[1] = (u32)hashbitlen;
        
        for (j = 0; j < NS160/2; j++)
        {
            //Mix
            k = 2*j;
            for (l = 0; l < 8; l++){
                vl = state->cv160[l];
                vr = state->cv160[l + 8];
                vl = ROL32(vl + vr, 29) ^ SC160[k][l];
                vr = ROL32(vr + vl, 1);
                T[l] = vr + vl;
                T[l + 8] = ROL32(vr, gamma160[l]);
            }
            //WordPerm
            state->cv160[0] = T[ 6];state->cv160[ 8] = T[ 2];
            state->cv160[1] = T[ 4];state->cv160[ 9] = T[ 0];
            state->cv160[2] = T[ 5];state->cv160[10] = T[ 1];
            state->cv160[3] = T[ 7];state->cv160[11] = T[ 3];
            state->cv160[4] = T[12];state->cv160[12] = T[ 8];
            state->cv160[5] = T[15];state->cv160[13] = T[11];
            state->cv160[6] = T[14];state->cv160[14] = T[10];
            state->cv160[7] = T[13];state->cv160[15] = T[ 9];
            
            //Mix
            k = 2*j+1;
            for (l = 0; l < 8; l++){
                vl = state->cv160[l];
                vr = state->cv160[l + 8];
                vl = ROL32(vl + vr, 5)^ SC160[k][l];
                vr = ROL32(vl + vr, 17);
                T[l] = vr + vl;
                T[l + 8] = ROL32(vr, gamma160[l]);
            }
            //WordPerm
            state->cv160[0] = T[ 6];state->cv160[ 8] = T[ 2];
            state->cv160[1] = T[ 4];state->cv160[ 9] = T[ 0];
            state->cv160[2] = T[ 5];state->cv160[10] = T[ 1];
            state->cv160[3] = T[ 7];state->cv160[11] = T[ 3];
            state->cv160[4] = T[12];state->cv160[12] = T[ 8];
            state->cv160[5] = T[15];state->cv160[13] = T[11];
            state->cv160[6] = T[14];state->cv160[14] = T[10];
            state->cv160[7] = T[13];state->cv160[15] = T[ 9];
        }
    }
    else /* if hashbitlen == 256*/
    {
        memcpy(state->cv160, IV160, sizeof(IV160));
    }
    
    state->hashbitlen = hashbitlen;
    state->databitlen = 0;
    memset(state->data160, 0, 80);
    
    return SUCCESS;
}
int Update160(hashState160 * state, const Byte * data, DataLength databitlen) {
    //databitlen is a multiple of 8 except for the last update
    
    int temp;
    int leftbits, leftbytes, filledbytes, datalen;
    
    if (state->databitlen & 0x7) return FAIL;
    if (!databitlen) return SUCCESS;
    
    leftbits = state->databitlen;
    temp = databitlen + leftbits;
    leftbytes = leftbits >> 3;
    datalen = databitlen >> 3;
    
    if (temp < 1024){
        //no message blocks processed
        //update the remaining block
        state->databitlen = temp;
        memcpy(state->data160 + leftbytes, data, datalen);
        if (databitlen & 0x7) state->data160[temp >> 3] = data[datalen] & (0xFF << (8 - (databitlen & 0x7)));
        return SUCCESS;
    }
    
    else{
        //process the first message block
        filledbytes = 80 - leftbytes;
        memcpy(state->data160 + leftbytes, data, filledbytes);
        compress160(state, state->data160);
        data += filledbytes;
        temp -= 1024;
        //process next message blocks in turns
        while (temp >= 1024){
            compress160(state, data);
            data += 80;
            temp -= 1024;
        }
        //update the remaining block
        state->databitlen = temp;
        memcpy(state->data160, data, temp >> 3);
        if (temp & 0x7) state->data160[temp >> 3] = data[temp >> 3] & (0xFF << (8 - (temp & 0x7)));
        return SUCCESS;
    }
    
}
void Final160(hashState160 * state, Byte * hashval) {
    
    int pos1, pos2;
    int l;
    u32 H[8];
    
    int databitlen = state->databitlen;
    
    pos1 = (u32)(databitlen >> 3);
    pos2 = (u32)(databitlen & 0x7);
    
    //if databitlen not multiple of 8
    if (pos2){
        state->data160[pos1] |= (0x1 << (7 - pos2));
    }
    
    else{
        state->data160[pos1] = 0x80;
    }
    
    memset(state->data160 + pos1 + 1, 0, 80 - pos1 - 1);
    compress160(state, state->data160);
    
    for (l = 0; l < 8; l++) H[l] = (state->cv160[l]) ^ (state->cv160[l + 8]);
    
    for (l = 0; l < (state->hashbitlen) >> 3; l++){
        //		hashval[l] = (u8)(ROR32(H[l >> 2], (l << 3) & 0x1f) ); 
        hashval[l] = (u8)(H[l >> 2] >> ((l << 3) & 0x1f)); //0,8,16,24,0,,.. = 8*l (mod 32) = (l<<3)&0x1f
    }
    
    return;
}
int Hash160(int hashbitlen, const Byte * data, DataLength databitlen, Byte * hashval) {
    
    int ret;
    hashState160 state;
    
    if (data == NULL && databitlen > 0){
        return FAIL;
    }
    if (hashval == NULL){
        return FAIL;
    }
    
    ret = Init160(&state, hashbitlen);
    if (ret != SUCCESS) return ret;
    
    Update160(&state, data, databitlen);
    
    Final160(&state, hashval);
    
    return SUCCESS;
}


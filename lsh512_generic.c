#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "lsh512_generic.h"

void compress512(hashState512 * state, const Byte * datablock) {
	int j, l, k;
	u64 vl, vr;
	

	/*expanded message*/
	u64 m[16 * (NS512 + 1)];

	u64 T[16];

	//message expansion
	for (l = 0; l < 32; l++){
		m[l] = U8TO64_LE(datablock + 8 * l);
	}

	for (j = 2; j <= NS512; j++){
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


	for (j = 0; j < NS512/2; j++){

		//MsgAdd & Mix
		k = 2*j;
		for (l = 0; l < 8; l++){
			vl = state->cv512[l]^m[16*k + l];
			vr = state->cv512[l + 8]^m[16*k + l+8];
			vl = ROL64(vl + vr, 23) ^ SC512[k][l];
			vr = ROL64(vr + vl, 59);
			if(!(l&1)) T[l] = vr + vl;
			T[l + 8] = ROL64(vr, gamma512[l]);
		}
		//WordPerm
		state->cv512[0] = T[ 6];state->cv512[ 8] = T[ 2];
		state->cv512[1] = T[ 4];state->cv512[ 9] = T[ 0];
		state->cv512[2] = T[ 5];state->cv512[10] = T[ 1];
		state->cv512[3] = T[ 7];state->cv512[11] = T[ 3];
		state->cv512[4] = T[12];state->cv512[12] = T[ 8];
		state->cv512[5] = T[15];state->cv512[13] = T[11];
		state->cv512[6] = T[14];state->cv512[14] = T[10];
		state->cv512[7] = T[13];state->cv512[15] = T[ 9];


		//MsgAdd & Mix
		k = 2*j+1;
		for (l = 0; l < 8; l++){
			vl = state->cv512[l]^m[16*k + l];
			vr = state->cv512[l + 8]^m[16*k + l+8];	
			vl = ROL64(vl + vr, 7)^ SC512[k][l];
			vr = ROL64(vl + vr, 3);
			if(l&1) T[l] = vr + vl;
			T[l + 8] = ROL64(vr, gamma512[l]);
		}
		//WordPerm
		state->cv512[0] = T[ 6];state->cv512[ 8] = T[ 2];
		state->cv512[1] = T[ 4];state->cv512[ 9] = T[ 0];
		state->cv512[2] = T[ 5];state->cv512[10] = T[ 1];
		state->cv512[3] = T[ 7];state->cv512[11] = T[ 3];
		state->cv512[4] = T[12];state->cv512[12] = T[ 8];
		state->cv512[5] = T[15];state->cv512[13] = T[11];
		state->cv512[6] = T[14];state->cv512[14] = T[10];
		state->cv512[7] = T[13];state->cv512[15] = T[ 9];
	}	

	for (l = 0; l < 16; l++) state->cv512[l] ^= m[16 * NS512 + l];
	return;
}
int Init512(hashState512 * state, int hashbitlen) {

	int j, l;
	int k;
	u64 vl, vr;

	u64 T[16];

	if ((hashbitlen <0) || (hashbitlen>512))
		return FAIL;
	else if (hashbitlen < 512){
		memset(state->cv512, 0, 16 * sizeof(u64));
		state->cv512[0] = 64;
		state->cv512[1] = (u64)hashbitlen;
		
		for (j = 0; j < NS512/2; j++)
		{		
			//Mix
			k = 2*j;
			for (l = 0; l < 8; l++){
				vl = state->cv512[l];
				vr = state->cv512[l + 8];
				vl = ROL64(vl + vr, 23) ^ SC512[k][l];
				vr = ROL64(vr + vl, 59);
				if(!(l&1)) T[l] = vr + vl;
				T[l + 8] = ROL64(vr, gamma512[l]);
			}
			//WordPerm
			state->cv512[0] = T[ 6];state->cv512[ 8] = T[ 2];
			state->cv512[1] = T[ 4];state->cv512[ 9] = T[ 0];
			state->cv512[2] = T[ 5];state->cv512[10] = T[ 1];
			state->cv512[3] = T[ 7];state->cv512[11] = T[ 3];
			state->cv512[4] = T[12];state->cv512[12] = T[ 8];
			state->cv512[5] = T[15];state->cv512[13] = T[11];
			state->cv512[6] = T[14];state->cv512[14] = T[10];
			state->cv512[7] = T[13];state->cv512[15] = T[ 9];


			//Mix
			k = 2*j+1;
			for (l = 0; l < 8; l++){
				vl = state->cv512[l];
				vr = state->cv512[l + 8];
				vl = ROL64(vl + vr, 7)^ SC512[k][l];
				vr = ROL64(vl + vr, 3);
				if(l&1) T[l] = vr + vl; 
				T[l + 8] = ROL64(vr, gamma512[l]);
			}
			//WordPerm
			state->cv512[0] = T[ 6];state->cv512[ 8] = T[ 2];
			state->cv512[1] = T[ 4];state->cv512[ 9] = T[ 0];
			state->cv512[2] = T[ 5];state->cv512[10] = T[ 1];
			state->cv512[3] = T[ 7];state->cv512[11] = T[ 3];
			state->cv512[4] = T[12];state->cv512[12] = T[ 8];
			state->cv512[5] = T[15];state->cv512[13] = T[11];
			state->cv512[6] = T[14];state->cv512[14] = T[10];
			state->cv512[7] = T[13];state->cv512[15] = T[ 9];
		}
	}
	else /* if hashbitlen == 512 */
	{
		memcpy(state->cv512, IV512, sizeof(IV512));
	}

	state->hashbitlen = hashbitlen;
	state->databitlen = 0;
	memset(state->data512, 0, 128);

	return SUCCESS;
}
int Update512(hashState512 * state, const Byte * data, DataLength databitlen) {
	//databitlen is a multiple of 8 except for the last update

	int temp;
	int leftbits, leftbytes, filledbytes, datalen;
	
	if (state->databitlen & 0x7) return FAIL;
	if (!databitlen) return SUCCESS;

	leftbits = state->databitlen;
	temp = databitlen + leftbits;
	leftbytes = leftbits >> 3;
	datalen = databitlen >> 3;

	if (temp < 2048){
		//no message blocks processed
		//update the remaining block
		state->databitlen = temp;
		memcpy(state->data512 + leftbytes, data, datalen);
		if (databitlen & 0x7) state->data512[temp >> 3] = data[datalen] & (0xFF << (8 - (databitlen & 0x7)));
		return SUCCESS;
	}

	else{
		//process the first message block
		filledbytes = 256 - leftbytes;
		memcpy(state->data512 + leftbytes, data, filledbytes);
		compress512(state, state->data512);
		data += filledbytes;
		temp -= 2048;
		//process next message blocks in turns
		while (temp >= 2048){
			compress512(state, data);
			data += 256;
			temp -= 2048;
		}
		//update the remaining block
		state->databitlen = temp;
		memcpy(state->data512, data, temp >> 3);
		if (temp & 0x7) state->data512[temp >> 3] = data[temp >> 3] & (0xFF << (8 - (temp & 0x7)));
		return SUCCESS;
	}

}
void Final512(hashState512 * state, Byte * hashval) {

	int pos1, pos2;
	int l;
	u64 H[8];

	int databitlen = state->databitlen;

	pos1 = (u32)(databitlen >> 3);
	pos2 = (u32)(databitlen & 0x7);

	//if databitlen not multiple of 8
	if (pos2){
		state->data512[pos1] |= (0x1 << (7 - pos2));
	}

	else{
		state->data512[pos1] = 0x80;
	}

	memset(state->data512 + pos1 + 1, 0, 256 - pos1 - 1);

	compress512(state, state->data512);

	for (l = 0; l < 8; l++) H[l] = (state->cv512[l]) ^ (state->cv512[l + 8]);

	for (l = 0; l < (state->hashbitlen) >> 3; l++){
//		hashval[l] = (u8)(ROR64(H[l >> 3], (l << 3) & 0x3f));
		hashval[l] = (u8)(H[l >> 3] >> ((l << 3) & 0x3f)); //0,8,16,24,32,40,48,56,0,... = 8*l (mod 64) = (l<<3)&0x3f
	}

	return;
}/////////////////////////////////////////////////////////////////////////////////////
int Hash512(int hashbitlen, const Byte * data, DataLength databitlen, Byte * hashval) {

	int ret;
	hashState512 state;

	if (data == NULL && databitlen > 0){
		return FAIL;
	}
	if (hashval == NULL){
		return FAIL;
	}

	ret = Init512(&state, hashbitlen);
	if (ret != SUCCESS) return ret;

	Update512(&state, data, databitlen);	

	Final512(&state, hashval);

	return SUCCESS;
}


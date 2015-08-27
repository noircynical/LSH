#ifndef _LSH512_GENERIC_H
#define _LSH512_GENERIC_H
//////////////////////////////////////////////////////
#include "lsh_common.h"

/* number of steps for LSH-512-n */
#define NS512  28

typedef struct  {	
	u64 cv512[16];         /* current chain value */
	Byte data512[256];	/* remaining data*/
	int hashbitlen;    /* length of the hash value (bits) */
	int databitlen;       /*amount of remaining data(data512) to hash in bits*/
} hashState512;


/*
compression funtion

INPUT
state: structure that holds the hashState information
datablock: 256-byte data

OUTPUT
state: state after compression
*/
void compress512(hashState512 * state, const Byte * datablock);

/*
load the hashState structure (copy hashbitlen...)

INPUT
state: hashState structure
hashbitlen: length of the hash output


OUTPUT
state: state after initialization
SUCCESS on success
FAIL on failure
*/
int Init512(hashState512 * state, int hashbitlen);

/*
update the state (chain value) with new data: process all but the last datablock

INPUT
state: hashState structure
data: data to hash
databitlen: bit length of the data

OUTPUT
state: state after update
SUCCESS on success
FAIL if arbitrary failure
*/
int Update512(hashState512 * state, const Byte * data, DataLength databitlen);

/*
finalize the hash, hashing remaining data and padding the message

INPUT
state: hashState structure
hashval: storage for the hash value

OUTPUT
hashval: the hash value
*/
void Final512(hashState512 * state, Byte * hashval);

/*
INPUT
hashbitlen: length of the hash output
data: data to hash
databitlen: bit length of the data
hashval: storage for the hash value

OUTPUT
hashval: the hash value
SUCCESS on success
FAIL if arbitrary failure
*/
int Hash512(int hashbitlen, const Byte * data, DataLength databitlen, Byte * hashval);

//step constants
static u64 SC512[NS512][8] = {
	{ 0x97884283c938982aULL, 0xba1fca93533e2355ULL, 0xc519a2e87aeb1c03ULL, 0x9a0fc95462af17b1ULL,
	0xfc3dda8ab019a82bULL, 0x02825d079a895407ULL, 0x79f2d0a7ee06a6f7ULL, 0xd76d15eed9fdf5feULL },
	{ 0x1fcac64d01d0c2c1ULL, 0xd9ea5de69161790fULL, 0xdebc8b6366071fc8ULL, 0xa9d91db711c6c94bULL,
	0x3a18653ac9c1d427ULL, 0x84df64a223dd5b09ULL, 0x6cc37895f4ad9e70ULL, 0x448304c8d7f3f4d5ULL },
	{ 0xea91134ed29383e0ULL, 0xc4484477f2da88e8ULL, 0x9b47eec96d26e8a6ULL, 0x82f6d4c8d89014f4ULL,
	0x527da0048b95fb61ULL, 0x644406c60138648dULL, 0x303c0e8aa24c0edcULL, 0xc787cda0cbe8ca19ULL },
	{ 0x7ba46221661764caULL, 0x0c8cbc6acd6371acULL, 0xe336b836940f8f41ULL, 0x79cb9da168a50976ULL,
	0xd01da49021915cb3ULL, 0xa84accc7399cf1f1ULL, 0x6c4a992cee5aeb0cULL, 0x4f556e6cb4b2e3e0ULL },
	{ 0x200683877d7c2f45ULL, 0x9949273830d51db8ULL, 0x19eeeecaa39ed124ULL, 0x45693f0a0dae7fefULL,
	0xedc234b1b2ee1083ULL, 0xf3179400d68ee399ULL, 0xb6e3c61b4945f778ULL, 0xa4c3db216796c42fULL },
	{ 0x268a0b04f9ab7465ULL, 0xe2705f6905f2d651ULL, 0x08ddb96e426ff53dULL, 0xaea84917bc2e6f34ULL,
	0xaff6e664a0fe9470ULL, 0x0aab94d765727d8cULL, 0x9aa9e1648f3d702eULL, 0x689efc88fe5af3d3ULL },
	{ 0xb0950ffea51fd98bULL, 0x52cfc86ef8c92833ULL, 0xe69727b0b2653245ULL, 0x56f160d3ea9da3e2ULL,
	0xa6dd4b059f93051fULL, 0xb6406c3cd7f00996ULL, 0x448b45f3ccad9ec8ULL, 0x079b8587594ec73bULL },
	{ 0x45a50ea3c4f9653bULL, 0x22983767c1f15b85ULL, 0x7dbed8631797782bULL, 0x485234be88418638ULL,
	0x842850a5329824c5ULL, 0xf6aca914c7f9a04cULL, 0xcfd139c07a4c670cULL, 0xa3210ce0a8160242ULL },
	{ 0xeab3b268be5ea080ULL, 0xbacf9f29b34ce0a7ULL, 0x3c973b7aaf0fa3a8ULL, 0x9a86f346c9c7be80ULL,
	0xac78f5d7cabcea49ULL, 0xa355bddcc199ed42ULL, 0xa10afa3ac6b373dbULL, 0xc42ded88be1844e5ULL },
	{ 0x9e661b271cff216aULL, 0x8a6ec8dd002d8861ULL, 0xd3d2b629beb34be4ULL, 0x217a3a1091863f1aULL,
	0x256ecda287a733f5ULL, 0xf9139a9e5b872fe5ULL, 0xac0535017a274f7cULL, 0xf21b7646d65d2aa9ULL },
	{ 0x048142441c208c08ULL, 0xf937a5dd2db5e9ebULL, 0xa688dfe871ff30b7ULL, 0x9bb44aa217c5593bULL,
	0x943c702a2edb291aULL, 0x0cae38f9e2b715deULL, 0xb13a367ba176cc28ULL, 0x0d91bd1d3387d49bULL },
	{ 0x85c386603cac940cULL, 0x30dd830ae39fd5e4ULL, 0x2f68c85a712fe85dULL, 0x4ffeecb9dd1e94d6ULL,
	0xd0ac9a590a0443aeULL, 0xbae732dc99ccf3eaULL, 0xeb70b21d1842f4d9ULL, 0x9f4eda50bb5c6fa8ULL },
	{ 0x4949e69ce940a091ULL, 0x0e608dee8375ba14ULL, 0x983122cba118458cULL, 0x4eeba696fbb36b25ULL,
	0x7d46f3630e47f27eULL, 0xa21a0f7666c0dea4ULL, 0x5c22cf355b37cec4ULL, 0xee292b0c17cc1847ULL },
	{ 0x9330838629e131daULL, 0x6eee7c71f92fce22ULL, 0xc953ee6cb95dd224ULL, 0x3a923d92af1e9073ULL,
	0xc43a5671563a70fbULL, 0xbc2985dd279f8346ULL, 0x7ef2049093069320ULL, 0x17543723e3e46035ULL },
	{ 0xc3b409b00b130c6dULL, 0x5d6aee6b28fdf090ULL, 0x1d425b26172ff6edULL, 0xcccfd041cdaf03adULL,
	0xfe90c7c790ab6cbfULL, 0xe5af6304c722ca02ULL, 0x70f695239999b39eULL, 0x6b8b5b07c844954cULL },
	{ 0x77bdb9bb1e1f7a30ULL, 0xc859599426ee80edULL, 0x5f9d813d4726e40aULL, 0x9ca0120f7cb2b179ULL,
	0x8f588f583c182cbdULL, 0x951267cbe9eccce7ULL, 0x678bb8bd334d520eULL, 0xf6e662d00cd9e1b7ULL },
	{ 0x357774d93d99aaa7ULL, 0x21b2edbb156f6eb5ULL, 0xfd1ebe846e0aee69ULL, 0x3cb2218c2f642b15ULL,
	0xe7e7e7945444ea4cULL, 0xa77a33b5d6b9b47cULL, 0xf34475f0809f6075ULL, 0xdd4932dce6bb99adULL },
	{ 0xacec4e16d74451dcULL, 0xd4a0a8d084de23d6ULL, 0x1bdd42f278f95866ULL, 0xeed3adbb938f4051ULL,
	0xcfcf7be8992f3733ULL, 0x21ade98c906e3123ULL, 0x37ba66711fffd668ULL, 0x267c0fc3a255478aULL },
	{ 0x993a64ee1b962e88ULL, 0x754979556301faaaULL, 0xf920356b7251be81ULL, 0xc281694f22cf923fULL,
	0x9f4b6481c8666b02ULL, 0xcf97761cfe9f5444ULL, 0xf220d7911fd63e9fULL, 0xa28bd365f79cd1b0ULL },
	{ 0xd39f5309b1c4b721ULL, 0xbec2ceb864fca51fULL, 0x1955a0ddc410407aULL, 0x43eab871f261d201ULL,
	0xeaafe64a2ed16da1ULL, 0x670d931b9df39913ULL, 0x12f868b0f614de91ULL, 0x2e5f395d946e8252ULL },
	{ 0x72f25cbb767bd8f4ULL, 0x8191871d61a1c4ddULL, 0x6ef67ea1d450ba93ULL, 0x2ea32a645433d344ULL,
	0x9a963079003f0f8bULL, 0x74a0aeb9918cac7aULL, 0x0b6119a70af36fa3ULL, 0x8d9896f202f0d480ULL },
	{ 0x654f1831f254cd66ULL, 0x1318a47f0366a25eULL, 0x65752076250b4e01ULL, 0xd1cd8eb888071772ULL,
	0x30c6a9793f4e9b25ULL, 0x154f684b1e3926eeULL, 0x6c7ac0b1fe6312aeULL, 0x262f88f4f3c5550dULL },
	{ 0xb4674a24472233cbULL, 0x2bbd23826a090071ULL, 0xda95969b30594f66ULL, 0x9f5c47408f1e8a43ULL,
	0xf77022b88de9c055ULL, 0x64b7b36957601503ULL, 0xe73b72b06175c11aULL, 0x55b87de8b91a6233ULL },
	{ 0x1bb16e6b6955ff7fULL, 0xe8e0a5ec7309719cULL, 0x702c31cb89a8b640ULL, 0xfba387cfada8cde2ULL,
	0x6792db4677aa164cULL, 0x1c6b1cc0b7751867ULL, 0x22ae2311d736dc01ULL, 0x0e3666a1d37c9588ULL },
	{ 0xcd1fd9d4bf557e9aULL, 0xc986925f7c7b0e84ULL, 0x9c5dfd55325ef6b0ULL, 0x9f2b577d5676b0ddULL,
	0xfa6e21be21c062b3ULL, 0x8787dd782c8d7f83ULL, 0xd0d134e90e12dd23ULL, 0x449d087550121d96ULL },
	{ 0xecf9ae9414d41967ULL, 0x5018f1dbf789934dULL, 0xfa5b52879155a74cULL, 0xca82d4d3cd278e7cULL,
	0x688fdfdfe22316adULL, 0x0f6555a4ba0d030aULL, 0xa2061df720f000f3ULL, 0xe1a57dc5622fb3daULL },
	{ 0xe6a842a8e8ed8153ULL, 0x690acdd3811ce09dULL, 0x55adda18e6fcf446ULL, 0x4d57a8a0f4b60b46ULL,
	0xf86fbfc20539c415ULL, 0x74bafa5ec7100d19ULL, 0xa824151810f0f495ULL, 0x8723432791e38ebbULL },
	{ 0x8eeaeb91d66ed539ULL, 0x73d8a1549dfd7e06ULL, 0x0387f2ffe3f13a9bULL, 0xa5004995aac15193ULL,
	0x682f81c73efdda0dULL, 0x2fb55925d71d268dULL, 0xcc392d2901e58a3dULL, 0xaa666ab975724a42ULL }
};

//IV for LSH-512-512
static u64 IV512[16] = {
	0xadd50f3c7f07094eULL, 0xe3f3cee8f9418a4fULL, 0xb527ecde5b3d0ae9ULL, 0x2ef6dec68076f501ULL,
	0x8cb994cae5aca216ULL, 0xfbb9eae4bba48cc7ULL, 0x650a526174725feaULL, 0x1f9a61a73f8d8085ULL,
	0xb6607378173b539bULL, 0x1bc99853b0c0b9edULL, 0xdf727fc19b182d47ULL, 0xdbef360cf893a457ULL,
	0x4981f5e570147e80ULL, 0xd00c4490ca7d3e30ULL, 0x5d73940c0e4ae1ecULL, 0x894085e2edb2d819ULL
};

//rotation amounts
static const int gamma512[8] = { 0, 16, 32, 48, 8, 24, 40, 56 };

#endif
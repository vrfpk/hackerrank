#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <wincrypt.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>

#define MYMAX 0x7f
#define MD5LEN  16

static unsigned int get_random_seed(){
	int seed, i;
	for (i = 0, seed = 0; i < 8; ++i) seed = (seed << 4) | (rand() & 0x0f);
	return seed;
}

static DWORD md5_init(char *dst, int dst_len, char *src, int src_len)
{
	DWORD dwStatus = 0;
	HCRYPTPROV provider = NULL;
	HCRYPTHASH hHash = NULL;
	BYTE hash[MD5LEN];
	DWORD hash_len;
	CHAR hash_digits[] = "0123456789abcdef";
	if (!CryptAcquireContext(&provider,
		NULL,
		NULL,
		PROV_RSA_FULL,
		CRYPT_VERIFYCONTEXT)) {
		dwStatus = GetLastError();
		printf("CryptAcquireContext failed: %d\n", dwStatus);
		return dwStatus;
	}
	if (!CryptCreateHash(provider, CALG_MD5, 0, 0, &hHash)) {
		dwStatus = GetLastError();
		printf("CryptCreateHash failed: %d\n", dwStatus);
		CryptReleaseContext(provider, 0);
		return dwStatus;
	}
	if (!CryptHashData(hHash, src, src_len, 0)) {
		dwStatus = GetLastError();
		printf("CryptHashData failed: %d\n", dwStatus);
		CryptReleaseContext(provider, 0);
		CryptDestroyHash(hHash);
		return dwStatus;
	}
	hash_len = MD5LEN;
	if (!CryptGetHashParam(hHash, HP_HASHVAL, hash, &hash_len, 0)) {
		dwStatus = GetLastError();
		printf("CryptGetHashParam failed: %d\n", dwStatus);
		CryptReleaseContext(provider, 0);
		CryptDestroyHash(hHash);
		return dwStatus;
	}
	printf("MD5 hash of string '%s' is: \t", src);
	for (DWORD i = 0; i < hash_len; i++) {
		printf("%c%c", hash_digits[hash[i] >> 4],
			hash_digits[hash[i] & 0xf]);
	}
	printf("\n");
	CryptReleaseContext(provider, 0);
	CryptDestroyHash(hHash);
	return 0;
}

typedef struct md5_t
{
	HCRYPTPROV provider;
	HCRYPTHASH hash;
} md5_t;

static DWORD md5_init2(md5_t *ctx)
{
	DWORD dwStatus = 0;
	if (!CryptAcquireContext(&ctx->provider, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
		dwStatus = GetLastError();
		printf("CryptAcquireContext failed: %d\n", dwStatus);
		return dwStatus;
	}
	if (!CryptCreateHash(ctx->provider, CALG_MD5, 0, 0, &ctx->hash)) {
		dwStatus = GetLastError();
		printf("CryptCreateHash failed: %d\n", dwStatus);
		CryptReleaseContext(ctx->provider, 0);
		return dwStatus;
	}
	return 0;
}

static DWORD md5_calc(md5_t *ctx, char *dst, char *src, int src_len)
{
	DWORD dwStatus;
	char *fun_name;
	HCRYPTHASH duplicate;
	BYTE *hash;
	DWORD hash_len;
	DWORD hash_len_size = sizeof(DWORD);
	int i;

	if (!CryptHashData(ctx->hash, (BYTE*) src, (DWORD) src_len, 0)) {
		fun_name = "CryptHashData"; goto fail;
	}
	if (!CryptDuplicateHash(ctx->hash, NULL, 0, &duplicate)) {
		fun_name = "CryptDuplicateHash"; goto fail;
	}
	if (!CryptGetHashParam(duplicate, HP_HASHSIZE, (BYTE *) &hash_len, &hash_len_size, 0)) {
		fun_name = "CryptGetHashParam HP_HASHSIZE"; goto fail;
	}
	if (!(hash = (BYTE*) malloc(hash_len))) {
		fun_name = "malloc"; goto fail;
	}
	if (!CryptGetHashParam(duplicate, HP_HASHVAL, hash, &hash_len, 0)) {
		fun_name = "CryptGetHashParam HP_HASHVAL"; goto fail;
	}
	printf("The hash is: ");
	for (i = 0; i < hash_len; i++, dst += 2) sprintf(dst, "%02x", hash[i]);
	printf("\n");

	free(hash);
	if (!CryptDestroyHash(duplicate)) {
		fun_name = "CryptDestroyHash"; goto fail;
	}
	return 0;

fail:
	dwStatus = GetLastError();
	printf("'%s' failed: %d\n", fun_name, dwStatus);
	CryptReleaseContext(ctx->provider, 0);
	CryptDestroyHash(ctx->hash);
	return dwStatus;
}

static DWORD md5_cleanup(md5_t *ctx) {
	CryptReleaseContext(ctx->provider, 0);
	CryptDestroyHash(ctx->hash);
}

//	hash_len = MD5LEN;
//	if (!CryptGetHashParam(ctx->hash, HP_HASHVAL, hash, &hash_len, 0)) {
//		dwStatus = GetLastError();
//		printf("CryptGetHashParam failed: %d\n", dwStatus);
//		CryptReleaseContext(ctx->provider, 0);
//		CryptDestroyHash(hOriginalHash);
//		return dwStatus;
//	}
//	printf("MD5 hash of string '%s' is: \t", src);
//	for (DWORD i = 0; i < hash_len; i++) {
//		printf("%c%c", hash_digits[hash[i] >> 4],
//			hash_digits[hash[i] & 0xf]);
//	}
//	printf("\n");
//	if (!CryptHashData(hOriginalHash, src2, src_len2, 0)) {
//		dwStatus = GetLastError();
//		printf("CryptHashData failed: %d\n", dwStatus);
//		CryptReleaseContext(provider, 0);
//		CryptDestroyHash(hOriginalHash);
//		return dwStatus;
//	}
//	hash_len = MD5LEN;
//	if (!CryptGetHashParam(hOriginalHash, HP_HASHVAL, hash, &hash_len, 0)) {
//		dwStatus = GetLastError();
//		printf("CryptGetHashParam failed: %d\n", dwStatus);
//		CryptReleaseContext(provider, 0);
//		CryptDestroyHash(hOriginalHash);
//		return dwStatus;
//	}
//	printf("MD5 hash of string '%s' is: \t", src2);
//	for (DWORD i = 0; i < hash_len; i++) {
//		printf("%c%c", hash_digits[hash[i] >> 4],
//			hash_digits[hash[i] & 0xf]);
//	}
//	printf("\n");
//	CryptReleaseContext(provider, 0);
//	CryptDestroyHash(hOriginalHash);
//	return 0;
//}

int main()
{
	int i;
	char cnonce[17] = { 0 };
	unsigned int cnonce_buf[2];
	srand((unsigned int) time(NULL));
	cnonce_buf[0] = get_random_seed();
	cnonce_buf[1] = get_random_seed();
	sprintf_s(cnonce, sizeof(cnonce), "%08x%08x", get_random_seed(), get_random_seed());
	printf("%s\n", cnonce);

	char *test1 = "Hello ";
	char dst[33] = { 0 };
	int dst_len;
	//md5_init(NULL, 0, test1, strlen(test1) + 1);
	//char *test2 = "World!";
	//md5_init(NULL, 0, test2, strlen(test2) + 1);
	//char *test3 = "Hello ";
	//char *test4 = "World!";
	//md5_init2(test3, strlen(test3) + 1, test4, strlen(test4) + 1);

	md5_t md5ctx;
	md5_init2(&md5ctx);
	md5_calc(&md5ctx, dst, test1, strlen(test1) + 1);
	printf("dst: %s", dst);
	md5_cleanup(&md5ctx);

	return 0;
}
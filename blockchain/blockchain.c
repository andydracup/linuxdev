#include <openssl/crypto.h>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

static void blockchain_genesis(void);
static void blockchain_addblock(int);
static bool blockchain_verify(void);
static void blockchain_corrupt(void);
static void bio_test(void);

struct block_header {
    unsigned char prev_hash[SHA256_DIGEST_LENGTH];
    int data;
};

struct block {
    struct block_header header;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    struct block* link;
};

struct block head;

int main(int argc, char* argv[]) 
{
    bool ok;
    blockchain_genesis();
    for (int i = 1; i <= 10; i++) {
        printf("Adding block %d\n", i);
        blockchain_addblock(i);
    }

    blockchain_corrupt();

    printf("verifying blockchain...\n");
    ok = blockchain_verify();
    if (ok) {
        printf("Verified\n");
    }
    else {
        printf("Not verified\n");
    }
        
    //bio_test();
    return 0;
}

static void blockchain_genesis(void) 
{
    char start[] = "";
    SHA256((unsigned char*) start, strlen(start)+1, head.hash);
}

static void blockchain_addblock(int data) 
{
    struct block* last = &head;
    for (;;) {
        if (last->link == NULL) {
            break;
        }
        last = last->link;
    }
    struct block* new = malloc(sizeof(struct block));
    if (new == NULL) {
        return;
    }
    memcpy(&new->header.prev_hash, &last->hash, SHA256_DIGEST_LENGTH);
    new->header.data = data;
    SHA256((unsigned char*) &new->header, sizeof(struct block_header), new->hash);
    new->link = NULL;
    last->link = new;
}

static void blockchain_corrupt(void) 
{
    struct block* last = &head;
    for (;;) {
        if (last->link == NULL) {
            break;
        }
        last = last->link;
    }
    last->header.data = -1;
}

static bool blockchain_verify(void) 
{
    bool ok;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    struct block* next = head.link;
    for (;;) {
        if (next == NULL) {
            break;
        }
        SHA256((unsigned char*) &next->header, sizeof(struct block_header), hash);
        if (memcmp(hash, next->hash, SHA256_DIGEST_LENGTH) != 0) {
            break;
        }
        next = next->link;
    }

    if (next == NULL) {
        ok = true;
        }
    else {
        ok = false;
    }
        
    return ok;
}

static void bio_test(void)
{
    BIO *bio, *b64;
    char message[] = "Hello World \n";
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new_fp(stdout, BIO_NOCLOSE);
    BIO_push(b64, bio);
    BIO_write(b64, message, strlen(message));
    BIO_flush(b64);
    BIO_free_all(b64);
}

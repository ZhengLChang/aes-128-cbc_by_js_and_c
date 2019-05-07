/*
 * Copyright (C), 2010-2017, ATCOM Tech. Co., Ltd.
 *
 * File Name: test.c
 * Author: liaoxuecheng
 * mail: liaoxuecheng@atcom.com.cn
 * Created Time: Tue 07 May 2019 11:07:54 AM CST
 *
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "acm_encryption.h"

static int generatep(uint8_t *p)
{
    for(int i = 0;i < 16; i++)
    {
        p[i] = rand() % 0xFF;
    }
    return 0;
}
static int generated(uint8_t *p, int len)
{
    int t = rand() % len;
    memset(p, 0, len);
    for(int i = 0;i < t; i++)
    {
        p[i] = rand() % 0xFF;
    }
    return t;
}
int main(int argc, char *argv[])
{
    int len_old = 0, len_d = 0;
    uint8_t p[16], iv[16], data[2048];
    void *e, *d;

    srand(time(NULL));
    for(int i = 0; i < 1000000; i++)
    {
        generatep(p);
        generatep(iv);
        len_old = generated(data, sizeof(data));
        e = (void *)acm_encode(iv, p, data, len_old);
        d = (void *)acm_decode(iv, p, e, &len_d);
        if(len_d != len_old || memcmp(data, d, len_old))
        {
            printf("len_old = %d len_d = %d\n", len_old, len_d);
            break;
        }
        if(i % 10000 == 0)
        {
            printf("times: %d, cur_len = %d\n", i, len_d);
            for(int j = 0; j < 32 && j < len_d; j++)
                printf("%02x,", data[j]);
            printf("\n");
        }
        free(e);
        free(d);
    }
    return 0;
}

int test_main(int argc, char *argv[])
{
    int len;
    char iv[17] = "0123456789abcdef";
    char passwd[64] = "0123456789abcdef";
    void *data;

    if(argc <= 3)
    {
        printf("%s [e|d] passwd data\n", argv[0]);
        return -1;
    }

    if(argv[1][0] == 'd')
    {
        acm_decode_file(iv, passwd, argv[2], argv[3]);
    }
    else
        acm_encode_file(iv, passwd, argv[2], argv[3]);
    return 0;

    char *p = argv[3];

    memset(passwd, 0, sizeof(passwd));
    snprintf(passwd, sizeof(passwd), "%s", argv[2]);
    len = strlen(argv[3]);
    

    if(argv[1][0] == 'd')
    {
        data = (void *)acm_decode(iv, passwd, p, &len);
        printf("%.*s\n", len, (char *)data);
    }
    else
    {
        data = (void *)acm_encode(iv, passwd, p, len);
        printf("%s\n", (char *)data);
    }

    free(data);
    return 0;
}

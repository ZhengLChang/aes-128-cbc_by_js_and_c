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


int main(int argc, char *argv[])
{
    int len_old = 0, len_d = 0;
    //uint8_t p[] = "751f621ea5c8f930", iv[] = "2624750004598718", data[2048] = "zheng";
    uint8_t p[] = "751f621ea5c8f930", iv[] = "2624750004598718", data[2048] = "zheng\r\nfjdkaldfasafsdjadjsaldsafjaskfldafdsjadfla";
    void *e, *d;
    e = (void *)acm_encode(iv, p, data, strlen(data));
	fprintf(stderr, "%s\n", (char *)e);
	d = (void *)acm_decode(iv, p, e, &len_d);
  fprintf(stderr, "%s===\n", d);

	free(e);
	free(d);
    return 0;
}


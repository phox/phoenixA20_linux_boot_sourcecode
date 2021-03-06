/*
******************************************************************************************************************
*                                            Aone project ---- eGON module
*
*                             Copyright(C), 2006-2008, SoftWinners Microelectronic Co., Ltd.
*											       All Rights Reserved
*
* File Name : gen_check_sum.c
*
* Author : Gary.Wang
*
* Version : 1.1.0
*
* Date : 2007.09.23
*
* Description : This file provides a function gen_check_sum( ) to generate a check_sum code for a
*             source file and create a destination file with the check_sum code and aligning 4KB.
*
* Functions list : int gen_check_sum( const char * source_file, const char * dest_file )
*
* Others : None at present.
*
*
* History :
*
*  <Author>        <time>       <version>      <desricption>
*
* Gary.Wang       2007.08.09      1.1.0        build the file
*
* Gary.Wang       2007.09.23      1.1.0        make many modifications:
*                                            create a destination file.
*                                            make destination file align 4KB.
*
* Gary.Wang       2007.10.13      1.1.0        ignore "stamp value"
*                                              "check sum" generated overlays "stamp value"
*                                              "destination file size" are inputed by outside
*******************************************************************************************************************
*/

#include  "check_sum.h"

__s32 gen_check_sum( void *boot_buf )
{
	boot_file_head_t  *head_p;
	__u32           length;
	__u32           *buf;
	__u32            loop;
	__u32            i;
	__u32            sum;

	head_p = (boot_file_head_t *)boot_buf;
	length = head_p->length;
	if( ( length & 0x3 ) != 0 )                   // must 4-byte-aligned
		return -1;
	buf = (__u32 *)boot_buf;
	head_p->check_sum = STAMP_VALUE;              // fill stamp
	loop = length >> 2;
    /* 计算当前文件内容的“校验和”*/
    for( i = 0, sum = 0;  i < loop;  i++ )
    	sum += buf[i];

    /* write back check sum */
    head_p->check_sum = sum;

    return 0;
}

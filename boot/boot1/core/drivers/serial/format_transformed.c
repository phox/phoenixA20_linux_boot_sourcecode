/*
************************************************************************************************************************
*                                                         eGON
*                                         the Embedded GO-ON Bootloader System
*
*                             Copyright(C), 2006-2008, Allwinner Microelectronic Co., Ltd.
*											       All Rights Reserved
*
*File Name�� format_transformed.c
*
*Author�� Gary.Wang
*
*Version 1.1.0
*
*Date  2007.07.30
*
*Description : This file provides several format_transformed functions, as following:
*
*              void int_to_string_dec( int input , char * str)
*                   This function is to convert an 'int' data 'input' to a string in decimalism, and the string
*                   converted is in 'str'.
*              void Uint_to_string_dec( unsigned int input, char * str )
*                   This function is to convert an 'unsigned int' data 'input' to a string in decimalism, and the
*                   string converted is in 'str'.
*              void int_to_string_hex( int input, char * str, int hex_flag )
*                   This function is to convert an 'int' data 'input' to a string in hex, and the string
*                   converted is in 'str'.
*
*
*Others : None at present.
*
*
* History :
*
*  <Author>         <time>      <version>     <description>
*
* Wangyugang       2007.07.30     1.1.0       build the file
*
*******************************************************************************************************************
*/


#include  <stdlib.h>
#include  "string.h"


#define  MASK_LOW4      0xf
#define  NEGATIVE       1
#define  POSITIVE       0
#define  HEX_x          'x'
#define  HEX_X          'X'








/*
******************************************************************************************************************
*
*Function Name : int_to_string_dec
*
*Description : This function is to convert an 'int' data 'input' to a string in decimalism, and the string
*              converted is in 'str'.
*
*Input : int input : 'int' data to be converted.
*        char * str : the start address of the string storing the converted result.
*
*Output : void
*
*call for :
*
*Others : None at present.
*
*******************************************************************************************************************
*/
void int_to_string_dec( int input , char * str)
{
	char stack[12];
	char sign_flag = POSITIVE ;      // 'sign_flag indicates wheater 'input' is positive or negative, default
	int i ;                           // value is 'POSITIVE'.
	int j ;



	if( input == 0 )
	{
		str[0] = '0';
		str[1] = '\0';                   // 'str' must end with '\0'
		return ;
	}

	if( input < 0 )                      // If 'input' is negative, 'input' is assigned to its absolute value.
	{
		sign_flag = NEGATIVE ;
		input = -input ;
	}

	for( i = 0; input > 0; ++i )
	{
		stack[i] = input%10 + '0';      // characters in reverse order are put in 'stack' .
		input /= 10;
	}                                   // at the end of 'for' loop, 'i' is the number of characters.


    j = 0;
	if( sign_flag == NEGATIVE )
		str[j++] = '-';		            // If 'input' is negative, minus sign '-' is placed in the head.
	for( --i  ; i >= 0; --i, ++j )
		str[j] = stack[i];
	str[j] = '\0';				        // 'str' must end with '\0'

	return;
}


void int_to_string_dec_ex( int input , char * str, unsigned length)
{
	int i ;                           // value is 'POSITIVE'.

	memset(str, ' ', length);
	str[length - 1] = '\0';			// 'str' must end with '\0'
	if( input == 0 )
	{
		str[length - 2] = '0';
		return ;
	}

	for( i = length - 2; input > 0; i--)
	{
		str[i] = input%10 + '0';      // characters in reverse order are put in 'stack' .
		input /= 10;
	}                                   // at the end of 'for' loop, 'i' is the number of characters.

	return;
}




/*
******************************************************************************************************************
*
*Function Name : Uint_to_string_dec
*
*Description : This function is to convert an 'unsigned int' data 'input' to a string in decimalism, and the
*              string converted is in 'str'.
*
*Input : int input : 'unsigned int' data to be converted.
*        char * str : the start address of the string storing the converted result.
*
*Output : void
*
*call for :
*
*Others : None at present.
*
*******************************************************************************************************************
*/
void Uint_to_string_dec( unsigned int input, char * str )
{
	char stack[11] ;
	int i ;
	int j ;


	if( input == 0 )
	{
		str[0] = '0';
		str[1] = '\0';                   // 'str' must end with '\0'
		return ;
	}

	for( i = 0; input > 0; ++i )
	{
		stack[i] = input%10 + '0';       // characters in reverse order are put in 'stack' .
		input /= 10;
	}                                    // at the end of 'for' loop, 'i' is the number of characters.

	for( --i, j = 0; i >= 0; --i, ++j )
		str[j] = stack[i];
	str[j] = '\0';		                 // 'str' must end with '\0'

	return;
}








/*
******************************************************************************************************************
*
*Function Name : int_to_string_hex
*
*Description : This function is to convert an 'int' data 'input' to a string in hex, and the string
*              converted is in 'str'.
*
*Input : int input : 'int' data to be converted.
*        char * str : the start address of the string storing the converted result.
*        int hex_flag : hex_flag is just a option to distinguish whether hex format is '0f' or '0F'.
*
*Output : void
*
*call for :
*
*Others : None at present.
*
*******************************************************************************************************************
*/
void int_to_string_hex( int input, char * str, int hex_flag )
{
	int i;
	int j;
	char stack[8];


	for( i = 0; i < 8; ++i )
	{
		if( hex_flag == HEX_X )
			stack[i] = "0123456789ABCDEF"[input&MASK_LOW4];
		else
			stack[i] = "0123456789abcdef"[input&MASK_LOW4];

		input >>= 4;
	}

	str[0] = '0';
	str[1] = hex_flag;                         // Hex format shoud start with "0x" or "0X".
	for( i = 7, j = 2; i >= 0; --i, ++j )
		str[j] = stack[i];
	str[j] = '\0';                             // 'str' must end with '\0'

	return;
}





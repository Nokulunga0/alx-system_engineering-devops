#include "main.h"

/************************* PRINT UNSIGNED NUMBER *************************/
/**
 * print_unsigned - Prints an unsigned number
 * @args: List a of arguments
 * @buffer: Buffer array to handle print
 * @flagChars:  Calculates active flags
 * @fieldWidth: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int print_unsigned(va_list args, char buffer[],
	int flagChars, int fieldWidth, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(args, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_unsgnd(0, i, buffer, flagChars, fieldWidth, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * print_octal - Prints an unsigned number in octal notation
 * @args: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flagChars:  Calculates active flags
 * @fieldWidth: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_octal(va_list args, char buffer[],
	int flagChars, int fieldWidth, int precision, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(args, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(fieldWidth);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flagChars & F_HASH && init_num != 0)
		buffer[i--] = '0';

	i++;

	return (write_unsgnd(0, i, buffer, flagChars, fieldWidth, precision, size));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @args: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flagChars:  Calculates active flags
 * @fieldWidth: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_hexadecimal(va_list args, char buffer[],
	int flagChars, int fieldWidth, int precision, int size)
{
	return (print_hexa(args, "0123456789abcdef", buffer,
		flagChars, 'x', fieldWidth, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @args: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flagChars:  Calculates active flags
 * @fieldWidth: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_hexa_upper(va_list args, char buffer[],
	int flagChars, int fieldWidth, int precision, int size)
{
	return (print_hexa(args, "0123456789ABCDEF", buffer,
		flagChars, 'X', fieldWidth, precision, size));
}

/************** PRINT HEXX NUM IN LOWER OR UPPER **************/
/**
 * print_hexa - Prints a hexadecimal number in lower or upper
 * @args: Lista of arguments
 * @map_to: Array of values to map the number to
 * @buffer: Buffer array to handle print
 * @flagChars:  Calculates active flags
 * @flag_ch: Calculates active flags
 * @fieldWidth: get width
 * @precision: Precision specification
 * @size: Size specifier
 * @size: Size specification
 * Return: Number of chars printed
 */
int print_hexa(va_list args, char map_to[], char buffer[],
	int flagChars, char flag_ch, int fieldWidth, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(args, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(fieldWidth);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = map_to[num % 16];
		num /= 16;
	}

	if (flagChars & F_HASH && init_num != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}

	i++;

	return (write_unsgnd(0, i, buffer, flagChars, fieldWidth, precision, size));
}

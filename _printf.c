#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: format.
 * Return: total count of printed chars.
 */
int _printf(const char *format, ...)
{
	int i, printed = 0, count_chars = 0;
	int flagChars, fieldWidth, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			/* write(1, &format[i], 1);*/
			count_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flagChars = get_flagChars(format, &i);
			fieldWidth = get_fieldWidth(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			printed = handle_print(format, &i, list, buffer,
				flagChars, fieldWidth, precision, size);
			if (printed == -1)
				return (-1);
			count_chars += printed;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(list);

	return (count_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}

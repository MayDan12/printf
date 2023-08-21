#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - The Printf function
 * DAniel wrote this
 * @format: format.
 * Return:The Printed chars.
 */
int _printf(const char *format, ...)
{
	int i, outputed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list form;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(form, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			/* write(1, &format[i], 1);*/
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &i);
			width = get_width(format, &i, form);
			precision = get_precision(format, &i, form);
			size = get_size(format, &i);
			++i;
			outputed = handle_print(format, &i, form, buffer,
				flags, width, precision, size);
			if (outputed == -1)
				return (-1);
			printed_chars += outputed;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(form);

	return (printed_chars);
}

/**
 * print_buffer - This function Prints the contents of the buffer if it exist
 * DAniel wrote this
 * @buffer: The Array of chars
 * @buff_ind: The Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}

#include "main.h"
/**
 * handle_print - This function Prints an argument based on its type
 * @fmt:The Formatted string used to print the arguments.
 * @list: The Liss of arguments to be printed.
 * written by DAniel and KAchi 2023
 * @ind: The ind.
 * @buffer: The Buffer array to handle print.
 * @flags: This Calculates active flags
 * @width: This get width.
 * @precision: Ths Precision specification
 * @size: The Size specifier
 * Return: 1 or 2 Success Excellence;
 */
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int gi, unknow_len = 0, printed_chars = -1;
	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (gi = 0; fmt_types[gi].fmt != '\0'; gi++)
		if (fmt[*ind] == fmt_types[gi].fmt)
			return (fmt_types[gi].fn(list, buffer, flags, width, precision, size));

	if (fmt_types[gi].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknow_len += write(1, &fmt[*ind], 1);
		return (unknow_len);
	}
	return (printed_chars);
}

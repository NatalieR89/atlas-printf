#include "main.h"
#include <stdarg.h>
#include <unistd.h> /* write func */

/* helper function prototypes */
void handle_char(va_list args, int *count);
void handle_string(va_list args, int *count);
void handle_int(va_list args, int *count);
void handle_uint(va_list args, int *count);

/**
 * _printf - Custom printf function
 * @format: Format string
 *
 * Return: Number of characters printed, excluding null byte
 */

int _printf(const char *format, ...)
{
	va_list args; /* va_list to hold variable arguments */
	int count = 0; /* counter for number characters printed */

	if (!format)
		return (-1); /* handle null str */

	/* initialize va_list with format argument */
	va_start(args, format);

	/* iterate over format string */
	while (*format)
	{
		if (*format == '%') /* looking for specifier */
		{
			format++; /* move to char after '%' */
			if (!*format)
				return (-1); /* handle single % */
			switch (*format) /* replaces if/else */
			{
				case 'c':
					handle_char(args, &count);
					break;

				case 's':
					handle_string(args, &count);
					break;

				case 'd':
				case 'i':
					handle_int(args, &count);
					break;

				case 'u':
					handle_uint(args, &count);
					break;

				case '%':
					write(STDOUT_FILENO, "%", 1);
					count++;
					break;

				default: /* for unknown specifier */
					write(1, "%", 1);
					write(1, format, 1); /* as is */
					count += 2;
					break;
			}
		}
		else
		{
			write(1, format, 1); /* regular char */
			count++;
		}
		format++; /* next char in format string */
	}

	va_end(args); /* clean up va_list */
	return (count);
}

/**
 * handle_char - Handles char specifier
 * @args: List of arguments
 * @count: Pointer to count of printed characters
 */
void handle_char(va_list args, int *count)
{
	char char_arg = va_arg(args, int);

	write(1, &char_arg, 1);
	(*count)++;
}

/**
 * handle_string - Handles string specifier
 * @args: List of arguments
 * @count: Pointer to count of printed characters
 */
void handle_string(va_list args, int *count)
{
	char *str_arg = va_arg(args, char *);

	if (!str_arg)
		str_arg = "(null)";
	while (*str_arg)
	{
		write(1, str_arg, 1);
		str_arg++;
		(*count)++;
	}
}

/**
 * handle_int - Handles integer specifier
 * @args: List of arguments
 * @count: Pointer to count of printed characters
 */
void handle_int(va_list args, int *count)
{
	int int_arg = va_arg(args, int);

	print_number(int_arg, count);
}

/**
 * handle_uint - Handles unsigned int specifier
 * @args: List of arguments
 * @count: Pointer to count of printed characters
 */
void handle_uint(va_list args, int *count)
{
	unsigned int uint_arg = va_arg(args, unsigned int);

	print_unsigned_int(uint_arg, count);
}

/**
 * print_number - Prints an integer
 * @n: Integer to be printed
 * @count: Pointer to count of printed characters
 */
void print_number(int n, int *count)
{
	unsigned int num;

	if (n < 0)
	{
		write(1, "-", 1);
		(*count)++;
		num = (unsigned int)(-n);
	}
	else
	{
		num = (unsigned int)n;
	}

	print_unsigned_int(num, count);
}

/**
 * print_unsigned_int - Prints an unsigned integer
 * @n: Unsigned integer to be printed
 * @count: Pointer to count of printed characters
 */
void print_unsigned_int(unsigned int n, int *count)
{
	char digit;

	if (n / 10)
	{
		print_unsigned_int(n / 10, count);
	}

	digit = (char)((n % 10) + '0');
	write(1, &digit, 1);
	(*count)++;
}

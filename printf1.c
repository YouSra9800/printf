#include <stdarg.h>
#include <unistd.h>
#include "main.h"
/**
  * find_function - function that finds formats for _printf
  * calls the corresponding function.
  * @format: format (character, string, integer, decimal)
  * Return: NULL or function associated ;
  */
int (*find_function(const char *format))(va_list)
{
	unsigned int i = 0;
	code_f find_f[] = {
		{"c", print_char},
		{"s", print_string},
		{"i", print_int},
		{"d", print_dec},
		{"r", print_rev},
		{"b", print_bin},
		{"u", print_unsig},
		{"o", print_octal},
		{"x", print_x},
		{"X", print_X},
		{"R", print_rot13},
		{NULL, NULL}
	};

	while (find_f[i].sc)
	{
		if (find_f[i].sc[0] == (*format))
			return (find_f[i].f);
		i++;
	}
	return (NULL);
}
/**
  * _printf - function that produces output according to a format.
  * @format: format (character, string, integer, decimal)
  * Return: size the output text;
  */
int _printf(const char *format, ...)
{
	va_list hy;
	int (*f)(va_list);
	unsigned int i = 0, print = 0;

	if (format == NULL)
		return (-1);
	va_start(hy, format);
	while (format[i])
	{
		while (format[i] != '%' && format[i])
		{
			_putchar(format[i]);
			print++;
			i++;
		}
		if (format[i] == '\0')
			return (print);
		f = find_function(&format[i + 1]);
		if (f != NULL)
		{
			print += f(hy);
			i += 2;
			continue;
		}
		if (!format[i + 1])
			return (-1);
		_putchar(format[i]);
		print++;
		if (format[i + 1] == '%')
			i += 2;
		else
			i++;
	}
	va_end(hy);
	return (print);
}

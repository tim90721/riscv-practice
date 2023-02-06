#include <stdarg.h>
#include <stdio.h>
#include <types.h>

#include <compiler.h>

#include "uart.h"

#define PB_NUM		10
#define PB_LEN		256

static char print_buffer[PB_NUM][PB_LEN];
static u8 pb_idx;

static void format_signed(char *buf, u32 *pos, u32 size,
			  char fmt, u8 longarg, va_list args)
{
	long num;
	int digits = 1;
	int i;
	int n;

	if (longarg == 1)
		num = va_arg(args, long);
	else
		num = va_arg(args, int);

	if (num < 0) {
		num = -num;
		if (*pos < size)
			buf[(*pos)] = '-';
		(*pos)++;
	}

	for (n = num; n /= 10; digits++)
		;
	for (i = digits - 1; i >= 0; i--) {
		if ((*pos) + i < size)
			buf[(*pos) + i] = '0' + num % 10;
		num /= 10;
	}

	(*pos) += digits;
}

static void format_unsigned(char *buf, u32 *pos, u32 size,
			    char fmt, u8 longarg, va_list args)
{
	unsigned long num;
	int digits;
	int i;
	int n;

	if (fmt == 'p')
		longarg = 1;

	if (longarg == 1) {
		num = va_arg(args, unsigned long);
		digits = sizeof(unsigned long);
	} else {
		num = va_arg(args, unsigned int);
		digits = sizeof(unsigned int);
	}

	switch (fmt) {
	case 'p':
		longarg = 1;

		if (*pos < size)
			buf[(*pos)] = '0';
		(*pos)++;

		if (*pos < size)
			buf[(*pos)] = 'x';
		(*pos)++;

		/* fallthrough */
	case 'x':
		digits = digits * 2 - 1;

		for (i = digits; i >= 0; i--) {
			n = (num >> (4 * i)) & 0xF;
			if (*pos < size)
				buf[*pos] = (n < 10) ? ('0' + n) : ('a' + n - 10);

			(*pos)++;
		}

		break;
	case 'u':
		digits = 1;

		for (n = num; n /= 10; digits++)
			;
		for (i = digits - 1; i >= 0; i--) {
			if ((*pos) + i < size)
				buf[(*pos) + i] = '0' + num % 10;
			num /= 10;
		}

		(*pos) += digits;
		break;
	}
}

static int decode_format(char *buf, u32 *pos, u32 size, const char *fmt, va_list args)
{
	const char *old_fmt = fmt;
	const char *s;
	u8 longarg = 0;

	if (*fmt == 'l') {
		longarg = 1;
		fmt++;
	}

	if (*fmt == 'l') {
		longarg = 2;
		fmt++;
	}

	switch (*fmt) {
	case 'd':
		format_signed(buf, pos, size, *fmt, longarg, args);
		break;
	case 's':
		s = va_arg(args, const char *);

		while (*s) {
			if (*pos < size)
				buf[(*pos)] = *s;

			(*pos)++;
			s++;
		}
		break;
	case 'c':
		if (*pos < size)
			buf[(*pos)] = va_arg(args, int);
		(*pos)++;

		break;
	case '%':
		if (*pos < size)
			buf[(*pos)] = '%';
		(*pos)++;
		break;
	default:
		format_unsigned(buf, pos, size, *fmt, longarg, args);
	}

	fmt++;

	return fmt - old_fmt;
}

static int vsnprintf(char *buf, u32 size, const char *fmt, va_list args)
{
	u8 format = 0;
	u32 pos = 0;

	if (unlikely(size > PB_LEN))
		return 0;

	while (*fmt) {
		if (format) {
			fmt += decode_format(buf, &pos, size, fmt, args);
			format = 0;
		} else if (*fmt == '%') {
			format = 1;
			fmt++;
		} else {
			if (pos < size)
				buf[pos] = *fmt++;
			pos++;
		}
	}

	if (pos < size)
		buf[pos] = '\0';
	else
		buf[size - 1] = '\0';

	return pos;
}

int vscnprintf(char *buf, u32 size, const char *fmt, va_list args)
{
	u32 done;

	if (unlikely(!size))
		return 0;

	done = vsnprintf(buf, size, fmt, args);

	if (done < size)
		return done;

	return size - 1;
}

static int vprintf(const char *fmt, va_list args)
{
	char *buf;
	u32 done;

	buf = print_buffer[pb_idx];
	pb_idx = (pb_idx + 1) % PB_NUM;

	done = vscnprintf(buf, PB_LEN, fmt, args);

	uart_puts(buf);

	return done;
}

int printf(const char *fmt, ...)
{
	va_list args;
	int done;

	va_start(args, fmt);
	done = vprintf(fmt, args);
	va_end(args);

	return done;
}

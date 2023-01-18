#include <stdarg.h>
#include <stdio.h>
#include <types.h>

#include <compiler.h>

#include "uart.h"

#define PB_NUM		10
#define PB_LEN		256

static int decode_format(char *buf, u32 *pos, u32 size, const char *fmt, va_list args)
{
	const char *old_fmt = fmt;
	const char *s;
	long num;
	int digits;
	int n;
	int i;
	u8 longarg = 0;

	if (*fmt == 'l') {
		longarg = 1;
		fmt++;
	}

	switch (*fmt) {
	case 'p':
		longarg = 1;
		if (*pos < size)
			buf[(*pos)] = '0';
		(*pos)++;
		if (*pos < size)
			buf[(*pos)] = 'x';
		(*pos)++;
	case 'x':
		num = longarg ? va_arg(args, long) : va_arg(args, int);
		digits = 2 * (longarg ? sizeof(long) : sizeof(int)) - 1;

		for (i = digits; i >= 0; i--) {
			n = (num >> (4 * i)) & 0xF;
			if (*pos < size)
				buf[*pos] = (n < 10) ? ('0' + n) : ('a' + n - 10);

			(*pos)++;
		}
		break;
	case 'd':
		num = longarg ? va_arg(args, long) : va_arg(args, int);
		digits = 1;

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
		longarg = 0;
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

static int vscnprintf(char *buf, u32 size, const char *fmt, va_list args)
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
	/* TODO: replace with a global buffer when linker script added */
	char buf[PB_LEN];
	u32 done;

	done = vscnprintf(buf, PB_LEN, fmt, args);

	uart_puts(buf);

	return done;
}

int printf(const char *fmt, ...)
{
	va_list args;
	int done;

	va_start(args, fmt);
	//done = __vprintf(
	//vprintf -> (vprintf_default) -> vprintf_emit(trigger logd) -> vprintf_store -> printk_sprint -> vscnprintf -> vsnprintf
	done = vprintf(fmt, args);
	va_end(args);

	return done;
}

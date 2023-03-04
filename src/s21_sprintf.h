#ifndef SRC_S21_SPRINTF_H_
#define SRC_S21_SPRINTF_H_
#include <locale.h>

#include "s21_string.h"
typedef struct {
  bool minus;
  bool plus;
  bool space;
  bool zero;
  bool hash;
  int precision;
  int is_precision_set;
  int width;
  char length;
  char specifier;
} flags;

int s21_sprintf(char *str, const char *format, ...);

void all_number_to_string(int64_t val, char *ret, int base);
void unsigned_number_to_string(uint64_t val, char *ret, int base);
bool check_integer_specifier(char c);
bool is_all_zeroes(char *buff);
void to_upper(char *str);
void prepend_ox(char *buff, flags flag);
void double_to_string(long double val, char *ret, flags flag);
void prepend_mantiss(char *str, int pow, char sign);
void remove_trailing_zeroes(char *buff);

const char *get_flags(const char *format, flags *flag);
const char *get_width(const char *format, flags *flag, va_list va);
const char *get_precision(const char *format, flags *flag, va_list va);
const char *get_length(const char *format, flags *flag);

void handle_value(flags flag, char *buff, va_list va);
void get_int(flags flag, char *buff, va_list va);
void get_unsigned(flags flag, char *buff, va_list va);
void get_octal(flags flag, char *buff, va_list va);
void get_hex(flags flag, char *buff, va_list va);
void get_char(flags flag, char *buff, va_list va);
void get_string(flags flag, char *buff, va_list va);
void get_pointer(flags flag, char *buff, va_list va);
void get_float(flags flag, char *buff, va_list va);
void get_mantiss(flags flag, char *buff, va_list va);
void get_float_g_G(flags flag, char *buff, va_list va);

void format_precision(char *buff, flags flag);
void format_flags(char *buff, flags flag);
void format_gG_precision(char *buff, int precision);
void format_wchar(flags flag, char *buff, wchar_t w_c);
void format_char(flags flag, char *buff, char c);
void format_string(flags flag, char *buff, char *str);
void format_wide_string(flags flag, char *buff, wchar_t *wstr);

#endif  //  SRC_S21_SPRINTF_H_
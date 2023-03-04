
#include "s21_sprintf.h"

int s21_sprintf(char *str, const char *format, ...) {
  flags flag = {0};
  va_list va;
  va_start(va, format);
  char *string_begin = str;
  while (*format) {
    if (*format != '%') {
      *str++ = *format++;
      continue;
    } else {
      format++;
      s21_memset(&flag, 0, sizeof(flags));
    }
    format = get_flags(format, &flag);
    format = get_width(format, &flag, va);
    format = get_precision(format, &flag, va);
    format = get_length(format, &flag);
    flag.specifier = *format;
    format++;
    char buffer[BUFF_SIZE] = {'\0'};
    handle_value(flag, buffer, va);
    for (int i = 0; buffer[i]; i++, str++) *str = buffer[i];
    if (flag.specifier == 'n') {
      int *ret = va_arg(va, int *);
      *ret = str - string_begin;
    }
  }
  *str = '\0';
  va_end(va);
  return str - string_begin;
}

const char *get_flags(const char *format, flags *flag) {
  while (*format == '-' || *format == '+' || *format == ' ' || *format == '0' ||
         *format == '#') {
    switch (*format) {
      case '0':
        flag->zero = true;
        break;
      case '-':
        flag->minus = true;
        break;
      case '+':
        flag->plus = true;
        break;
      case ' ':
        flag->space = true;
        break;
      case '#':
        flag->hash = true;
        break;
    }
    format++;
  }
  return format;
}

const char *get_width(const char *format, flags *flag, va_list va) {
  if (*format == '*') {
    format++;
    flag->width = va_arg(va, int);
  } else if (s21_isdigit(*format)) {
    char tmp[BUFF_SIZE] = {'\0'};
    for (int i = 0; s21_isdigit(*format); i++, format++) tmp[i] = *format;
    flag->width = s21_atoi(tmp);
  }
  return format;
}

const char *get_precision(const char *format, flags *flag, va_list va) {
  if (*format == '.') {
    flag->is_precision_set = true;
    format++;
  }
  if (*format == '*') {
    format++;
    flag->precision = va_arg(va, int);
  }
  if (s21_isdigit(*format)) {
    char tmp[BUFF_SIZE] = {'\0'};
    for (int i = 0; s21_isdigit(*format); i++, format++) tmp[i] = *format;
    flag->precision = s21_atoi(tmp);
  }
  return format;
}

const char *get_length(const char *format, flags *flag) {
  switch (*format) {
    case 'h':
      flag->length = 'h';
      format++;
      break;
    case 'l':
      flag->length = 'l';
      format++;
      break;
    case 'L':
      flag->length = 'L';
      format++;
  }
  return format;
}

void handle_value(flags flag, char *buffer, va_list va) {
  if (flag.specifier == 'd' || flag.specifier == 'i')
    get_int(flag, buffer, va);
  else if (flag.specifier == 'u')
    get_unsigned(flag, buffer, va);
  else if (flag.specifier == 'o')
    get_octal(flag, buffer, va);
  else if (flag.specifier == 'x' || flag.specifier == 'X')
    get_hex(flag, buffer, va);
  else if (flag.specifier == '%')
    buffer[0] = '%';
  else if (flag.specifier == 'c')
    get_char(flag, buffer, va);
  else if (flag.specifier == 's')
    get_string(flag, buffer, va);
  else if (flag.specifier == 'p')
    get_pointer(flag, buffer, va);
  else if (flag.specifier == 'f')
    get_float(flag, buffer, va);
  else if (flag.specifier == 'e' || flag.specifier == 'E')
    get_mantiss(flag, buffer, va);
  else if (flag.specifier == 'g' || flag.specifier == 'G')
    get_float_g_G(flag, buffer, va);
  if (flag.specifier == 'G' || flag.specifier == 'E' || flag.specifier == 'X')
    to_upper(buffer);
}

void get_int(flags flag, char *buffer, va_list va) {
  int64_t val = va_arg(va, int64_t);

  switch (flag.length) {
    case 0:
      val = (int32_t)val;
      break;
    case 'h':
      val = (int16_t)val;
  }
  all_number_to_string(val, buffer, 10);
  format_precision(buffer, flag);
  format_flags(buffer, flag);
}

void all_number_to_string(int64_t val, char *ret, int base) {
  char tmp[BUFF_SIZE] = {'\0'};
  int idx = BUFF_SIZE - 2;

  bool neg = val < 0 ? 1 : 0;
  val = neg ? -val : val;

  if (val == 0) tmp[idx] = '0';

  while (val > 0) {
    idx--;
    tmp[idx] = "0123456789abcdef"[val % base];
    val /= base;
  }
  for (int j = 0; tmp[idx]; idx++, j++) {
    if (neg && j == 0) {
      ret[j++] = '-';
    }

    ret[j] = tmp[idx];
  }
}

void format_precision(char *buffer, flags flag) {
  char tmp[BUFF_SIZE] = {'\0'};

  int sign = 0;
  int len = s21_strlen(buffer);

  if (buffer[0] == '-') {
    tmp[0] = '-';
    len--;
    sign = 1;
  }

  if (flag.precision > len) {
    int idx;
    for (idx = sign; idx < flag.precision - len + sign; idx++) tmp[idx] = '0';

    for (int i = sign; buffer[i]; i++, idx++) tmp[idx] = buffer[i];

    s21_strcpy(buffer, tmp);
  }

  if (flag.is_precision_set && flag.precision == 0 &&
      check_integer_specifier(flag.specifier) && buffer[0] == '0')
    buffer[0] = '\0';
}

bool check_integer_specifier(char c) {
  char specs[] = {'d', 'i', 'o', 'u', 'x', 'X'};
  bool res = false;
  for (s21_size_t i = 0; i < sizeof(specs); i++) {
    if (specs[i] == c) {
      res = true;
      break;
    }
  }
  return res;
}

void format_flags(char *buffer, flags flag) {
  char tmp[BUFF_SIZE + 1] = {'\0'};
  if (flag.plus && flag.specifier != 'u') {
    tmp[0] = buffer[0] == '-' ? buffer[0] : '+';
    s21_strcpy(tmp + 1, buffer[0] == '-' ? buffer + 1 : buffer);
    s21_strcpy(buffer, tmp);
  } else if (flag.space && buffer[0] != '-' && flag.specifier != 'u') {
    tmp[0] = ' ';
    s21_strcpy(tmp + 1, buffer);
    s21_strcpy(buffer, tmp);
  }
  if (flag.width > (int)s21_strlen(buffer)) {
    int idx = flag.width - s21_strlen(buffer);
    if (!flag.minus) {
      s21_memset(tmp, flag.zero ? '0' : ' ', idx);
      s21_strcpy(tmp + idx, buffer);
    } else {
      s21_strcpy(tmp, buffer);
      s21_memset(tmp + s21_strlen(tmp), ' ', idx);
    }
    s21_strcpy(buffer, tmp);
  }
}

void unsigned_number_to_string(uint64_t val, char *ret, int base) {
  char buf[BUFF_SIZE + 1] = {'\0'};
  int idx = BUFF_SIZE - 1;
  if (val == 0) {
    buf[idx] = '0';
    idx--;
  }

  for (; val && idx; --idx, val /= base)
    buf[idx] = "0123456789abcdef"[val % base];
  for (int j = 0; buf[idx + 1]; idx++, j++) ret[j] = buf[idx + 1];
}

void get_unsigned(flags flag, char *buffer, va_list va) {
  uint64_t val = va_arg(va, uint64_t);
  switch (flag.length) {
    case 'h':
      val = (uint16_t)val;
      break;
    case 'l':
      val = (uint64_t)val;
      break;
    case 0:
      val = (uint32_t)val;
  }
  unsigned_number_to_string(val, buffer, 10);
  format_precision(buffer, flag);
  format_flags(buffer, flag);
}

void get_octal(flags flag, char *buffer, va_list va) {
  buffer[0] = '0';
  all_number_to_string(va_arg(va, int64_t), buffer + flag.hash, 8);
  format_precision(buffer, flag);
  format_flags(buffer, flag);
}

void to_upper(char *str) {
  while (*str) {
    if (*str >= 'a' && *str <= 'z') *str = *str - 'a' + 'A';
    str++;
  }
}

bool is_all_zeroes(char *buffer) {
  for (int i = 0; buffer[i]; i++)
    if (buffer[i] != '0') return false;
  return true;
}

void get_hex(flags flag, char *buffer, va_list va) {
  uint64_t val = va_arg(va, uint64_t);
  switch (flag.length) {
    case 0:
      val = (uint32_t)val;
      break;
    case 'h':
      val = (uint16_t)val;
      break;
    case 'l':
      val = (uint64_t)val;
      break;
  }
  unsigned_number_to_string(val, buffer, 16);
  format_precision(buffer, flag);
  if (flag.hash) {
    prepend_ox(buffer, flag);
  }
  format_flags(buffer, flag);
}

void prepend_ox(char *buffer, flags flag) {
  if (!is_all_zeroes(buffer) || flag.specifier == 'p') {
    s21_memmove(buffer + 2, buffer, s21_strlen(buffer));
    buffer[0] = '0';
    buffer[1] = 'x';
  }
}

void get_char(flags flag, char *buffer, va_list va) {
  if (flag.length == 'l') {
    wchar_t w_c;
    w_c = va_arg(va, wchar_t);
    format_wchar(flag, buffer, w_c);
  } else {
    char c;
    c = va_arg(va, int);
    format_char(flag, buffer, c);
  }
}

void format_wchar(flags flag, char *buffer, wchar_t w_c) {
  if (!flag.minus && flag.width) {
    for (int i = 0; i < flag.width; i++) {
      buffer[i] = ' ';
      if (i == flag.width - 1) wcstombs(buffer, &w_c, BUFF_SIZE);
    }
  } else if (flag.width) {
    wcstombs(buffer, &w_c, BUFF_SIZE);
    for (int i = s21_strlen(buffer); i < flag.width; i++) buffer[i] = ' ';
  } else {
    wcstombs(buffer, &w_c, BUFF_SIZE);
  }
}
void format_char(flags flag, char *buffer, char c) {
  if (!flag.minus && flag.width) {
    for (int i = 0; i < flag.width; i++) {
      buffer[i] = ' ';
      if (i == flag.width - 1) buffer[i] = c;
    }
  } else if (flag.width) {
    buffer[0] = c;
    for (int i = 1; i < flag.width; i++) buffer[i] = ' ';
  } else {
    buffer[0] = c;
  }
}

void get_string(flags flag, char *buffer, va_list va) {
  if (flag.length == 'l') {
    wchar_t *wstr = va_arg(va, wchar_t *);
    format_wide_string(flag, buffer, wstr);
  } else {
    char *str = va_arg(va, char *);
    format_string(flag, buffer, str);
  }
}
void format_string(flags flag, char *buffer, char *str) {
  char tmp[BUFF_SIZE] = {'\0'};
  s21_strcpy(tmp, str);
  if (flag.is_precision_set) tmp[flag.precision] = '\0';

  int shift = flag.width - s21_strlen(tmp);
  int len = s21_strlen(tmp);

  if (flag.minus && shift > 0) {
    s21_strcpy(buffer, tmp);
    s21_memset(buffer + len, ' ', shift);
  } else if (shift > 0) {
    s21_memset(buffer, ' ', shift);
    s21_strcpy(buffer + shift, tmp);
  } else {
    s21_strcpy(buffer, tmp);
  }
}
void format_wide_string(flags flag, char *buffer, wchar_t *wstr) {
  char tmp[BUFF_SIZE] = {'\0'};
  char str[BUFF_SIZE] = {'\0'};

  wcstombs(str, wstr, BUFF_SIZE);
  s21_strcpy(tmp, str);
  if (flag.is_precision_set) tmp[flag.precision] = '\0';

  int shift = flag.width - s21_strlen(tmp);
  int len = s21_strlen(tmp);

  if (flag.minus && shift > 0) {
    s21_strcpy(buffer, tmp);
    s21_memset(buffer + len, ' ', shift);
  } else if (shift > 0) {
    s21_memset(buffer, ' ', shift);
    s21_strcpy(buffer + shift, tmp);
  } else {
    s21_strcpy(buffer, tmp);
  }
}

void get_pointer(flags flag, char *buffer, va_list va) {
  unsigned_number_to_string(va_arg(va, uint64_t), buffer, 16);
  format_precision(buffer, flag);
  prepend_ox(buffer, flag);
  format_flags(buffer, flag);
}

void get_float(flags flag, char *buffer, va_list va) {
  long double val = 0;
  if (flag.length == 'L') {
    val = va_arg(va, long double);
  } else {
    val = va_arg(va, double);
  }

  if (!flag.is_precision_set) {
    flag.precision = 6;
  }

  double_to_string(val, buffer, flag);
  format_flags(buffer, flag);
}
void double_to_string(long double val, char *ret, flags flag) {
  char buffer[BUFF_SIZE] = {'\0'};
  int idx = BUFF_SIZE - 2;
  bool neg = val < 0 ? 1 : 0;
  val = neg ? val * -1 : val;
  long double l = 0, r = modfl(val, &l);
  if (flag.precision == 0) {
    l = roundl(val);
    r = 0;
  }
  char fractions[BUFF_SIZE] = {'\0'};
  for (int i = 0; i < flag.precision; i++) {
    r = r * 10;
    fractions[i] = (int)r + '0';
  }
  long long right = roundl(r), left = l;
  if (!right) {
    for (int i = 0; i < flag.precision; idx--, i++) buffer[idx] = '0';
  } else {
    for (int i = s21_strlen(fractions); right || i > 0; right /= 10, idx--, i--)
      buffer[idx] = (int)(right % 10 + 0.05) + '0';
  }
  if ((flag.is_precision_set && flag.precision != 0) || (int)r ||
      (!flag.is_precision_set && val == 0) || s21_strlen(fractions))
    buffer[idx--] = '.';
  if (!left) {
    buffer[idx] = '0';
    idx--;
  } else {
    for (; left; left /= 10, idx--) buffer[idx] = (int)(left % 10) + '0';
  }
  for (int i = 0; buffer[idx + 1]; idx++, i++) {
    if (neg && i == 0) {
      ret[i] = '-';
      i++;
    }
    ret[i] = buffer[idx + 1];
  }
}

void get_mantiss(flags flag, char *buffer, va_list va) {
  long double val = 0;
  if (flag.length == 'L') {
    val = va_arg(va, long double);
  } else {
    val = va_arg(va, double);
  }
  int pow = 0;
  char sign = (int)val == 0 ? '-' : '+';

  if ((int)val - val) {
    while ((int)val == 0) {
      pow++;
      val *= 10;
    }
  } else {
    sign = '+';
  }
  while ((int)val / 10 != 0) {
    pow++;
    val /= 10;
  }

  if (!flag.is_precision_set) flag.precision = 6;
  double_to_string(val, buffer, flag);
  prepend_mantiss(buffer, pow, sign);
  format_flags(buffer, flag);
}

void prepend_mantiss(char *str, int pow, char sign) {
  int len = s21_strlen(str);
  str[len] = 'e';
  str[len + 1] = sign;
  str[len + 3] = pow % 10 + '0';
  pow /= 10;
  str[len + 2] = pow % 10 + '0';
  str[len + 4] = '\0';
}

void get_float_g_G(flags flag, char *buffer, va_list va) {
  long double val = 0;
  if (flag.length == 'L') {
    val = va_arg(va, long double);
  } else {
    val = va_arg(va, double);
  }

  if (!flag.is_precision_set) {
    flag.precision = 6;
  }
  if (flag.precision == 0) flag.precision = 1;
  int precision = flag.precision;
  long double m_val = val;
  int pow = 0;
  if ((int)val - val) {
    while ((int)m_val == 0) {
      pow++;
      m_val *= 10;
    }
  }
  if (pow > 4) {
    flag.precision = 0;
    double_to_string(m_val, buffer, flag);
  } else {
    flag.precision = 10;
    double_to_string(val, buffer, flag);
  }
  format_gG_precision(buffer, precision);
  if (pow > 4) prepend_mantiss(buffer, pow, '-');
  remove_trailing_zeroes(buffer);
  format_flags(buffer, flag);
}

void remove_trailing_zeroes(char *buffer) {
  int len = s21_strlen(buffer);
  char *dot = s21_strchr(buffer, '.');
  if (dot) {
    for (int i = len - 1; buffer[i] != '.'; i--) {
      if (buffer[i] == '0')
        buffer[i] = '\0';
      else
        break;
    }
    if (dot[1] == '\0') dot[0] = '\0';
  }
}

void format_gG_precision(char *buffer, int precision) {
  int sig_digs = 0;
  s21_size_t len = s21_strlen(buffer);
  int not_zero_found = 0;
  for (s21_size_t i = 0; i < s21_strlen(buffer); i++) {
    if ((buffer[i] == '0' && !not_zero_found) || buffer[i] == '.')
      continue;
    else
      not_zero_found = 1;

    if (s21_isdigit(buffer[i]) && not_zero_found) {
      sig_digs++;
    }
    if (sig_digs == precision && i + 1 < len) {
      int next = buffer[i + 1] == '.' ? 2 : 1;
      buffer[i] =
          buffer[i + next] - '0' > 5 ? (char)(buffer[i] + 1) : buffer[i];
      buffer[i + 1] = '\0';
      break;
    }
  }
}

int s21_isdigit(char c) { return (c >= '0' && c <= '9'); }
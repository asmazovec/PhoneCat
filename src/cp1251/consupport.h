/* MIT License
 * Copyright (c) Alexander Mazovets
*/ 


#ifndef CONSUPPORT_H_
#define CONSUPPORT_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <assert.h>


/* ���� ������������ �������. */
char get_specific (const char *purpose);

/* ���� ������. */
char *get_line         (const char *prompt, const char *def, int length);
char *get_line_capital (const char *prompt, const char *def, int length);

/* ���� �����. */
char *get_word         (const char *prompt, const char *def, int length);
char *get_word_capital (const char *prompt, const char *def, int length);

/* ���� �����. */
char get_key           (const char *prompt, char def, const char *purpose);

/* ���� ������������������ �����. */
int *get_sign_set (const char *prompt, int def, int count);
int *get_number_set (const char *prompt, const char *purpose, int count, int def, ...);

#endif /* CONSUPPORT_H_ */

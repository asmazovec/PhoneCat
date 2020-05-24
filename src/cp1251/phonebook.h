/* MIT License 
 * Copyright (c) Alexander Mazovets
 * */

#ifndef PHONEBOOK_H_
#define PHONEBOOK_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <assert.h>


/* ����� ��������. */
typedef struct {        
    int locale;         /// ������������� ������������� (4 - 1 ������).
    int service;        /// ��� ������ (3 �������).
    int provider;       /// ��� ���������� ������ (3 �������). 
    int abonent;        /// ������������� �������� (4 �������).
} phone;

/* ��������� ������ � �����. */
typedef struct record {     
    char* nickname;     /// ��������� ��������� ������ ��������.  
    phone phonenumber;  /// ����� ��������.
    struct record *next;/// ��������� �� ��������� ������ �� ��������.
} record;

/* ��������� ���������� �����. */
typedef struct book {
    char character;     /// ����� ������� �������� �����.
    record *node;       /// ������ ������ �� ��������, �������������� ��������.
    struct book *next;  /// ��������� �� ��������� �������� �����.
    struct book *prev;  /// ��������� �� ���������� �������� �����.
} book;


/* ����������� ������ ��������. */
phone get_phone (
        int locale,
        int service,
        int provider,
        int abonent);

/* ���������� ������ ��������. 
 * ���� ����������, ���������� 0, ����� 1.
 * */
int phone_cmp (phone phone1, phone phone2);

/* ������� ����� �������� inline */
int print_phone (phone current);



/* ����������� ������ ���������� �����. */
record *get_record (
        char  *name,
        phone number); 

/* ����������� ������������ ������. 
 * ���������� ��������� �� ����������������� ������.
 * */
record *update_record (
        record *new_record,
        book *cur_book,
        char   *new_name,
        phone  new_number);

/* ���������� 2 ������.
 * ���� ����������, ���������� 0, ����� 1.
 * */
int record_cmp (record record1, record record2);

/* ������� ���������� � ������ inline. */
int print_record (record current, int size);



/* �������������� ����� �����. */
book *init_book (void);

/* ������� ��������, ��������������� ������ ����� ������� ������ �
 * ���������� �����. 
 * ���������� ��������� �� ��������, ���� ����� ����������, ����� NULL.
 * */
book *find_page (char character, book cur_book);

/* ��������� �������� ����� ������� � ����� � ������������������ �������. 
 * ���������� ��������� �� ��������. 
 * */
book *add_page (char character, book *cur_book);

/* �������� �������� �� ���������� �����, �� ��������� ��������� size
 * ��������.
 * */
int print_page (book cur_page, int size);

/* ������������� ��� ���������� �����, �� ��������� ��������� size
 * ��������. 
 * */
int print_book (book cur_book, int size);

/* ������� ������, ��������������� ������� ������ � ���������� �����.
 * ���������� ��������� �� ������, ���� ����� ����������, ����� NULL.
 * */
record *find_record (record required, book cur_book);

/* ������� ��� ������ �� ���������� � ���������� �����. ���������
 * ������� - ��������� NULL.
 * */
record **find_nickname (char *nickname, book cur_book);

/* �������� ��� ������ �������� �� �������� �����. */
int print_nickname (char *nickname, book cur_book, int size);

/* ������� ������ � ���������� �����. 
 * ���������� ��������� �� ��� ������ � �����.
 * */
record *add_record (record current, book *cur_book);

/* ������� ������ �� ���������� �����. 
 * ���� �����, ���������� 0, ����� 1.
 * */
int delete_record (record *removable, book *page);

/* ��������� �����, ���������� ������. */
int close_book (book *cur_book);

/* ��������� ���������� ����� �� �����. */
int upload_book (const char *path, int size, book *new_book);

/* ���������� ���������� ����� �� ����. 
 * ���� �����, ���������� 0, ����� 1.
 * */
int write_book (book cur_book, const char* path);


#endif /* PHONEBOOK_H_ */

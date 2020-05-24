/* MIT License
 *
 * Copyright (c) 2020 Alexander Mazovets
 * */

#ifndef MAIN_H_
#define MAIN_H_

#include "phonebook.h"
#include "consupport.h"


typedef struct {
    book *cur_book;
    char *path;
} bookpath;

/* ���������� ���������� � ����� ����� ������.
 * size - ������ ������ ���������� ������.
 * */
record *path_ask_record (const char *def_name, phone *def_phone, int size) {
    int locale   = 0;       /// ������������� ������������� (4 - 1 ������).
    int service  = 0;       /// ��� ������ (3 �������).
    int provider = 0;       /// ��� ���������� ������ (3 �������). 
    int abonent  = 0;       /// ������������� �������� (4 �������).

    char *new_name;
    int *number;

    if (def_name[0]=='\0') {
        new_name = get_line ("\n����� ���: ", "?NoName", 256); 
    } else {
        new_name = get_line ("\n����� ���   (enter - ����������): ", def_name, 256); 
    }
    if (NULL==def_phone) {
        number = get_sign_set ("����� ����� ��������: ", -1, 14);
    } else {
        number = get_sign_set ("����� ����� (enter - ����������): ", -1, 14);
    }
    phone new_phone;
    if (NULL==def_phone || number[0]!=-1) {
        int i = 13;
        while (i+1>0) {
            if (number[i]!=-1) { break; }
            i--;
        }

        int dec = 1; int cur = i; i -= 4;
        while (cur>i && cur+1>0) {
            abonent += number[cur]*dec;
            dec*=10;
            cur--;
        }

        dec = 1; cur = i; i -= 3;
        while (cur>i && cur+1>0) {
            provider += number[cur]*dec;
            dec*=10;
            cur--;
        }

        dec = 1; cur = i; i -= 3;
        while (cur>i && cur+1>0) {
            service += number[cur]*dec;
            dec*=10;
            cur--;
        }

        dec = 1; cur = i; i -= 4;
        while (cur>i && cur+1>0) {
            locale += number[cur]*dec;
            dec*=10;
            cur--;
        }
        new_phone = get_phone (locale, service, provider, abonent);
    } else {
        new_phone = *def_phone;
    }

    record *new_record = get_record (new_name, new_phone); 

    printf ("\n");
    print_record (*new_record, size);
    printf ("\n"); 
    return new_record;
}

/* �������� ����� �� ���� � �������� �� ��������. */
int close_path (bookpath *catalog, int cat_size, int cat_cur)  {
    close_book (catalog[cat_cur].cur_book);
    for (int i = 0; i<cat_size-1; i++) {
        catalog[cat_cur+i] = catalog[cat_cur+i+1]; }
    return 0;
}

int path_print_page (char character, book cur_book, int size) {
    book *cur_page = find_page (character, cur_book); if (NULL==cur_page) { return 1; } 
    print_page (*cur_page, size); 
    return 0;
}

int path_update_record (book *cur_book) {
    char *line = get_line ("\n����� ������ �� ����� ����� (enter - ������): ", "", 256);
    if (line[0]=='\0') { printf ("\n������ ��������������\n"); return 1; }
    record *new_record;

    record **f_records = find_nickname (line, *cur_book);
    int i = 0;
    int cur = 0;
    while (f_records[i]) {
        printf ("%3d :: ", i+1);
        print_record (*f_records[i], 15);
        printf ("\n", i);
        i++;
    }
    free (line);
    if (i==0) {
        printf ("\n�� �������� ��� ����� ��� ������ � ����� ������ �� ����������\n");
    } else if (i==1) {
        new_record = path_ask_record (f_records[0]->nickname, &f_records[0]->phonenumber, 15); 
        update_record (f_records[0], cur_book, new_record->nickname, new_record->phonenumber);
    } else {
        cur = *get_number_set ("\n����� ������ �� ������ (enter - ������): ", "\n0123456789", 1, 0, 0, i+1);
        if (cur<1 || cur>i) { printf ("\n������ ��������������\n"); return 1; }
        
        new_record = path_ask_record (f_records[cur-1]->nickname, &f_records[cur-1]->phonenumber, 15); 
        update_record (f_records[cur-1], cur_book, new_record->nickname, new_record->phonenumber);
    }
    return 0;
}

int path_delete_record (book *cur_book) {
    char *line = get_line ("\n����� ������ �� ����� ����� (enter - ������): ", "", 256);
    if (line[0]=='\0') { printf ("\n������ ��������\n"); return 1; }
    record *new_record;

    record **f_records = find_nickname (line, *cur_book);
    int i = 0;
    int cur = 0;
    while (f_records[i]) {
        printf ("%3d :: ", i+1);
        print_record (*f_records[i], 15);
        printf ("\n", i);
        i++;
    }
    free (line);
    
    book *cur_page;
    char key;
    if (i==0) {
        printf ("\n�� �������� ��� ����� ��� ������ � ����� ������ �� ����������\n");
    } else if (i==1) {
        key = get_key ("\n������� ������? (y/N): ", 'N', "\nyY");
        if ('y'==key || 'Y'==key) {
            cur_page = find_page (f_records[0]->nickname[0], *cur_book);
            delete_record (f_records[0], cur_page); 
        } else {
            printf ("\n������ ��������\n");
        }
    } else {
        cur = *get_number_set ("\n����� ������ �� ������ (������ ���� - ������): ", "\n0123456789", 1, 0, 0, i+1);
        if (cur<1 || cur>i) { printf ("\n������ ��������������\n"); return 1; }
        
        key = get_key ("\n������� ������? (y/N): ", 'N', "\nyY");
        if ('y'==key || 'Y'==key) {
            cur_page = find_page (f_records[cur-1]->nickname[0], *cur_book);
            delete_record (f_records[cur-1], cur_page); 
        } else {
            printf ("\n������ ��������\n");
        }
    }
    return 0;
}

int help (void) {
#if defined (__gnu_linux__)
    return printf (
            "\n"
            "�������:\n"
            "\n"
            "\x1b[1;32m  �������� �������: https://github.com/asmazovec/prog.sem2.8 \x1b[0m\n"
            "\n"
            "   ?   ����� ����� ������\n"
            "\n"
            "\x1b[1m  ���������� � ����� \x1b[0m \n"
            "   o   ������� ����� ����� (������� ����� � �������)\n"
            "   q   ������� ����� ��� ����������\n"
            "   Q   ������� ��� ����� � �������� � �����\n"
            "   w   ��������� �����\n"
            "   W   ��������� ����� ���\n"
            "\n"
            "\x1b[1m  ����� \x1b[0m \n"
            "   f   ����� �� ����� �����\n"
            "   b   �������� ���� ������� � �����\n"
            "   p   �������� ���� ������� �� ��������\n"
            "\n"
            "\x1b[1m  �������������� \x1b[0m \n"
            "   n   ����� ������\n"
            "   u   ������������� ������\n"
            "   d   ������� ������\n"
            "\n"
            "\x1b[1m  ������� �������� ���� \x1b[0m \n"
            "   c   �������� �������� �������� ����\n"
            "   ]   ������� � ��������� ����� �� ��������\n"
            "   [   ������� � ���������� ����� �� ��������\n"
            );
#elif defined (__WIN32__) || defined (__WIN64__)
    return printf (
            "\n"
            "�������:\n"
            "\n"
            "  �������� �������: https://github.com/asmazovec/prog.sem2.8\n"
            "\n"
            "   ?   ����� ����� ������\n"
            "\n"
            "  ���������� � �����\n"
            "   o   ������� ����� ����� (������� ����� � �������)\n"
            "   q   ������� ����� ��� ����������\n"
            "   Q   ������� ��� ����� � �������� � �����\n"
            "   w   ��������� �����\n"
            "   W   ��������� ����� ���\n"
            "\n"
            "  �����\n"
            "   f   ����� �� ����� �����\n"
            "   b   �������� ���� ������� � �����\n"
            "   p   �������� ���� ������� �� ��������\n"
            "\n"
            "  ��������������\n"
            "   n   ����� ������\n"
            "   u   ������������� ������\n"
            "   d   ������� ������\n"
            "\n"
            "  ������� �������� ����\n"
            "   c   �������� �������� �������� ����\n"
            "   ]   ������� � ��������� ����� �� ��������\n"
            "   [   ������� � ���������� ����� �� ��������\n"
            );
    

#else
    return 0;

#endif
}


#endif /* MAIN_H_ */

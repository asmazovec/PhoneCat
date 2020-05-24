/* MIT License
 * Copyright (c) Alexander Mazovets
*/

#include "consupport.h"


/* ���������� ����������� ������, ����� ��� �� ������������ ������
 * �����.
 * ���� ������ �� �������� �����������, ���������� '\0'.
 * */
char get_specific (const char *purpose) {
    char key = getchar ();
    while (*purpose) {
        if (key==*purpose++) { return key; }
    }
    return '\0';
}

/* ����������� � ���������� ������ �� ������������ ������ �����. 
 * prompt - ����������� �� �����,
 * def - ���� �� ���������,
 * length - ����� ����������� ������.
 * */
char *get_line (const char *prompt, const char *def, int length) {
    printf ("%s", prompt); // �����������.
    char *line = (char*) malloc (length*sizeof (char)); if (NULL==line) { exit (1); } 

    int cur_pose = 0; // ������� �������, �� ������� ������� ������ � ������.
    do {
        if (cur_pose>=length) { while (getchar ()!='\n'); break; } // ��������� ������ ��� ������.
        line[cur_pose] = getchar (); 
    } while (line[cur_pose++]!='\n'); // �������� ������� ���������� ������.
    if (cur_pose==1) { strcpy (line, def); return line; } // ������ ���� ������ default.
    line[cur_pose-1] = '\0';  
    return line;
}

/* ����������� � ���������� ������ ���������� ������� �� ������������ ������ �����. 
 * prompt - ����������� �� �����,
 * def - ���� �� ���������,
 * length - ����� ����������� ������.
 * */
char *get_line_capital (const char *prompt, const char *def, int length) {
    printf ("%s", prompt); // �����������.
    char *line = (char*) malloc (length*sizeof (char)); if (NULL==line) { exit (1); } 

    int cur_pose = 0; // ������� �������, �� ������� ������� ������ � ������.
    do {
        if (cur_pose>=length) { while (getchar ()!='\n'); break; } // ��������� ������ ��� ������.
        line[cur_pose] = toupper (getchar ()); 
    } while (line[cur_pose++]!='\n'); // �������� ������� ���������� ������.
    if (cur_pose==1) { strcpy (line, def); return line; } // ������ ���� ������ default.
    line[cur_pose-1] = '\0';  
    return line;
}

/* ����������� � ���������� ����� �� ������� ������� �� ������������ ������ �����. 
 * prompt - ����������� �� �����,
 * def - �������� �� ���������,
 * length - ����� ����������� ������.
 * */
char *get_word (const char *prompt, const char *def, int length) {
    printf ("%s", prompt); // �����������.
    char *line = (char*) malloc (length*sizeof (char)); if (NULL==line) { exit (1); } 

    int cur_pose = 0; // ������� �������, �� ������� ������� ������ � ������.
    do {
        if (cur_pose>=length)      { while (getchar ()!='\n'); break; } // ��������� ������ ��� ������.
        if (line[cur_pose-1]==' ') { while (getchar ()!='\n'); break; } // ��������� ����� �����.
        line[cur_pose] = getchar (); 
    } while (line[cur_pose++]!='\n'); // �������� ������� ���������� ������.
    if (cur_pose==1) { strcpy (line, def); return line; } // ������ ���� ������ default.
    line[cur_pose-1] = '\0';  
    return line;
}

/* ����������� � ���������� ����� �� ������� ������� �� ������������ ������ �����. 
 * prompt - ����������� �� �����,
 * def - �������� �� ���������,
 * length - ����� ����������� ������.
 * */
char *get_word_capital (const char *prompt, const char *def, int length) {
    printf ("%s", prompt); // �����������.
    char *line = (char*) malloc (length*sizeof (char)); if (NULL==line) { exit (1); } 

    int cur_pose = 0; // ������� �������, �� ������� ������� ������ � ������.
    do {
        if (cur_pose>=length)      { while (getchar ()!='\n'); break; } // ��������� ������ ��� ������.
        if (line[cur_pose-1]==' ') { while (getchar ()!='\n'); break; } // ��������� ����� �����.
        line[cur_pose] =  toupper (getchar ()); 
    } while (line[cur_pose++]!='\n'); // �������� ������� ���������� ������.
    if (cur_pose==1) { strcpy (line, def); return line; } // ������ ���� ������ default.
    line[cur_pose-1] = '\0';  
    return line;
}


/* ����������� ���� �������. 
 * prompt - �����������,
 * def - �������� �� ���������,
 * purpose - ������� �������.
 * */
char get_key (const char *prompt, char def, const char *purpose) {
    printf ("%s", prompt); // �����������.
    char key = get_specific (purpose);
    if (key=='\n') { return  def; }
    while (getchar ()!='\n');
    return key;
}

/* �������� �� ������ ������ ����� ����.
 * prompt - �����������,
 * def - �������� ����������� �����,
 * count - ��������� ����� ����.
 * */
int *get_sign_set (const char *prompt, int def, int count) {
    printf ("%s", prompt); // �����������
    int *set = (int*) malloc (count*sizeof (int)); if (NULL==set) { exit (1); }

    char cur_char = '\0';

    int cur_sign = 0;
    int num_sign = 0;
    while (num_sign<count) {
        set[num_sign] = def;
        num_sign++;
    }
    
    num_sign = 0;
    do {
        if (num_sign>=count) { while (getchar ()!='\n'); break; } // ��������� ������ ��� ������.
        cur_char = get_specific ("\n0123456789");
        if (cur_char!='\0') {
            if (cur_char=='0') { set[num_sign] = 0; }
            if (cur_char=='1') { set[num_sign] = 1; }
            if (cur_char=='2') { set[num_sign] = 2; }
            if (cur_char=='3') { set[num_sign] = 3; }
            if (cur_char=='4') { set[num_sign] = 4; }
            if (cur_char=='5') { set[num_sign] = 5; }
            if (cur_char=='6') { set[num_sign] = 6; }
            if (cur_char=='7') { set[num_sign] = 7; }
            if (cur_char=='8') { set[num_sign] = 8; }
            if (cur_char=='9') { set[num_sign] = 9; }
            num_sign++;
        }
    } while (cur_char!='\n'); // �������� ������� ���������� ������.
    return set;
}

/* ���� ������������������ �����.
 * prompt - �����������,
 * def - �������� �� ���������,
 * count - ���������� �������� �����,
 * ... - �� ������ ����� ����� min1, max1, min2, max2, ...
 * */
int *get_number_set (const char *prompt, const char *purpose, int count, int def, ...) {
    printf ("%s", prompt); // �����������.
    int *set = (int*) malloc (count*sizeof (int)); if (NULL==set) { exit (1); }

    va_list args;
    va_start (args, def);

    int cur_min; // ������� ��� ��������.
    int cur_max; // �������� ��� ��������.

    char *number_line; 
    int length;
    char cur_char;
    int cur_cell = 0;

    while (cur_cell<count) {
        cur_min = va_arg (args, int);
        cur_max = va_arg (args, int);
        length = 1;
        set[cur_cell] = def;
        number_line = (char*) malloc (length*sizeof (char)); if (NULL==number_line) { exit (1); }
        while ('\0'==(cur_char = get_specific (purpose)));
        number_line[length-1] = cur_char;
        while (cur_char!='\n' && cur_char!='\0') {
            number_line[length-1] = cur_char;
            cur_char = get_specific (purpose);
            length++;
            number_line = (char*) realloc (number_line, length*sizeof (char)); 
            if (NULL==number_line) { exit (1); }
            number_line[length-1] = '\0';
        }
        if ('\0'!=number_line[0])  { set[cur_cell] = atoi (number_line); }
        if (set[cur_cell]>cur_max) { set[cur_cell] = cur_max; }
        if (set[cur_cell]<cur_min) { set[cur_cell] = cur_min; }
        
        if ('\n'==number_line[0]) { 
            while (cur_cell<count) { set[cur_cell++] = def; } 
            free (number_line); 
            return set;
        }
        cur_cell++;
        if ('\n'==cur_char) { 
            while (cur_cell<count) { set[cur_cell++] = def; }
            free (number_line);
            return set;
        }
        free (number_line);
    }
    if ('\0'==number_line[0]) { while (getchar ()!='\n'); }
    va_end (args);
    return set;
}


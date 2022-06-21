#ifndef MISTRING_H
#define MISTRING_H

#include <stdlib.h>
#include <stddef.h>

#define mi_toupper(X) ((X)>='a' && (X)<='z') ? ((X)-' '):(X)
#define mi_tolower(X) ((X)>='A' && (X)<='Z') ? ((X)+' '):(X)

char *mi_strchr(char *s, int c);
char *mi_strrchr(char *s, int c);

size_t mi_strlen(const char *s);

char *mi_strcat(char*s1, char *s2);
char *mi_strcatV2(char* s1, char *s2);

char *mi_strcpy(char *s1, const char *s2);

int mi_strcmp(const char *s1, const char *s2);
int mi_stricmp(const char *s1, const char *s2);
int mi_strncmp(const char *s1, const char *s2, size_t n);

char *mi_strstr(const char *s1, const char *s2);

#endif // MISTRING_H

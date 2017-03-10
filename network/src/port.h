/*
**  @(#)port.h
**
**  libnetwork - portable functions
**  -------------------------------
**
**  copyright 2001-2017 Code Construct Systems (CCS)
*/
#ifndef __PORT_H
#define __PORT_H

/*
**  Function prototypes.
*/
extern int strcat_p(string_c_t, size_t, const string_c_t, size_t);
extern int strcpy_p(string_c_t, size_t, const string_c_t, size_t);
extern int strfmt_p(string_c_t, size_t, const string_c_t, ...);
extern int strtok_p(string_c_t *, string_c_t, const string_c_t, string_c_t *);
extern int time_p(time_t *);
extern int localtime_p(time_t *, struct tm *);
extern int fopen_p(FILE **, const string_c_t, const string_c_t);
extern int fclose_p(FILE *);
extern int tmpfile_p(FILE **);

#endif /* __PORT_H */


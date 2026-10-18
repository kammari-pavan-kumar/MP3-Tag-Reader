#ifndef ENCODE_H
#define ENCODE_H

#include "types.h" // Contains user defined types

typedef struct 
{
    /* mp3 file */
    char *mp3_fname;
    FILE *fptr_mp3_file;
    unsigned int size;
    uint loop;

} ToviewInfo;



/* Check operation type */
OperationType check_operation_type(char *argv[]);

/* read and validation with extension */
Status read_and_validate(char *argv[], ToviewInfo *Toview );
//Status read_and_validate(char *filename, ToviewInfo *Toview);

/* Perform to view */
Status to_view(ToviewInfo *Toview,char *argv[]);

/* Get File pointers */
Status open_files(ToviewInfo *Toview);

/* check ID3 tag */
Status check_ID3_tag(ToviewInfo *Toview);

/* check version  */
Status check_version(ToviewInfo *Toview);

/* call function for view */
Status mp3_view(ToviewInfo *Toview);

/* skip header */
Status skip_header(ToviewInfo *Toview);

/* read the tag */
Status read_size(ToviewInfo *Toview);

/* read the contents */
Status Read_contents(ToviewInfo *Toview);

/* help data */
void help_menu();


#endif

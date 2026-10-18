#ifndef ENCODE
#define ENCODE


typedef struct _Toedit
{
    /* mp3 file */
    char *edit_mp3_fname;
    FILE *fptr_edit_mp3_file;
    unsigned int e_size;
    char tag[5];
    int flag;

    /* temp mp3 file */
    char *temp_mp3_fname;
    FILE *fptr_temp_mp3_file;
    uint argv_size; 
    char option[2];
    char buffer[1000];


} ToeditInfo;




/* read and validation with extension_for_edit*/

Status Read_and_Validation_for_edit(int argc,char *argv[],ToeditInfo *Toedit);


/* Perform to edit*/
Status to_edit(int argc,ToeditInfo *Toedit,char *argv[]);

/* Get File pointers for edit */
Status open_files_for_edit(ToeditInfo *Toedit);


/* check ID3 tag for edit */
Status check_ID3_tag_for_edit(ToeditInfo *Toedit);

/* check version for edit */
Status check_version_for_edit(ToeditInfo *Toedit);

/* call function for edit */
Status mp3_edit(int argc,ToeditInfo *Toedit,char *argv[]);

/* skip header for edit */
Status skip_header_for_edit(ToeditInfo *Toedit);

/* read tag for edit */
Status read_tag_for_edit(ToeditInfo *Toedit,char *argv[]);

/* read the size */
Status read_size_for_edit(ToeditInfo *Toedit);

/* read and replace */
Status read_and_replace(int argc,ToeditInfo *Toedit,char *argv[]);

/* copy data */
Status copy_data(ToeditInfo *Toedit,char *Tag);

/*copy remain */
Status copy_remaining_data(ToeditInfo *Toedit);

/*copy temporary file to original file*/
Status copy_temp_to_org(ToeditInfo *Toedit);

/*convert endian*/
void convertendian(int size,unsigned char *ptr);

#endif


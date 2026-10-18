#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "view.h"
#include "edit.h"
#include "types.h"

/* read and validation with extension_for_edit*/
Status Read_and_Validation_for_edit(int argc,char *argv[], ToeditInfo *Toedit )
{
    //compare extension .mp3 or not
    char *cmp=strstr(argv[argc-1],".mp3");
    if(cmp!=NULL&&strcmp(cmp,".mp3")==0)
    {   
        //if it is .mp3 then assign file to Toedit->edit_mp3_fname and return success
        Toedit->edit_mp3_fname = argv[argc-1];
        return success;
        
    }
    else
    {
        //if it is not .mp3 return failure
        printf("ERROR: It is not .mp3 file\n");
        return failure;
    }
}
Status to_edit(int argc,ToeditInfo *Toedit,char *argv[])
{
    //check open_files_for_edit(Toedit) return value is success or not
    if(open_files_for_edit(Toedit)==success)
    {
       // printf("File is opened successfully\n");
       //check check_ID3_tag_for_edit(Toedit) return value is success or not
       if(check_ID3_tag_for_edit(Toedit)==success)
       {
        //printf("check id3 tag is successfull\n");
        //check check_version_for_edit(Toedit) return value is success or not
        if(check_version_for_edit(Toedit)==success)
        {
            //printf("check version is successful\n");
            //check check mp3_edit(arc,Toedit,argv) return value is success or not
            if(mp3_edit(argc,Toedit,argv)==success)
            {
                //printf("check mp3 is successful\n");
                return success;
            }
            else
            {
                //if failure print error message and return failure
                printf("ERROR: Error in mp3_edit\n");
                return failure;
            }

        }
        else
        {
            //if failure print error message and return failure
            printf("ERROR: Error in check_version_for_edit\n");
            return failure;

        }

       }
       else
       {
        //if failure print error message and return failure
        printf("ERROR: check_ID3_tag_for_edit\n");
        return failure;

       }

    }
    else
    {
        //if failure print error message and return failure
        printf("Error: Unable to open file\n");
        return failure;
    }
    return success;
}
Status open_files_for_edit(ToeditInfo *Toedit)
{
    //open all required files
    Toedit->fptr_edit_mp3_file = fopen(Toedit->edit_mp3_fname, "rb");
    if (Toedit->fptr_edit_mp3_file == NULL)
    {
        printf("ERROR : File not exist\n");
        return failure;
    }
    Toedit->fptr_temp_mp3_file = fopen("temp.mp3", "wb");
    if (Toedit->fptr_temp_mp3_file == NULL)
    {
        printf("ERROR : File not exist\n");
        return failure;
    }
    return success;
}
Status check_ID3_tag_for_edit(ToeditInfo *Toedit)
{
    //declare tag char array type
    char tag[4];
    //read 3 bytes from Toedit->fptr_edit_mp3_file and store to tag
    fread(tag, 1, 3, Toedit->fptr_edit_mp3_file);
    tag[3] = '\0';
    //compare it is ID3 tag or not
    if (strcmp(tag, "ID3") == 0)
    {
        //printf("ID3 Tag Found\n");
        return success;
    }
    else
    {
        //if failure print error message and return failure
        printf("ID3 Tag Not Found\n");
        return failure;
    }
}
Status check_version_for_edit(ToeditInfo *Toedit)
{
    //declare unsigned char data
    unsigned char data;
    //read 1 byte
    fread(&data, 1, 1, Toedit->fptr_edit_mp3_file);
    //compare data and return success
    if (data == 0X03)
    {
        //printf("This is version ID3v2\n");
        return success;
    }
    else
    {
        //if failure then return failure
        printf("This is not version ID3v2\n");
        return failure;
    }
}
Status mp3_edit(int argc,ToeditInfo *Toedit,char *argv[])
{
    //check skip_header_for_edit(Toedit) return value is success or not
    if(skip_header_for_edit(Toedit)==success)
    {
       // printf("skip header is successful\n");
        //check (read_tag_for_edit(Toedit,argv) return value is success or not
        if(read_tag_for_edit(Toedit,argv)==success)
        {
            //printf("read tag for edit is successful\n");
            //check read_and_replace(argc,Toedit,argv) return value is success or not
            if(read_and_replace(argc,Toedit,argv)==success)
            {
                //printf("read and replace is successfull\n");
                fclose(Toedit->fptr_edit_mp3_file);
                fclose(Toedit->fptr_temp_mp3_file);
                return success;

            }
            else
            {
                //if failure print error message and return failure
                printf("ERROR: Error in read and replace\n");
                return failure;

            }
        }
        else
        {
            //if failure print error message and return failure
            printf("ERROR: Error in tag for edit\n");
            return failure;
        }
    }
    else
    {
        //if failure print error message and return failure
        printf("ERROR: Error in skip header for edit\n");
        return failure;
    }

    return success;
}
Status skip_header_for_edit(ToeditInfo *Toedit)
{
    //declare buffer
    char buffer[10];
    //rewind to first position
    rewind(Toedit->fptr_edit_mp3_file);
    //skip 10 bytes or read 10 bytes from src to temp
    fread(buffer, 1, 10, Toedit->fptr_edit_mp3_file);
    fwrite(buffer, 1, 10, Toedit->fptr_temp_mp3_file);
    return success;
}
Status read_tag_for_edit(ToeditInfo *Toedit,char *argv[])
{
  

    //declare option
  //  char option[3];
  char *option = argv[2];
    //printf("Enter operation option\n");
    printf("\n..................................Select Edit option.......................................\n");
    //read option from CAL
    //strcpy(option, argv[2]);
    //option[2] = '\0';
      
    //compare option with each tag and store the tag name
    if (!strcmp(option, "-t"))
    {
        strcpy(Toedit->tag, "TIT2");
    }
    else if (!strcmp(option, "-a"))
    {
        strcpy(Toedit->tag, "TPE1");
    }
    else if (!strcmp(option, "-A"))
    {
        strcpy(Toedit->tag, "TALB");
    }
    else if (!strcmp(option, "-y"))
    {
        strcpy(Toedit->tag, "TYER");
    }
    else if (!strcmp(option, "-T"))
    {
        strcpy(Toedit->tag, "TCON");
    }
    else if (!strcmp(option, "-c"))
    {
        strcpy(Toedit->tag, "COMM");
    }
    else
    {
        return failure;
    }
    return success;
}
Status read_size_for_edit(ToeditInfo *Toedit)
{
    //declare size
    unsigned char size[4];
    //read 4 byres from Toedit->fptr_edit_mp3_file and store to size
    fread(size, 1, 4, Toedit->fptr_edit_mp3_file);
    for (int i = 0; i < 2; i++)
    {
        char temp = size[i];
        size[i] = size[4 - i - 1];
        size[4 - i - 1] = temp;
    }
    Toedit->e_size = *(int *)size;
    //Toedit->e_size = (size[0] << 24) | (size[1] << 16) | (size[2] << 8) | size[3];
    return success;
}
void convertendian(int size,unsigned char *ptr)
 {
    //convert from little endian to big endian


    // char *cptr = (char *)ptr;  
    // for(int i=0;i<size/2;i++)  
    // {
    // char temp = *(cptr+i);
    // *(cptr+i) =*(cptr+size-i-1);
    // *(cptr+size-i-1) = temp;
    // }
    ptr[0] = (size>> 24) & 0xFF;
    ptr[1] = (size>> 16) & 0xFF;
    ptr[2] = (size >> 8) & 0xFF;
    ptr[3] = (size) & 0xFF;

   
}
Status read_and_replace(int argc,ToeditInfo *Toedit,char *argv[])
{
    
    //declare flags,buffer,tagdata
    char flags[4];
    char *buffer = malloc(Toedit->e_size);
    char tagdata[5];   
    //loop for upto tag matches
    while (fread(tagdata, 1, 4, Toedit->fptr_edit_mp3_file)==4)
    {
        tagdata[4] = '\0';
        //read 4 bytes of tagdata from Toedit->fptr_temp_mp3_file
        fwrite(tagdata, 1, 4, Toedit->fptr_temp_mp3_file);
        //call read size for edit 
        read_size_for_edit(Toedit);
        //compare tagdata with Toedit->tag
        if (!strcmp(Toedit->tag, tagdata))
        {
            //compare each tag 
            if (!strcmp(Toedit->tag, "TIT2"))
            {
                //declare tag
                char Tag[1000];
                printf("\n..................................Select Title change option.......................................\n");
                //printf("Enter Title to Modify: ");
                //copy full tag data to Tag
                strcpy(Tag, argv[3]);
                for(int i=4;i<=argc-2;i++)
                {
                    strcat(Tag," ");
                    strcat(Tag,argv[i]);
                }
                //finding string length
                int new_len = strlen(Tag)+1;
                //declare char
                unsigned char arr[10];
                //call convertendian function
                convertendian(new_len,arr);
                //write arr to temparory file
                fwrite(arr, 1, 4, Toedit->fptr_temp_mp3_file);
                //read and write flags from main file to temp file
                fread(flags, 1, 3, Toedit->fptr_edit_mp3_file);
                fwrite(flags, 1, 3, Toedit->fptr_temp_mp3_file);
                //skip the orginal data in main file
                fseek(Toedit->fptr_edit_mp3_file, Toedit->e_size-1, SEEK_CUR);
                //call copy_data function
                copy_data(Toedit, Tag);
                //print tag data
                printf("Title\t:\t%s",Tag);
                printf("\n..................................Title changed successfully.......................................\n");
            }
            
            else if (!strcmp(Toedit->tag, "TPE1"))
            {
                //declare tag
                char Tag[1000];
                printf("\n..................................Select Artist change option.......................................\n");
                //printf("Enter Artist to Modify: ");
                //copy full tag data to Tag
                strcpy(Tag, argv[3]);
                for(int i=4;i<=argc-2;i++)
                {
                    strcat(Tag," ");
                    strcat(Tag,argv[i]);
                }
                //finding string length
                int new_len = strlen(Tag)+1;
                unsigned char arr[10];
                //call convertendian function
                convertendian(new_len,arr);
                //write arr to temparory file
                fwrite(arr, 1, 4, Toedit->fptr_temp_mp3_file);
                //read and write flags from main file to temp file
                fread(flags, 1, 3, Toedit->fptr_edit_mp3_file);
                fwrite(flags, 1, 3, Toedit->fptr_temp_mp3_file);
                //skip the orginal data in main file
                fseek(Toedit->fptr_edit_mp3_file, Toedit->e_size-1, SEEK_CUR);
                //call copy_data function
                copy_data(Toedit, Tag);
                //print tag data
                printf("Artist\t:\t%s",Tag);
                printf("\n..................................Artist changed successfully.......................................\n");
            }
            else if (!strcmp(Toedit->tag, "TALB"))
            {
                //declare tag
                char Tag[1000];
                printf("\n..................................Select Album change option.......................................\n");
                //printf("Enter Album to Modify: ");
                //copy full tag data to Tag
                strcpy(Tag, argv[3]);
                for(int i=4;i<=argc-2;i++)
                {
                    strcat(Tag," ");
                    strcat(Tag,argv[i]);
                }
                //finding string length
                int new_len = strlen(Tag)+1;
                unsigned char arr[10];
                //call convertendian function
                convertendian(new_len,arr);
                //write arr to temparory file
                fwrite(arr, 1, 4, Toedit->fptr_temp_mp3_file);
                //read and write flags from main file to temp file
                fread(flags, 1, 3, Toedit->fptr_edit_mp3_file);
                fwrite(flags, 1, 3, Toedit->fptr_temp_mp3_file);
                //skip the orginal data in main file
                fseek(Toedit->fptr_edit_mp3_file, Toedit->e_size-1, SEEK_CUR);
                //call copy_data function
                copy_data(Toedit, Tag);
                //print tag data
                printf("Album\t:\t%s",Tag);
                printf("\n..................................Album changed successfully.......................................\n");
            }
            else if (!strcmp(Toedit->tag, "TYER"))
            {

                //declare tag
                char Tag[1000];
                printf("\n..................................Select Year change option.......................................\n");
                //printf("Enter Year  to Modify: ");
                //copy full tag data to Tag
                strcpy(Tag, argv[3]);
                for(int i=4;i<=argc-2;i++)
                {
                    strcat(Tag," ");
                    strcat(Tag,argv[i]);
                }
                //finding string length
                int new_len = strlen(Tag)+1;
                unsigned char arr[10];
                //call convertendian function
                convertendian(new_len,arr);
                //write arr to temparory file
                fwrite(arr, 1, 4, Toedit->fptr_temp_mp3_file);
                //read and write flags from main file to temp file
                fread(flags, 1, 3, Toedit->fptr_edit_mp3_file);
                fwrite(flags, 1, 3, Toedit->fptr_temp_mp3_file);
                //skip the orginal data in main file
                fseek(Toedit->fptr_edit_mp3_file, Toedit->e_size-1, SEEK_CUR);
                //call copy_data function
                copy_data(Toedit, Tag);
                //print tag data
                printf("Year\t:\t%s",Tag);
                printf("\n..................................Year changed successfully.......................................\n");
            }
            else if (!strcmp(Toedit->tag, "TCON"))
            {
                //declare tag
                char Tag[1000];
                //printf("Enter Music to Modify: ");
                printf("\n..................................Select Music change option.......................................\n");
                //copy full tag data to Tag
                strcpy(Tag, argv[3]);
                for(int i=4;i<=argc-2;i++)
                {
                    strcat(Tag," ");
                    strcat(Tag,argv[i]);
                }
                //finding string length
                int new_len = strlen(Tag)+1;
                unsigned char arr[10];
                //call convertendian function
                convertendian(new_len,arr);
                //write arr to temparory file
                fwrite(arr, 1, 4, Toedit->fptr_temp_mp3_file);
                //read and write flags from main file to temp file
                fread(flags, 1, 3, Toedit->fptr_edit_mp3_file);
                fwrite(flags, 1, 3, Toedit->fptr_temp_mp3_file);
                //skip the orginal data in main file
                fseek(Toedit->fptr_edit_mp3_file, Toedit->e_size-1, SEEK_CUR);
                //call copy_data function
                copy_data(Toedit, Tag);
                //print tag data
                printf("Music\t:\t%s",Tag);
                printf("\n..................................Music changed successfully.......................................\n");
            }
            else if (!strcmp(Toedit->tag, "COMM"))
            {
                //declare tag
                char Tag[1000];
                //printf("Enter comment to Modify: ");
                printf("\n..................................Select comment change option.......................................\n");
                //copy full tag data to Tag
                strcpy(Tag, argv[3]);
                for(int i=4;i<=argc-2;i++)
                {
                    strcat(Tag," ");
                    strcat(Tag,argv[i]);
                }
                //finding string length
                int new_len = strlen(Tag)+1;
                unsigned char arr[10];
                //call convertendian function
                convertendian(new_len,arr);
                //write arr to temparory file
                fwrite(arr, 1, 4, Toedit->fptr_temp_mp3_file);
                //read and write flags from main file to temp file
                fread(flags, 1, 3, Toedit->fptr_edit_mp3_file);
                fwrite(flags, 1, 3, Toedit->fptr_temp_mp3_file);
                //skip the orginal data in main file
                fseek(Toedit->fptr_edit_mp3_file, Toedit->e_size-1, SEEK_CUR);
                //call copy_data function
                copy_data(Toedit, Tag);
                //print tag data
                printf("comment\t:\t%s",Tag);
                printf("\n..................................Comment changed successfully.......................................\n");
            }
                  
        }
        else
        {
            //declare size
            unsigned char size[4];
            //call convertendian function
            convertendian(Toedit->e_size, size);
            //write size to temporary file 
            fwrite(size, 1, 4, Toedit->fptr_temp_mp3_file);
            //read and write flags to temporary file 
            fread(flags, 1, 2, Toedit->fptr_edit_mp3_file);
            fwrite(flags, 1, 2, Toedit->fptr_temp_mp3_file);
            //read and write filedata to temporary file
            fread(buffer, 1,Toedit->e_size, Toedit->fptr_edit_mp3_file);
            fwrite(buffer, 1, Toedit->e_size, Toedit->fptr_temp_mp3_file);
        }
    }
    
    return success;
}
Status copy_data(ToeditInfo *Toedit, char *Tag)
{
    //copy data to Toedit->fptr_temp_mp3_file
    fwrite(Tag, 1, strlen(Tag), Toedit->fptr_temp_mp3_file);
    copy_remaining_data(Toedit);//call copy remaining data function

    return success;
}
Status copy_remaining_data(ToeditInfo *Toedit)
{
    //declare buffer
    char buffer;
    //read contens from Toedit->fptr_edit_mp3_file to Toedit->fptr_temp_mp3_file
    while(fread(&buffer,1,1,Toedit->fptr_edit_mp3_file))
    fputc(buffer,Toedit->fptr_temp_mp3_file);
    fclose(Toedit->fptr_edit_mp3_file);
    fclose(Toedit->fptr_temp_mp3_file);
    copy_temp_to_org(Toedit);
    return success;
}
Status copy_temp_to_org(ToeditInfo *Toedit)
{
    char ch;
    FILE *fptr1 = fopen("temp.mp3","r");
    FILE *fptr2 = fopen("song.mp3","w");
    while(fread(&ch,1,1,Toedit->fptr_temp_mp3_file))
    fputc(ch,Toedit->fptr_edit_mp3_file);
}


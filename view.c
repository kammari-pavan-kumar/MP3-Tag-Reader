#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "view.h"
#include "edit.h"
#include "types.h"

/* read and validation with extension */
Status read_and_validate(char *argv[], ToviewInfo *Toview )
{
    //check if argv[2] is .mp3   
    if(strstr(argv[2],".mp3"))
    {
        //if true assign argv[2] to Toview->mp3_fname
        Toview->mp3_fname = argv[2];
        return success;
    }
    else
    {
        //if it is failure print error message return failure
        printf("ERROR: It is not .mp3 file\n"); 
        return failure;
    }
}
/* Perform to view */
Status to_view(ToviewInfo *Toview,char *argv[])
{
    //check if open_files(Toview) return value is success or not
    if(open_files(Toview)==success)
    {
        //print success message
        //printf("file is opened successfully\n");
        //check check_ID3_tag(Toview) return value is success or not
        if(check_ID3_tag(Toview)==success)
        {
            //print success message
            //printf("ID3 tag is found\n");
            //check check_version(Toview) return value is success or not
            if(check_version(Toview)==success)
            {
                //print success message
                //printf("version is ID3v2\n");
                //check mp3_view(Toview) return value is success or not
                if(mp3_view(Toview)==success)
                {
                    //if true return success
                    return success;
                }
                else
                {
                    //if not return failure
                    return failure;
                }

            }
            else
            {
                //if not print error message and return failure
                printf("ERROR: check version is failed\n");
                return failure;
            }
            
        }
        else
        {
            //if not print error message and return failure
            printf("ERROR: check ID3 tag failed\n");
            return failure;
        }
    }
    else
    {
        //if not print error message and return failure
        printf("ERROR: Unable to open files\n");
        return failure;
    }
    return success;
}

/* Get File pointers */
Status open_files(ToviewInfo *Toview)
{
    //Open all files if all files opened return success
    Toview->fptr_mp3_file = fopen(Toview->mp3_fname,"rb");
    if(Toview->fptr_mp3_file == NULL)
    {
        //if no file exist print error message and return failure
        printf("ERROR : File not exist\n");
        return failure;
    }
    //printf("File is opened\n");
    return success;
}
/* check ID3 tag */
Status check_ID3_tag(ToviewInfo *Toview)
{
    //declare tag 
    char tag[4];
    //read 3 bytes from fptr_mp3_file
    fread(tag,1,3,Toview -> fptr_mp3_file);
    tag[3]='\0';
    //compare tag and "ID3" are same or not
    if(strcmp(tag, "ID3")==0)
    {
        //printf("ID3 Tag Found\n");
        return success;
    }
    else
    {
        //if failure return error message and return failure
        printf("ERROR: ID3 Tag Not Found\n");
        return failure;
    }
}
/* check version  */
Status check_version(ToviewInfo *Toview)
{
    //decalre data
    char data;
    //read 1 byte data from fptr_mp3_file
    fread(&data,1,1,Toview -> fptr_mp3_file);
    //check data condition meets or not
    if(data == 0X03)
    {
        //printf("This is version ID3v2\n");
        return success;
    }
    else
    {
        //if failure print error message return failure
        printf("This is not version ID3v2\n");
        return failure;
    }
}
/* call function for view */
Status mp3_view(ToviewInfo *Toview)
{
    printf(".................................................................\n");
    printf("MP3 Tag Reader and Editor for ID3v2\n");
    printf(".................................................................\n");
    //check skip_header(Toview) return value is success or not
    if(skip_header(Toview)==success)
    {
        //printf("skip header completed successfully\n");
        //check Read_contents(Toview) return value is success or not
        if(Read_contents(Toview)==success)
        {
            //printf("Read_contents completed successfully\n");
            return success;
        }
    }
    return success;

}
/* skip header */
Status skip_header(ToviewInfo *Toview)
{
    //seek to 10th byte and return success
    fseek(Toview->fptr_mp3_file,10,SEEK_SET);
    return success;
}
/* read the tag */
Status read_size(ToviewInfo *Toview)
{
    //declare size array of char type
    unsigned char size[4];
    //read 4 bytes from Toview->fptr_mp3_file
    fread(size,1,4,Toview->fptr_mp3_file);
    //swap bits of data
    for(int i=0;i<2;i++)
    {
        char temp = size[i];
        size[i] = size[4 - i - 1];
        size[4 - i - 1] = temp;
    }
    //assign size to Toview->size
    Toview->size = *(int*)size;
    //skip 2 bytes
    fseek(Toview->fptr_mp3_file, 2, SEEK_CUR);
    return success;
}
/* read the contents */
Status Read_contents(ToviewInfo *Toview)
{
    //initalize tagcount to 0
    int tagcount=0;
    //declare buffer
    char buffer[1000];
    while(tagcount<6)
    {
        //declare tag of char array type
    char tag[5];
    //read 4 byes from Toview->fptr_mp3_file store to tag
    fread(tag,1,4,Toview->fptr_mp3_file);
    tag[4] = '\0';
    read_size(Toview);//call read_size(Toview)
    fread(buffer,1, Toview->size,Toview -> fptr_mp3_file);
    buffer[Toview->size] = '\0';
    //compare and read tag data
    if(!strcmp(tag,"TIT2"))
    {
        printf("Title\t\t:");
        printf("\t%s\n",buffer+1);
        tagcount++;
    }
    else if (!strcmp(tag,"TPE1"))
    {
        printf("Artist\t\t:");
        printf("\t%s\n",buffer+1);
        tagcount++;
    }
    else if (!strcmp(tag,"TALB"))
    {
        printf("Album\t\t:");
        printf("\t%s\n",buffer+1);
        tagcount++;
    }
    else if (!strcmp(tag,"TYER"))
    {
        printf("Year\t\t:");
        printf("\t%s\n",buffer+1);
        tagcount++;
    }
    else if (!strcmp(tag,"TCON"))
    {
        printf("Music\t\t:");
        printf("\t%s\n",buffer+1);
        tagcount++;
    }
     else if (!strcmp(tag,"COMM"))
    {
        printf("Comment\t\t:");
        printf("\t%s\n",buffer+1);
        tagcount++;
    }
}
printf("\n.................................................................\n");
return success;
}
/* help data */
void help_menu()
{
    //help menu 
    printf("mp3tag --help\n");
    printf("Help Menu\n\n");
    printf("usage: mp3tag -[tTaAycg] 'value' file1\n");
    printf("mp3tag -v\n");
    printf("-t -> Modifies a Title tag\n");
    printf("-T -> Modifies a Track tag\n");
    printf("-a -> Modifies a Artist tag\n");
    printf("-A -> Modifies a Album tag\n");
    printf("-y -> Modifies a Year tag\n");
    printf("-c -> Modifies a Comment tag\n");
    printf("-g -> Modifies a Genre tag\n");
    printf("-h -> Displays this help info\n");
    printf("-v -> Prints version info\n");
}
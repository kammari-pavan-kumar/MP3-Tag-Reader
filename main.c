#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include "view.h"
#include "edit.h"

int main(int argc,char *argv[])
{
    ToviewInfo Toview;
    ToeditInfo Toedit;

	if(argc < 2)
	{
		printf("ERROR: ./a.out : INVALID ARGUMENTS\n");
		printf("USAGE :\n");
		printf("To view please pass like: ./a.out -v mp3filename\n");
		printf("To edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c mp3filename\n");
		return 0;

	}
	
	//check operation type
	int ret = check_operation_type(argv);
	//check if ret is view_mp3
	if(ret == view_mp3)
	{
		if(argc>=3)
		{
			//check if read_and_validate(argv,&Toview ) return value is success or not
			if(read_and_validate(argv,&Toview )==success)
			{
				//printf("read and validate completed successfully\n");
				//check to_view return value is success or not
				if(to_view(&Toview,argv)==success)
				{
					//print success message
					printf("view_mp3 completed successfully\n");
				}
				else
				{
					//if it is failure return failure message terminate program
					printf("ERROR:view_mp3 failed\n");
					return 1;
				}
			}
		}
		else
		{

			printf("ERROR: enter correct arguments\n");
			return 1;
		}
	}
	//check if ret is edit_mp3
	else if(ret == edit_mp3)
	{
		if(argc>=3)
		{
			//check if Read_and_Validation_for_edit(argv, &Toedit ) return value is success or not
			if(Read_and_Validation_for_edit(argc,argv, &Toedit )==success)
			{
				//check to_edit(&Toedit,argv) return value is success or not
				if(to_edit(argc,&Toedit,argv)==success)
				{
					//print success message
					printf("edit_mp3 completed successfully\n");
				}
				else
				{
					//if it is failure print errror message and terminate program
					printf("Error: to_edit failed\n");
					return 1;
				}
			}
		}
		else
		{
			//print error message and terminate program
			printf("Error: failed\n");
			return 1;
		}
	}
	//check if ret is helpmenu
	else if(ret==helpmenu)
	{
		//if it is true call help menu
		help_menu();
	}
	else
	{
		//if not true enter error message
		printf("Invalid option\n");
		printf("enter --help for usage of options\n");

	}
	return 0;
}
	
/* Check operation type */
OperationType check_operation_type(char *argv[])
{
	//compare argv[1] with "-v" if true return view_mp3
    if(!strcmp(argv[1],"-v"))
    {
		//print operation type
        //printf("Operation type is view_mp3\n");
        return view_mp3;
    }
	//compare argv[1] with "-e" if true return edit_mp3
    else if(!strcmp(argv[1],"-e"))
    {
		//print operation type
        //printf("Operation type is edit_mp3\n");
        return edit_mp3;
    }
	//compare argv[1] with "--help" if true return helpmenu
    else if(!(strcmp(argv[1],"--help")))
    {
		//print operation type
        //printf("Operation type is help_menu\n");
        return helpmenu;
    }
    else
    {
		//if not print error message and return Invalid_operator
       printf("Error:Operation type is invalid");
       return Invalid_operator;
    }
}
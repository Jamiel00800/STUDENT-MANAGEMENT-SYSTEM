#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <process.h>
#include <ctype.h>
#include <mmsystem.h>

COORD coord = { 0, 0 };

void gotoxy(int x, int y)
{
    coord.X = x; coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct studData
{
        float s1,s2,s3,s4;
        char name[100];
        char snum[100];
}a;

FILE *scores;

void login()
{
    system("cls");
	int a=0,i=0;
    char uname[10],c=' ';
    char pword[10],code[10];
    char user[10]="user";
    char pass[10]="pass";

    do
    {
        printf("\n  ::::::::::::::::::::::::::  LOGIN FORM  ::::::::::::::::::::::::::  ");
        printf(" \n                       ENTER USERNAME:-");
        scanf("%s", &uname);
        printf(" \n                       ENTER PASSWORD:-");

        while(i<10)
        {
            pword[i]=getch();
            c=pword[i];
            if(c==13) break;
            else printf("*");
            i++;
        }

        pword[i]='\0';
        //char code=pword;
        i=0;
        //scanf("%s",&pword);

        if(strcmp(uname,"user")==0 && strcmp(pword,"pass")==0)
        {
            printf("  \n\n\n       WELCOME TO EMPLOYEE RECORD MANAGEMENT SYSTEM !!!! LOGIN IS SUCCESSFUL");
                printf("\n LOADING PLEASE WAIT... \n");

            for(i=0; i<3; i++)
            {
                printf(".");
                Sleep(500);
            }

            printf("\n\n\n\t\t\t\tPress any key to continue...");
            getch();//holds the screen
            break;
        }
        else
        {
            printf("\n        SORRY !!!!  LOGIN IS UNSUCESSFUL");
            a++;
            getch();//holds the screen
        }
    }

	while(a<=2);
	if (a>2)
	{
		printf("\nSorry you have entered the wrong username and password for four times!!!");

		getch();
    }
}

int cFile()
{
    scores = fopen("data3.txt","rb+");

     if(scores == NULL)
    {
        scores = fopen("data3.txt","wb+");

        if(scores == NULL)
        {
            printf("Cannot open file");
            exit(1);
        }
    }
    return 0;
}

void newStud()
{
	int i, count=1;
    system("cls");
    long int recsize;
    recsize=sizeof(a);
    char ch, sav;
	rewind(scores); ///this moves file cursor to start of the file
    	while(fread(&a,recsize,1,scores)==1)  /// read the file and fetch the record one record per fetch
        {
            count++;
        }

        fseek(scores,0,SEEK_END);
        ch = 'y';
        while(ch == 'y')
        {
        char snum[100]="2020-IT-00", countID[100];
    	while(fread(&a,recsize,1,scores)==1)  /// read the file and fetch the record one record per fetch
        {
            count++;
        }
        sprintf(countID, "%d", count);
		strcat(snum, countID);
        strcpy(a.snum, snum);
        printf("\n\n\t=====================================");
        printf("\n\t\tSTUDENT NUMBER:%s",a.snum);
        printf("\n\t\tENTER STUDENT NAME:");
        scanf(" %[^\n]s",a.name);



        printf("\n\tENTER QUIZ 1 SCORE: ");
        scanf("%f",&a.s1);

        printf("\n\tENTER QUIZ 2 SCORE: ");
        scanf("%f",&a.s2);

        printf("\n\tENTER MIDTERMS SCORE: ");
        scanf("%f",&a.s3);

        printf("\n\tENTER FINALS SCORE: ");
        scanf("%f",&a.s4);

       printf("\n\t\tSAVE THIS RECORD? y/n :");
       scanf("%s",&sav);

                   if (sav=='y')
                {
                	count++;
                	while(fread(&a,recsize,1,scores)==1)  /// read the file and fetch the record one record per fetch
			        {
			        	if(strcmp(a.snum,snum) == 0){
			        		count++;
						}

			        }
                    fwrite(&a,sizeof(a),1,scores);
                    printf("\n\t\tSaving this record");
                     for(i=0; i<6; i++)
    {
        printf(".",177);
        Sleep(500);
    }

                }

                        else
                    {
                        printf("\n\t\tSAVING CANCELLED");
                    }

       printf("\n\n\t\tDO YOU WANT TO ADD ANOTHER?[Y/N]: ");
       fflush(stdin);
       ch=getche();

    }
getch();
}

void edStud()
{
    system("cls");
    char sname[100];
    char edit,ch;
    int test=0,i=1;
    long int recsize;
    recsize=sizeof(a);


                ch='y';
                while(ch=='y')
                {
                printf("\n\n\t\tSEARCH STUDENT NUMBER:");
                scanf("%s",&sname);
                rewind(scores);

                while(fread(&a,recsize,1,scores) == 1)  /// fetch all record from file
                {
                    if(strcmp(a.snum,sname) == 0)  ///if entered name matches with that in file
                    {

                        printf("\n\t\tSTUDENT NAME:%s\n",a.name);
                        printf("\n\t\t=========================================================================");
                        printf("\n\t\tQUIZ 1: %1.f      QUIZ 2 : %1.f        MIDTERM : %1.f       FINALS : %1.f",a.s1,a.s2,a.s3,a.s4);
                        printf("\n\t\t=========================================================================");

                        printf("\n\n\t\tWhich scores would you like to EDIT [1/2/3/4]? ");
                        scanf("%s",&edit);
                        switch (edit)
                        {
                            case '1':

                            printf("\n\t\tENTER NEW QUIZ 1 SCORE:");
                            scanf("%f",&a.s1);
                            break;

                            case '2':

                            printf("\n\t\tENTER NEW  QUIZ 2 SCORE:");
                            scanf("%f",&a.s2);
                            break;

                            case '3':

                            printf("\n\t\tENTER NEW MIDTERM SCORE:");
                            scanf("%f",&a.s3);
                            break;

                           case '4':

                            printf("\n\t\tENTER NEW FINALS SCORE:");
                            scanf("%f",&a.s4);
                            break;
                        }

                        printf("\n\t\tUPDATING RECORD");
                          for(i=0; i<6; i++)
                                {
                                    printf(".",177);
                                    Sleep(500);
                                }
                        fseek(scores,-recsize,SEEK_CUR); /// move the cursor 1 step back from current position
                        fwrite(&a,recsize,1,scores);/// override the record
                        break;
                    }
                }
                    printf("\n\n\t\tModify another record(y/n)?:");
                    fflush(stdin);
                    ch=getche();


            }
getch();
}

void delStud()
{
    system("cls");
    int j;
    char ch, del;
    char snum[100];
    long int recsize;
    FILE *ft;
    recsize = sizeof(a);


                gotoxy(25,6);
                printf("Search Student Number to Delete: ");
                scanf("%s",&snum);
                printf("\n\t\tAre you sure you want to delete this record? y/n : ");
                scanf("%s", &del);
                ft = fopen("Temp.txt","wb");  /// create a intermediate file for temporary storage
                rewind(scores); /// move record to starting of file

                if ((del =='y')&&(del!='n'))
                {
                while(fread(&a,recsize,1,scores) == 1)  /// read all records from file
                {
                    if(strcmp(a.snum,snum)!=0)
                    {
                        fwrite(&a,recsize,1,ft); /// move all records except the one that is to be deleted to temp file
                    }
                }
                printf("\n\t\tDeleting record");
                             for(j = 0; j < 6; j++)
                             {
                                 printf(".",177);
                                 Sleep(500);
                             }
                             printf("\n\n\t\tRecord deleted.");
                fclose(scores);
                fclose(ft);
                remove("data3.txt"); /// remove the orginal file
                rename("Temp.txt","data3.txt"); /// rename the temp file to original file name
                scores = fopen("data3.txt", "rb+");

                }
                else if (del=='n') {
                         remove("data3.txt"); /// remove the orginal file
                        rename("Temp.txt","data3.txt"); /// rename the temp file to original file name
                        scores = fopen("data3.txt", "rb+");
                    printf("\n\n\t\tDeleting Canceled.");
                }

            getch();
}

void sStud()
{
    system("cls");
    char snum[100];
    long int recsize;
    recsize=sizeof(a);

    gotoxy(25,5);
    printf("Search Student Number:");
    scanf("%s",&snum);
    rewind(scores);

                while(fread(&a,recsize,1,scores)==1)  /// fetch all record from file
                {
                    if(strcmp(a.snum,snum) == 0)  ///if entered name matches with that in file
                    {
                         gotoxy(0,8);
                         printf("\t\t==================================================================================================");
                         gotoxy(0,9);
                         printf("\t\t%s\t\t%s \t\t%.1f \t\t%.1f \t\t%.1f \t\t%.1f \n\n",a.snum,a.name,a.s1,a.s2,a.s3,a.s4);
                         gotoxy(0,10);
                         printf("\t\t==================================================================================================");
                    }
                }
                printf("\n\nPress any key to RETURN to MAIN MENU");
                getch();


}

void dStud()
{
    system("cls");
    long int recsize;
    recsize=sizeof(a);

            gotoxy(25,4);
            printf("STUDENTS's RECORD LIST");
            rewind(scores); ///this moves file cursor to start of the file
            while(fread(&a,recsize,1,scores)==1)  /// read the file and fetch the record one record per fetch
            {
                printf("\t\n\n%s \t%s \t%.1f \t%.1f \t%.1f \t%.1f",a.snum,a.name,a.s1,a.s2,a.s3,a.s4);
            }
            getch();
}

void studGrade()
{
    system("cls");
    double average;
    int passed=0, failed=0;
    char type;
    long int recsize;
    recsize=sizeof(a);

    int r,q;

    gotoxy(15,6);
    printf("Computing the Grade");

    //PlaySound(TEXT("1.wav"),NULL,SND_SYNC);

    gotoxy(35,6);
    for(r=0;r<=20;r++)
    {
        for(q=1;q<=100000000;q++);
        printf("%c",177);
    }
    gotoxy(22,10);
    printf("100 PERCENT COMPLETED");
    gotoxy(22,13);
    printf("Press ENTER key to display");
    //PlaySound(TEXT("2.wav"),NULL,SND_SYNC);
    getch();
    system("cls");
    cFile();

    gotoxy(17 , 5);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 SUMMARY OF GRADE REPORT \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

    gotoxy(5, 6);
    printf("============================================================================");

    gotoxy(12, 7);
    printf("STUDENT NAME\t\tAVERAGE\t\tGRADE LETTER ");

    gotoxy(5,8);
    printf("============================================================================");

     while(fread(&a,recsize,1,scores)==1)
        {
            average=(a.s1+a.s2+a.s3+a.s4)/4;

             if(average>=90)
            {
                type='A';
                passed++;
            }
            else if((average>=81)&&(average<=91))
            {
                type='B';
                passed++;
            }
            else if((average>=75)&&(average<=80))
            {
                type='C';
                failed++;
            }
            else if(average<75)
            {
                type='F';
                failed++;
            }

                printf("\n\n\t\t%s\t\t\t%.2f\t\t\t  %c",a.name,average,type);
        }
           printf("\n\n\n\n\t\tTOTAL PASSED : %d",passed);
           printf("\n\t\tTOTAL FAILED : %d",failed);
           printf("\n\n\nPress any key to RETURN to MAIN MENU");
           getch();
    }
void summary()
{
    system("cls");
    int passed=0, failed=0, drop=0;
    float average;
    char type;
    long int recsize;
    recsize=sizeof(a);
    cFile();

    gotoxy(40,4);
    printf("Technological University of the Philippines");
    gotoxy(54,5);
    printf("SUMMARY OF GRADE");
    gotoxy(15,10);
    printf("Subject Code : CC131");
    gotoxy(15,12);
    printf("Subject Description : Computer Programming 2");
    gotoxy(15,14);
    printf("Semester : First Semester");
    gotoxy(45,14);
    printf("SY : 2020-2021");
    gotoxy(70,10);
    printf("Day/Time : Thursday 07:00 - 12:00 am");
    gotoxy(70,12);
    printf("Room : 1");

    gotoxy(19, 17);
    printf("==============================================================================");
    gotoxy(19,18);
    printf("\tSTUDENT NUMBER\t\tNAME\t\t\tGRADE\t\tREMARKS");
    gotoxy(19, 19);
    printf("==============================================================================");

rewind(scores);
  while(fread(&a,recsize,1,scores)==1)
        {
            average=(a.s1+a.s2+a.s3+a.s4)/4;

             if(average>=90)
            {
                type='A';
                passed++;
            }
            else if((average>=81)&&(average<=91))
            {
                type='B';
                passed++;
            }
            else if((average>=75)&&(average<=80))
            {
                type='C';
                failed++;
            }
            else if(average<75)
            {
                type='F';
                failed++;
            }
            if (average==0)
            {
                type='D';
                drop++;
            }

                printf("\n\t\t\t2021-IT-%s\t\t%s\t\t\t%.2f \t\t%c",a.snum,a.name,average,type);
    }
    gotoxy(50,40);
    //printf("\n\n\n\n\t\tTOTAL STUDENTS : %d",a.stud);
    printf("\n\n\t\tTOTAL PASSED : %d",passed);
    printf("\n\n\t\tTOTAL FAILED : %d",failed);
    printf("\n\n\t\tTOTAL DROPPED : %d",drop);
    gotoxy(50,50);
    printf("Faculty Department");
    printf("\t\tDate : March 2021 ");


    getch();
}


void intro()
{
 system("cls");
 gotoxy(25 , 5);
 printf("PROGRAMMERS:");
 gotoxy(28 , 7);
 printf("KATE FEBE B. ESCOTIDO");
 gotoxy(28 , 9);
 printf("KAIROS RAMIREZ");
 gotoxy(28 , 11);
 printf("JAMIEL R. SUMERACRUZ");
 getch();
}

int main()
{
    system("color 5");
  //login();
    intro();
    char menu;


    FILE* scores;
    FILE* ft;
    FILE *dat;
    FILE* ft1;

    cFile();
    while(1)
        {
            system("cls");
            gotoxy(13 , 3);
            printf("MAIN MENU");
            gotoxy(14 , 6);
            printf("WANT DO YOU WANT TO DO?");
            gotoxy(14 , 8);
            printf("1.ADD NEW STUDENT");
            gotoxy(14 , 10);
            printf("2.EDIT STUDENT");
            gotoxy(14 , 12);
            printf("3.DELETE STUDENT ");
            gotoxy(14 , 14);
            printf("4.DISPLAY STUDENT");
            gotoxy(14 , 16);
            printf("5.DISPLAY ALL");
            gotoxy(14 , 18);
            printf("6.COMPUTE GRADE");
            gotoxy(14 , 20);
            printf("7.SUMMARY");
            gotoxy(14 , 22);
            printf("8.EXIT");
            gotoxy(14 , 24);
            printf("Please Enter Your Choice [1/2/3/4/5/6]: ");
            scanf("%d",&menu);

        switch (menu)
        {
            case 1:
                   newStud();
                   break;

            case 2:
                    edStud();
                    break;

            case 3:
                    delStud();
                    break;

            case 4:
                    sStud();
                    break;
            case 5:
                    dStud();
                    break;

           case 6:
                    studGrade();
                    break;

            case 7:
                    summary();
                    break;
            case 8:
                exit(0);
        }
    }
        return 0;
}



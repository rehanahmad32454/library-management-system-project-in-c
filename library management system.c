#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<dos.h>
struct date dt;
struct lib
{
char book[30];
char auth[30];
int stock;
}s;
struct issue
{
char na[30];
char cl[10];
char dep[10];
char bk[30];
int da;
int mo;
int ye;
int r;
}s1;
struct password
{
char uss[30];
char pss[30];
char r[50];
}p;
void dep();
void intro();
void login();
void forget();
void bca_lib();
void bbm_lib();
void chapass();
void bbm_stud();
void lib_menu();
void bca_stud();
void security();
void book_dep();
void stud_menu();
void lib_opt_ch();
void stud_opt_ch();
void in_book(char lib_file[]);
void dis_book(char lib_file[]);
void del_book(char lib_file[]);
void upd_book(char lib_file[]);
void sort_book(char lib_file[]);
void dis_stud(char stud_file[]);
void sort_stud(char stud_file[]);
void search_book(char lib_file[]);
void search_stud(char stud_file[]);
void upd_stud(char lib_file[],char stud_file[]);
void ret_book(char lib_file[],char stud_file[]);
void issue_book(char lib_file[],char stud_file[]);
int m;
FILE *fp,*ftemp,*fp1;
long int si=sizeof(s);
long int si2=sizeof(p);
long int si1=sizeof(s1);
void in_book(char lib_file[])
{
fp=fopen(lib_file,"ab");
printf("\nENTER BOOK NAME=");
scanf("%s",s.book);
printf("\nENTER STOCK=");
scanf("%d",&s.stock);
printf("\nENTER AUTHOR NAME=");
scanf("%s",s.auth);
fwrite(&s,sizeof(s),1,fp);
fclose(fp);
}
void dis_book(char lib_file[])
{
fp=fopen(lib_file,"rb");
printf(" _____________________________________________________");
printf("\n|   BOOK NAME\t\tSTOCK\t\tAUTHOR NAME   |");
printf("\n|_____________________________________________________|");
while(fread(&s,sizeof(s),1,fp)==1)
{
printf("\n|   %s\t\t%d\t\t%s\t      |",s.book,s.stock,s.auth);
}
printf("\n|_____________________________________________________|");
fclose(fp);
}
void del_book(char lib_file[])
{
char book[30];
int p=0,c=0,p1=0;
fp1=fopen(lib_file,"rb");
printf("\nENTER BOOK NAME FOR DELETING=");
scanf("%s",book);
while(fread(&s1,sizeof(s1),1,fp1)==1)
{
c++;
if(strcmpi(book,s1.bk)==0)
{
p=1;
break;
}
}
if(p==1)
printf("\nTHIS BOOK CANNOT DELETED BECAUSE IT'S ISSUED BY A PERSON");
if(c>=0&&p==0)
{
fp=fopen(lib_file,"rb");
ftemp=fopen("temp1.txt","wb");
while(fread(&s,sizeof(s),1,fp)==1)
{
if(strcmpi(book,s.book)!=0)
fwrite(&s,sizeof(s),1,ftemp);
else
p1=1;
}
fclose(fp);
fclose(ftemp);
remove(lib_file);
rename("temp1.txt",lib_file);
if(p1==0)
printf("\nBOOK NOT FOUND");
else
printf("\nBOOK RECORD DELETED SUCCESSFULLY");
}
fclose(fp1);
}
void upd_book(char lib_file[])
{
char bk1[30];
int f=0;
printf("\nENTER BOOK NAME FOR UPDATE=");
scanf("%s",bk1);
fp=fopen(lib_file,"rb+");
while(fread(&s,sizeof(s),1,fp)==1)
{
if(strcmpi(s.book,bk1)==0)
{
printf("\nENTER BOOK NAME=");
scanf("%s",s.book);
printf("\nENTER STOCK=");
scanf("%d",&s.stock);
printf("\nENTER AUTHOR NAME=");
scanf("%s",s.auth);
fseek(fp,-si,1);
fwrite(&s,sizeof(s),1,fp);
f=1;
break;
}
}
if(f==0)
printf("\nBOOK NOT FOUND");
else
printf("\nBOOK RECORD UPDATED SUCCESSFULLY");
fclose(fp);
}
void search_book(char lib_file[])
{
char bk[30];
int p=0,m=0;
fp=fopen(lib_file,"rb");
printf("\nENTER BOOK NAME FOR SEARCHING=");
scanf("%s",bk);
while(fread(&s,sizeof(s),1,fp)==1)
{
if(strcmpi(bk,s.book)==0)
{
if(m==0)
{
printf(" _____________________________________________________");
printf("\n|   BOOK NAME\t\tSTOCK\t\tAUTHOR NAME   |");
printf("\n|_____________________________________________________|");
m++;
}
printf("\n|   %s\t\t%d\t\t%s\t      |",s.book,s.stock,s.auth);
p=1;
}
}
if(p==0)
printf("\nBOOK NOT FOUND");
else
{
printf("\n|_____________________________________________________|");
printf("\n\nRECORD SERACHED SUCCESSFULLY");
}
fclose(fp);
}
void sort_book(char lib_file[])
{
struct lib temp,st[50];
int i,j,n=0;
fp=fopen(lib_file,"rb");
while(fread(&s,sizeof(s),1,fp)==1)
st[n++]=s;
for(i=0;i<n-1;i++)
{
for(j=i+1;j<n;j++)
{
if(strcmpi(st[i].book,st[j].book)>0)
{
temp=st[i];
st[i]=st[j];
st[j]=temp;
}
}
}
printf(" _____________________________________________________");
printf("\n|   BOOK NAME\t\tSTOCK\t\tAUTHOR NAME   |");
printf("\n|_____________________________________________________|");
for(i=0;i<n;i++)
printf("\n|   %s\t\t%d\t\t%s\t      |",st[i].book,st[i].stock,st[i].auth);
printf("\n|_____________________________________________________|");
fclose(fp);
}
void issue_book(char lib_file[],char stud_file[])
{
char bk[30],dep[5]={"BCA"};
char bca_cl[4][40]={"BCA-I","BCA-II","BCA-III"};
char bbm_cl[4][40]={"BBM-I","BBM-II","BBM-III"};
int p=0,opt,i;
fp=fopen(lib_file,"rb+");
fp1=fopen(stud_file,"ab");
printf("\nENTER BOOK NAME=");
scanf("%s",bk);
while(fread(&s,sizeof(s),1,fp)==1)
{
if(strcmpi(bk,s.book)==0&&s.stock>0)
{
p=1;
break;
}
}
if(p==0)
printf("\nTHIS BOOK IS CURRENTLY UNAVAILABLE");
else
{
p=0;
printf("\nENTER YOUR NAME=");
scanf("%s",s1.na);
printf("CHOOSE CLASS:");
if(strcmpi(lib_file,"bca_lib.txt")==0)
printf("\n1-BCA-I\t\t2-BCA-II\t3-BCA-III\n");
else
printf("\n1-BBM-I\t\t2-BBM-II\t3-BBM-III");
printf("\nENTER OPTION(1-3)=");
scanf("%d",&opt);
while(!(opt>0&&opt<4))
{
if(strcmpi(lib_file,"bca_lib.txt")==0)
printf("\n1-BCA-I\t\t2-BCA-II\t3-BCA-III");
else
printf("\n1-BBM-I\t\t2-BBM-II\t3-BBM-III\n");
printf("\nPLEASE ENTER CORRECT OPTION:");
scanf("%d",&opt);
}
if(strcmpi(lib_file,"bca_lib.txt")==0)
strcpy(s1.cl,bca_cl[opt-1]);
else
strcpy(s1.cl,bbm_cl[opt-1]);
printf("\nENTER YOUR ROLL=");
scanf("%d",&s1.r);
strcpy(s1.dep,dep);
strcpy(s1.bk,bk);
getdate(&dt);
s1.da=dt.da_day;
s1.mo=dt.da_mon;
s1.ye=dt.da_year;
s.stock--;
fseek(fp,-si,1);
fwrite(&s1,sizeof(s1),1,fp1);
fwrite(&s,sizeof(s),1,fp);
}
fclose(fp1);
fclose(fp);
}
void ret_book(char lib_file[],char stud_file[])
{
char bk[30],bk1[30];
int p=0,roll,i=0,j;
fp=fopen(lib_file,"rb+");
fp1=fopen(stud_file,"rb");
printf("\nENTER STUDENT ROLL NO FOR RETURN BOOK=");
scanf("%d",&roll);
printf("\nENTER BOOK NAME FOR RETURNING=");
scanf("%s",bk1);
ftemp=fopen("temp2.txt","wb");
while(fread(&s1,sizeof(s1),1,fp1)==1)
{
if(s1.r!=roll||strcmpi(s1.bk,bk1)!=0)
fwrite(&s1,sizeof(s1),1,ftemp);
else
{
p=1;
strcpy(bk,s1.bk);
i++;
}
}
fclose(fp1);
fclose(ftemp);
remove(stud_file);
rename("temp2.txt",stud_file);
if(p==0)
printf("\nSTUDENT RECORD NOT FOUND");
else
printf("\nBOOK RETURNED SUCCESSFULLY");
while(fread(&s,sizeof(s),1,fp)==1)
{
if(strcmpi(bk,s.book)==0)
{
for(j=1;j<=i;j++)
s.stock++;
fseek(fp,-si,1);
fwrite(&s,sizeof(s),1,fp);
}
}
fclose(fp);
}
void search_stud(char stud_file[])
{
int p=0,m=0,r;
fp=fopen(stud_file,"rb");
printf("\nENTER STUDENT ROLL FOR SEARCHING=");
scanf("%d",&r);
while(fread(&s1,sizeof(s1),1,fp)==1)
{
if(s1.r==r)
{
if(m==0)
{
printf(" ________________________________________________________________________");
printf("\n|    NAME\tCLASS\tROLL\tDEPARTMENT  BOOK NAME   ISSUE DATE       |");
printf("\n|________________________________________________________________________|");
m++;
}
if((s1.da>=1&&s1.da<=9)&&(s1.mo>=1&&s1.mo<=9))
printf("\n|    %s\t%s\t%d\t%s\t     %s   \t%d/%d/%d         |",s1.na,s1.cl,s1.r,s1.dep,s1.bk,s1.da,s1.mo,s1.ye);
if((s1.da>=1&&s1.da<=9)&&(s1.mo>9)||(s1.mo>=1&&s1.mo<=9)&&(s1.da>9))
printf("\n|    %s\t%s\t%d\t%s\t     %s   \t%d/%d/%d        |",s1.na,s1.cl,s1.r,s1.dep,s1.bk,s1.da,s1.mo,s1.ye);
if(s1.da>9&&s1.mo>9)
printf("\n|    %s\t%s\t%d\t%s\t     %s   \t%d/%d/%d       |",s1.na,s1.cl,s1.r,s1.dep,s1.bk,s1.da,s1.mo,s1.ye);
p=1;
}
}
if(p==0)
printf("\nSTUDENT NOT FOUND");
else
{
printf("\n|________________________________________________________________________|");
printf("\n\nRECORD SEARCHED SUCCESSFULLY");
}
fclose(fp);
}
void dis_stud(char stud_file[])
{
fp1=fopen(stud_file,"rb");
printf(" ________________________________________________________________________");
printf("\n|    NAME\tCLASS\tROLL\tDEPARTMENT  BOOK NAME   ISSUE DATE       |");
printf("\n|________________________________________________________________________|");
while(fread(&s1,sizeof(s1),1,fp1)==1)
{
if((s1.da>=1&&s1.da<=9)&&(s1.mo>=1&&s1.mo<=9))
printf("\n|    %s\t%s\t%d\t%s\t     %s   \t%d/%d/%d         |",s1.na,s1.cl,s1.r,s1.dep,s1.bk,s1.da,s1.mo,s1.ye);
if((s1.da>=1&&s1.da<=9)&&(s1.mo>9)||(s1.mo>=1&&s1.mo<=9)&&(s1.da>9))
printf("\n|    %s\t%s\t%d\t%s\t     %s   \t%d/%d/%d        |",s1.na,s1.cl,s1.r,s1.dep,s1.bk,s1.da,s1.mo,s1.ye);
if(s1.da>9&&s1.mo>9)
printf("\n|    %s\t%s\t%d\t%s\t     %s   \t%d/%d/%d       |",s1.na,s1.cl,s1.r,s1.dep,s1.bk,s1.da,s1.mo,s1.ye);
}
printf("\n|________________________________________________________________________|");
fclose(fp1);
}
void upd_stud(char lib_file[],char stud_file[])
{
int f=0,r,i,opt;
char bca_cl[4][40]={"BCA-I","BCA-II","BCA-III"};
char bbm_cl[4][40]={"BBM-I","BBM-II","BBM-III"};
printf("\nENTER STUDENT ROLL NO FOR UPDATE=");
scanf("%d",&r);
fp=fopen(stud_file,"rb+");
while(fread(&s1,sizeof(s1),1,fp)==1)
{
if(r==s1.r)
{
printf("\nENTER YOUR NAME=");
scanf("%s",s1.na);
printf("CHOOSE CLASS:");
if(strcmpi(lib_file,"bca_lib.txt")==0)
printf("\n1-BCA-I\t\t2-BCA-II\t3-BCA-III\n");
else
printf("\n1-BBM-I\t\t2-BBM-II\t3-BBM-III");
printf("\nENTER OPTION(1-3)=");
scanf("%d",&opt);
while(!(opt>0&&opt<4))
{
if(strcmpi(lib_file,"bca_lib.txt")==0)
printf("\n1-BCA-I\t\t2-BCA-II\t3-BCA-III");
else
printf("\n1-BBM-I\t\t2-BBM-II\t3-BBM-III\n");
printf("\nPLEASE ENTER CORRECT OPTION:");
scanf("%d",&opt);
}
if(strcmpi(lib_file,"bca_lib.txt")==0)
strcpy(s1.cl,bca_cl[opt-1]);
else
strcpy(s1.cl,bbm_cl[opt-1]);
printf("\nENTER YOUR ROLL=");
scanf("%d",&s1.r);
fseek(fp,-si1,1);
fwrite(&s1,sizeof(s1),1,fp);
f=1;
break;
}
}
if(f==0)
printf("\nSTUDENT NOT FOUND");
else
printf("\nSTUDENT RECORD UPDATED SUCCESSFULLY");
fclose(fp);
}
void sort_stud(char stud_file[])
{
struct issue temp,st1[50];
int i,j,n=0;
fp=fopen(stud_file,"rb");
printf(" ________________________________________________________________________");
printf("\n|    NAME\tCLASS\tROLL\tDEPARTMENT  BOOK NAME   ISSUE DATE       |");
printf("\n|________________________________________________________________________|");
while(fread(&s1,sizeof(s1),1,fp)==1)
st1[n++]=s1;
for(i=0;i<n-1;i++)
{
for(j=i+1;j<n;j++)
{
if(strcmpi(st1[i].na,st1[j].na)>0)
{
temp=st1[i];
st1[i]=st1[j];
st1[j]=temp;
}
}
}
for(i=0;i<n;i++)
{
if((st1[i].da>=1&&st1[i].da<=9)&&(st1[i].mo>=1&&st1[i].mo<=9))
printf("\n|    %s\t%s\t%d\t%s\t     %s   \t%d/%d/%d         |",st1[i].na,st1[i].cl,st1[i].r,st1[i].dep,st1[i].bk,st1[i].da,st1[i].mo,st1[i].ye);
if((st1[i].da>=1&&st1[i].da<=9)&&(st1[i].mo>9)||(st1[i].mo>=1&&st1[i].mo<=9)&&(st1[i].da>9))
printf("\n|    %s\t%s\t%d\t%s\t     %s   \t%d/%d/%d        |",st1[i].na,st1[i].cl,st1[i].r,st1[i].dep,st1[i].bk,st1[i].da,st1[i].mo,st1[i].ye);
if(st1[i].da>9&&st1[i].mo>9)
printf("\n|    %s\t%s\t%d\t%s\t     %s   \t%d/%d/%d       |",st1[i].na,st1[i].cl,st1[i].r,st1[i].dep,st1[i].bk,st1[i].da,st1[i].mo,st1[i].ye);
}
printf("\n|________________________________________________________________________|");
fclose(fp);
}
void chapass()
{
char pss1[30],pss2[30];
int p1=0;
fp=fopen("password.txt","rb+");
printf("\nENTER YOUR PASSWORD=");
scanf("%s",pss1);
while(fread(&p,sizeof(p),1,fp)==1)
{
if(strcmpi(p.pss,pss1)==0)
{
printf("\nENTER NEW PASSWORD=");
scanf("%s",pss2);
h:
printf("\nENTER CONFIRM PASSWORD=");
scanf("%s",p.pss);
if(strcmpi(pss2,p.pss)==0)
{
fseek(fp,-si2,1);
fwrite(&p,sizeof(p),1,fp);
p1=1;
break;
}
else
{
printf("\nPLEASE ENTER CORRECT CONFIRM PASSWORD");
goto h;
}
}
}
if(p1==0)
printf("\nINCORRECT PASSWORD");
else
printf("\nPASSWORD CHANGED SUCCESSFULLY");
fclose(fp);
}
void forget()
{
char r1[50];
int p1=0;
fp=fopen("password.txt","rb+");
printf("\nENTER YOUR EMAIL=");
scanf("%s",r1);
while(fread(&p,sizeof(p),1,fp)==1)
{
if(strcmpi(p.r,r1)==0)
{
printf("\nENTER NEW PASSWORD=");
scanf("%s",p.pss);
fseek(fp,-si2,1);
fwrite(&p,sizeof(p),1,fp);
p1=1;
break;
}
}
if(p1==0)
printf("\nINCORRECT EMAIL");
else
printf("\nPASSWORD CHANGED SUCCESSFULLY");
fclose(fp);
}
void login()
{
int ch1;
int p1=0;
char us1[30],ps1[30];
clrscr();
fp=fopen("password.txt","ab");
fp1=fopen("password.txt","rb");
if(fread(&p,sizeof(p),1,fp1)!=1)
{
printf("\n\n\n\t\t\t\t-----------------------------");
printf("\n\t\t\t\t|\t\t            |");
printf("\n\t\t\t\t| REGISTER LIBRARIAN ID     |");
printf("\n\t\t\t\t|\t\t            |");
printf("\n\t\t\t\t-----------------------------");
printf("\n\n\n\t\t\t\tENTER YOUR ID=");
scanf("%s",p.uss);
printf("\n\t\t\t\tENTER YOUR PASSWORD=");
scanf("%s",p.pss);
printf("\n\t\t\t\tENTER YOUR EMAIL=");
scanf("%s",p.r);
fwrite(&p,sizeof(p),1,fp);
printf("\n\t\t\t\tLIBRARIAN ID CREATED SUCCESSFULLY");
}
else
{
printf("\n\n\n\t\t\t\t--------------");
printf("\n\t\t\t\t|\t     |");
printf("\n\t\t\t\t| LOGIN PAGE |");
printf("\n\t\t\t\t|\t     |");
printf("\n\t\t\t\t--------------");
fp=fopen("password.txt","rb");
printf("\n\n\n\t\t\tENTER YOUR ID=");
scanf("%s",us1);
printf("\n\t\t\tENTER YOUR PASSWORD=");
scanf("%s",ps1);
while(fread(&p,sizeof(p),1,fp)==1)
{
if(strcmpi(p.uss,us1)==0&&strcmpi(p.pss,ps1)==0)
{
p1=1;
break;
}
}
if(p1==0)
printf("\n\t\t\tACCESS DENIED!!!");
else
{
lib_menu();
}
}
fclose(fp1);
fclose(fp);
}
void intro()
{
clrscr();
printf("\n\t\t\t____________________________________");
printf("\n\t\t\t|\t\t\t\t    |");
printf("\n\t\t\t|     LIBRARY MANAGEMENT PROJECT    |\n");
printf("\t\t\t|___________________________________|");
printf("\n\n\t\t\t\t   DISCRIPTION\n");
printf("\n\t----------------------------------------------------------------------");
printf("\n\t|\t\t\t\t\t\t\t\t     |");
printf("\n\t| HELLO EVERYONE MY NAME IS........I AM THE DEVELOPER OF THIS        |");
printf("\n\t|\t\t\t\t\t\t\t\t     |");
printf("\n\t| PROJECT AND THIS PROJECT IS DEVELOPED UNDER THE GUIDANCE OF OUR    |");
printf("\n\t|\t\t\t\t\t\t\t\t     |");
printf("\n\t| RESPECTABLE ............. SIR.\t\t\t\t     |");
printf("\n\t|\t\t\t\t\t\t\t\t     |");
printf("\n\t|\t\t\t\t\t\t\t  < next >   |");
printf("\n\t----------------------------------------------------------------------");
getch();
}
void stud_opt_ch()
{
printf("\n\t\t\t|  1-ISSUE BOOK               |");
printf("\n\t\t\t|  2-RETURN BOOK              |");
printf("\n\t\t\t|  3-DISPLAY RECORD           |");
printf("\n\t\t\t|  4-UPDATE RECORD            |");
printf("\n\t\t\t|  5-SEARCH RECORD            |");
printf("\n\t\t\t|  6-SORT RECORD              |");
printf("\n\t\t\t|  7-BACK                     |");
printf("\n\t\t\t|  8-HOME                     |");
printf("\n\t\t\t*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
printf("\n\n\t\t\tENTER YOUR CHOICE=");
}
void lib_opt_ch()
{
printf("\n\t\t\t|  1-INSERT BOOK IN LIBRARY       |");
printf("\n\t\t\t|  2-DISPLAY BOOK IN LIBRARY      |");
printf("\n\t\t\t|  3-SEARCH BOOK IN LIBRARY       |");
printf("\n\t\t\t|  4-DELETE BOOK IN LIBRARY       |");
printf("\n\t\t\t|  5-UPDATE BOOK RECORD           |");
printf("\n\t\t\t|  6-SORT BOOK IN LIBRARY         |");
printf("\n\t\t\t|  7-BACK                         |");
printf("\n\t\t\t|  8-HOME                         |");
printf("\n\t\t\t*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
printf("\n\n\t\t\tENTER YOUR CHOICE=");
}
void dep()
{
clrscr();
printf("\n\n\n\t\t\t*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
printf("\n\t\t\t|  1-BCA DEPARTMENT         |");
printf("\n\t\t\t|  2-BBM DEPARTMENT         |");
printf("\n\t\t\t|  3-BACK                   |");
printf("\n\t\t\t|  4-HOME                   |");
printf("\n\t\t\t*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
printf("\n\n\t\t\tENTER YOUR CHOICE=");
}
void main()
{
int ch;
if(m==0)
{
intro();
m++;
}
do
{
clrscr();
printf("\n\n\n\t\t\t*-*-*-*-*-*-MENU*-*-*-*-*-*-*");
printf("\n\t\t\t|  1-STUDENT                |");
printf("\n\t\t\t|  2-LIBRARY                |");
printf("\n\t\t\t|  3-PASSWORD SETTING       |");
printf("\n\t\t\t|  4-EXIT                   |");
printf("\n\t\t\t*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
printf("\n\n\t\t\tENTER YOUR CHOICE=");
scanf("%d",&ch);
clrscr();
switch(ch)
{
case 1:
stud_menu();
break;
case 2:
login();
break;
case 3:
security();
break;
case 4:
exit(0);
default:
printf("\nINVALID CHOICE!!!");
}
getch();
}while(2>1);
}
void stud_menu()
{
while(1)
{
int ch1;
dep();
scanf("%d",&ch1);
switch(ch1)
{
case 1:
bbm_stud();
break;
case 2:
bca_stud();
case 3:
main();
break;
case 4:
main();
break;
default:
printf("\nINVALID CHOICE!!!");
}
getch();
}
}
void bbm_stud()
{
int ch4;
while(1)
{
char lib_file[20]="bca_lib.txt";
char stud_file[20]="bca_stud.txt";
clrscr();
printf("\n\n\n\t\t\t*-*-*-*-*BCA DEPARTMENT-*-*-*-*");
stud_opt_ch();
scanf("%d",&ch4);
clrscr();
switch(ch4)
{
case 1:
issue_book(lib_file,stud_file);
break;
case 2:
ret_book(lib_file,stud_file);
break;
case 3:
dis_stud(stud_file);
break;
case 4:
upd_stud(lib_file,stud_file);
break;
case 5:
search_stud(stud_file);
break;
case 6:
sort_stud(stud_file);
break;
case 7:
stud_menu();
break;
case 8:
main();
break;
default:
printf("\nINVALID CHOICE!!!");
}
getch();
}
}
void bca_stud()
{
int ch4;
char lib_file[20]="bbm_lib.txt";
char stud_file[20]="bbm_stud.txt";
while(1)
{
clrscr();
printf("\n\n\n\t\t\t*-*-*-*-BBM DEPARTMENT*-*-*-*-");
stud_opt_ch();
scanf("%d",&ch4);
clrscr();
switch(ch4)
{
case 1:
issue_book(lib_file,stud_file);
break;
case 2:
ret_book(lib_file,stud_file);
break;
case 3:
dis_stud(stud_file);
break;
case 4:
upd_stud(lib_file,stud_file);
break;
case 5:
search_stud(stud_file);
break;
case 6:
sort_stud(stud_file);
break;
case 7:
stud_menu();
break;
case 8:
main();
break;
default:
printf("\nINVALID CHOICE!!!");
}
getch();
}
}
void bca_lib()
{
int ch3;
char lib_file[20]="bca_lib.txt";
while(1)
{
clrscr();
printf("\n\n\n\t\t\t*-*-*-*-*-*BCA LIBRARY*-*-*-*-*-*-*");
lib_opt_ch();
scanf("%d",&ch3);
clrscr();
switch(ch3)
{
case 1:
in_book(lib_file);
break;
case 2:
dis_book(lib_file);
break;
case 3:
search_book(lib_file);
break;
case 4:
del_book(lib_file);
break;
case 5:
upd_book(lib_file);
break;
case 6:
sort_book(lib_file);
break;
case 7:
lib_menu();
break;
case 8:
main();
break;
default:
printf("\nINVALID CHOICE!!!");
}
getch();
}
}
void bbm_lib()
{
int ch3;
while(1)
{
char lib_file[20]="bbm_lib.txt";
clrscr();
printf("\n\n\n\t\t\t*-*-*-*-*-*BBM LIBRARY*-*-*-*-*-*-*");
lib_opt_ch();
scanf("%d",&ch3);
clrscr();
switch(ch3)
{
case 1:
in_book(lib_file);
break;
case 2:
dis_book(lib_file);
break;
case 3:
search_book(lib_file);
break;
case 4:
del_book(lib_file);
break;
case 5:
upd_book(lib_file);
break;
case 6:
sort_book(lib_file);
break;
case 7:
lib_menu();
break;
case 8:
main();
break;
default:
printf("\nINVALID CHOICE!!!");
}
getch();
fclose(fp);
}
}
void security()
{
int ch;
while(1)
{
clrscr();
printf("\n\n\n\t\t\t*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
printf("\n\t\t\t|  1-CHANGE PASSWORD          |");
printf("\n\t\t\t|  2-FORGET PASSWORD          |");
printf("\n\t\t\t|  3-BACK                     |");
printf("\n\t\t\t|  4-HOME                     |");
printf("\n\t\t\t*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
printf("\n\n\t\t\tENTER YOUR CHOICE=");
scanf("%d",&ch);
clrscr();
switch(ch)
{
case 1:
chapass();
break;
case 2:
forget();
break;
case 3:
main();
break;
case 4:
main();
break;
default:
printf("\nINVALID CHOICE!!!");
}
getch();
}
}
void lib_menu()
{
int ch1;
while(1)
{
dep();
scanf("%d",&ch1);
switch(ch1)
{
case 1:
bca_lib();
break;
case 2:
bbm_lib();
break;
case 3:
main();
break;
case 4:
main();
break;
default:
printf("\nINVALID CHOICE!!!");
}
getch();
}
}

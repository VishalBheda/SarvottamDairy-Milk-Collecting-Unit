/***********************************************************
* PROJECT TITLE : SARVOTTAM DAIRY [ MILK COLLECTION UNIT ] *
* COMPILED ON   : TURBO C++ 3.0                            *
* DEVELOPED BY  : BHEDA VISHAL                             *
*         	 : BOLANIYA KIRAN                           *
* SUBMITED TO   : GUJARAT TECHNICAL UNIVERSITY AHMEDABAD   *
************************************************************/

/*HEADER FILES*/
#include<iostream.h>
#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<dos.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

/* GLOBAL VARIABLES */
int count_menu=1;
int AddData=0;
int invalid=0;
char *pay_date;

/* GLOBAL FUNCTIONS PROTOTYPES */
void 	msgBox(char[25],char);  //FOR DISPLAY MASSAGE
void 	menuCol();              //FOR MENU COLOR
void 	selCol();				//FOR SELECTION CHARACTER COLOR
void	     logo();				//FOR DISPLAY LOGO
void 	clearForm();			//FOR CLEAR FORM
void 	header();				//FOR DISPLAY HEADER
void 	highlight(int);			//FOR DISPLAY SELECTED MENU
void 	box(int,int,int,int,char[15]);//FOR CREATE BOX

void 	mainMenu(char); //FOR DISPLAY MENU

char *getDay(int); //FOR GET DAY
char *getMon(int); //FOR GET MONTH
char *searchFile(); //FOR GET FILE NAME

/* DECLARATION OF CLASSES */

//Declaration of Login Class//
class Login
{
	  char user_name[10];
	  char pass[6];
	public:
	  void login();
	  void changePass();
}lg;

//Declaration of Member Class //
class Member
{
 public:
		int 	 id;
		char 	 name[15];
		char  	 address[25];
		char 	 type[5];
		char     phone[10];
		float 	 tot_milk;
		float 	 tot_rs;

  public:
		void addMember();
		void showMember();
		void delMember();
		void modifyMember();

		void showPayment();
		void payment();
}mb;

//Declaration of Fat Class
class Fat
{
public:
		float fat;
		float fvalue;
public:
		void  showFat();
	    void  updateFvalue();
	    float getRs(float);
}ft;

//Declaration of Milk Class
class Milk : public Member
{
  public:
		int    input_id;
		char   cname[15];
		float  input_milk;
		float  input_fet;
		float  tot_amt;
		char   ctype[5];
		char   date[25];
		char   ses[4];
  public:
		void showSession();
		void collectMilk();
		void search();
}ml;

//Declaration of Ken Class
class Ken : public Milk
{
 public:
	 int 	cKen;
	 float	cfat;
	 float	cweight;

	 int 	fKen;
	 float	ffat;
	 float	fweight;

	 char 	kses[4];
	 char 	kdate[15];

	 public:
		void 	addKen();
		void 	showKen();
}kn;

/*End of Class Declaration*/

//MAIN FUNCTION//
void main()
{
  cout.precision(3);
		Login l;
		l.login();
}

// FOR CLEAR FORM //
void clearForm()
{
	   int i,j;
		for(i=8;i<=23;i++)
			{
				for(j=21;j<=78;j++)
				{
				gotoxy(j+1,i);
				textbackground(BLACK);
				textcolor(WHITE);
				cprintf(" ");
				}
			}
			return;
}

//Start Member Function Declaration

/* FUNCTION FOR LOGIN AND FIRST TIME USER CREATION */
void Login ::login()
{
	char ch;
	char tempuser[15];
	char temppass[6];
	char *day,*mon,*div="-",*year;

	int i=0,flag=0,flag1=0;

	struct date d;
	getdate(&d);

	fstream file1,file2,file3;
	file1.open("user.txt",ios::in);

	system("cls");
		/*USER REGISTRATION*/
		if(file1.read((char*)this,sizeof(lg))==NULL)
		{
			file1.close();

			system("mkdir payment");
				if(d.da_day==1)
				{
					d.da_day=31;
						if(d.da_mon==1)
							d.da_mon=12;
				}
				else
					d.da_day--;

			day=getDay(d.da_day);
			mon=getMon(d.da_mon);
			strcpy(pay_date,"PAYMENT\\");
			strcat(pay_date,day);
			strcat(pay_date,div);
			strcat(pay_date,mon);
			strcat(pay_date,".txt");
			file2.open(pay_date,ios::out);
			file2.close();

			//FOR CREATE KEN FILES//
			file3.open("ken.txt",ios::out);
			struct time t;
			char tempses[4],tempdate[15];
			char sesm[4]="MOR",sese[4]="EVE";

			getdate(&d);
			gettime(&t);

			day= getDay(d.da_day);
			mon= getMon(d.da_mon);

			strcpy(kn.kdate,day);
			strcat(kn.kdate,div);
			strcat(kn.kdate,mon);

			if(t.ti_hour<=12)
				strcpy(kn.kses,sesm);
			else
				strcpy(kn.kses,sese);


				kn.cKen=0;
				kn.fKen=0;
				kn.cfat=0;
				kn.ffat=0;
				kn.cweight=0;
				kn.fweight=0;
				file3.write((char*)&kn,sizeof(kn));
			file3.close();

			file1.open("user.txt",ios::out);

		    textcolor(BLACK);textbackground(7);
			gotoxy(23,18); 	cprintf("       Press [Ctlr+x] for Exit    ");
			selCol(); gotoxy(36,18);cprintf("[Ctrl+x]");

			box(15,5,65,9,"");
		   gotoxy(25,7);cout<<"REGISTER USER NAME AND PASSWORD";
		    box(22,9,56,19,"");
		   gotoxy(26,12);

					cout<<"Enter User Name : ";
					i=0;
					do
					{
					user_name[i]=getch();
						if(user_name[i]==24)
						exit(0);

						if(user_name[i]=='\r')
							break;

						else if(user_name[i]=='\b' && i>0)
						{

							  textbackground(BLACK);
							 textcolor(WHITE);
							  cprintf("%c%c%c",8,32,8);
							  i--;
						}
						else
						{
							cout<<user_name[i];
							i++;
						}
					}while(user_name[i]!='\r');
					user_name[i]='\0';

				gotoxy(26,14); cout<<"Enter Password  : ";
				i=0;
					do
					{
							pass[i]=getch();
							if(pass[i]==24)
								exit(0);

							if(pass[i]=='\r')
							  continue;

							if(i==6)
								break;

							else if(pass[i]=='\b' && i>0)
							{
								textbackground(BLACK);
								textcolor(WHITE);
								cprintf("%c%c%c",8,32,8);
								i--;
							}
							else
							{
								cout << "*";
								i++;
							}
						 }while(i!=6);

				 gotoxy(25,18);
				 textcolor(BLACK);
				 cprintf(" Press Any Key To Cont....   ");
				 getch();

		    file1.write((char*)this,sizeof(lg));
		    file1.close();

	    }

	   /*USER LOGIN*/
	   Enter_User:

	   system("cls");
	   file1.open("user.txt",ios::in);

		 textcolor(BLACK);textbackground(7);  gotoxy(21,18); 	cprintf("       Press [Ctlr+x] for Exit     ");
		 selCol(); gotoxy(34,18);cprintf("[Ctrl+x]");

		  gotoxy(5,24);
		  cout<<"NOTE : press the RED character for perform  specific operation ! ";
		  gotoxy(12,25);cout<<"press Enter to select and Backspace to back to Menu..";
		 box(20,8,55,19," LOG IN ");

		   gotoxy(26,12); cout<<"Enter User Name : ";
					i=0;
					do
					{
					tempuser[i]=getch();
						if(tempuser[i]==24)
						exit(0);

						if(tempuser[i]=='\r')
							break;

						else if(tempuser[i]=='\b' && i>0)
						{

						    textbackground(BLACK);
						    textcolor(WHITE);
							cprintf("%c%c%c",8,32,8);
							i--;
						}
						else
						{
							cout<<tempuser[i];
							i++;
						}
					}while(tempuser[i]!='\r');
					tempuser[i]='\0';

				 for(i=0;i<strlen(tempuser);i++)
				{
				  if(user_name[i]==tempuser[i])
					flag1++;
				}
		  gotoxy(26,14); cout<<"Enter Password  : ";
		   i=0;
				do
				   {
						temppass[i]=getch();
						if(temppass[i]==24)
							exit(0);

						if(temppass[i]=='\r')
						   continue;

						if(i==6)
							break;

						else if(temppass[i]=='\b' && i>0)
						{
							textbackground(BLACK);
							textcolor(WHITE);
							cprintf("%c%c%c",8,32,8);
							i--;
						}
						else
						{
							cout << "*";
							i++;
						}
				 }while(i!=6);

		   flag=0;
		   for(i=0;i<6;i++)
		   {
			if(pass[i]==temppass[i])
				 flag++;
		   }

				gotoxy(26,16);
				textcolor(BLACK);textbackground(7);
				gotoxy(21,18); 	cprintf("          LOGIN      CANCLE      ");
			    selCol(); gotoxy(31,18);cprintf("L"); gotoxy(42,18);cprintf("C");

				ch=getch();

		   if(flag==6 && flag1==strlen(user_name))
		   {
				while(1)
				 {
					 switch(ch)
					 {
						case 'l' :
						case '\r':
								mainMenu(NULL);
								break;

						  case 'c':
						  case '\b':
								exit(0);
							    break;
					 }
				    ch=getch();
				   }
		   }
		   else
		   {
				textcolor(RED);
				if(flag==6)
					msgBox("   Wrong User Name !  ",'a');
				else if(flag1==strlen(user_name))
					msgBox("   Wrong Password !   ",'a');
				else
					msgBox("Invalid user name and pass",'a');

				if(ch=='c')
					exit(0);

			textcolor(WHITE);
			}

system("cls");
cout.flush();
login();
} //End of login()

/* FOR CHANGE PASSWORD */
void Login :: changePass()
{
	int i,flag=0;
	char ch;
	char temppass[6],newpass[6],confpass[6],newpass1[6];

		clearForm();
		box(21,7,79,24," CHANGE PASSWORD ");
			 menuCol();  gotoxy(40,23); 	cout<<"Press [Ctlr+x] for Exit ";
			 selCol(); gotoxy(46,23);cprintf("[Ctrl+x]");

		   fstream file1,file2;
			file1.open("user.txt",ios::in);
			file2.open("tempuser.txt",ios::out);

			file1.read((char*)this,sizeof(lg));
			box(23,9,77,13,"อออออออออออออออออCURRENT PASSWORD");
			gotoxy(33,11);
			cout<<"Enter Current Password : ";

		   i=0;
		   do
			{
				temppass[i]=getch();
				if(temppass[i]==24)
					 goto Exit;

				if(temppass[i]=='\r' || i==6)
					break;

				else if(temppass[i]=='\b' && i>0)
				{
					cprintf("%c%c%c",8,32,8);
				    i--;
				 }
				 else
				{
						cout << "*";
						i++;
				}
		   }while(temppass[i]!='b' || i==6);

		   temppass[i]='\0';

		   for(i=0;i<6;i++)//check current Password
			{
			 if(pass[i]==temppass[i])
				  flag++;
			}

			if(flag==6)
			{
					box(23,15,77,21,"อออออออออออออออออออNEW PASSWORD");
					gotoxy(35,17); cout<<"New Password     : ";

					i=0;
					do
					{
						newpass[i]=getch();
						if(newpass[i]==24)
							  goto Exit;

						if(newpass[i]=='\r')
							continue;

						if( i==6)
							break;

						else if(newpass[i]=='\b' && i>0)
						{
							cprintf("%c%c%c",8,32,8);
							i--;
						}
						else
						{
							cout << "*";
							i++;
						}
					} while(i!=6);

				  strcpy(newpass1,newpass);

				 gotoxy(35,19); cout<<"Confirm Password : ";

				  i=0;
					do
					{
						confpass[i]=getch();
							if(confpass[i]==24)
							   goto Exit;

							if( i==6)
							  break;

							if(newpass[i]=='\r')
							  continue;

							else if(confpass[i]=='\b' && i>0)
						   {
							printf("%c%c%c",8,32,8);
							i--;
						   }
							else
						   {
							cout << "*";
							i++;
						 }
					}while( i!=6);

				  confpass[i]='\0';

				  flag=0;
			   for(i=0;i<6;i++)
			   {
				  if(confpass[i]==newpass1[i])
				  flag++;
			    }

				menuCol();gotoxy(44,23); cprintf("SAVE    CANCLE");
				selCol();gotoxy(44,23); cprintf("S");gotoxy(52,23);cprintf("C");

		    while(1)
			{
				 ch=getch();
				 if(ch=='s' || ch=='c' || ch=='\r' || ch=='\b')
				{
					if(ch=='s' || ch=='\r')
					{
						if(flag==6)
						{

							gotoxy(34,22);
							msgBox("Password Change Successfully!",'m');
							for(i=0;i<6;i++)
							pass[i]=newpass1[i];

							file2.write((char*)this,sizeof(lg));
								file1.close();
								file2.close();

							file1.open("user.txt",ios::out);
							file2.open("tempuser.txt",ios::in);

								while(file2.read((char*)this,sizeof(lg)))
								file1.write((char*)this,sizeof(lg));

								file1.close();
								file2.close();
								system("cls");
								mainMenu(NULL);
						}
						else
						{
							msgBox("Confirm Password Mismatch !",'a');
							changePass();
						}

					  }
					else if(ch== 'c' || ch=='\b')
					{
							Exit:
							file1.close();
							file2.close();
							system("cls");
							mainMenu(NULL);
					}
			    }
			}
		   }
		   else
		   {
				msgBox(" Wrong Password !",'a');
				cout.flush();
				mainMenu(NULL);
		   }

}//End of Change Password

/* FUNCTION FOR SHOW MEMBER */
void Member::showMember()
{
		int count,i,j;

		fstream file;

		file.open("member.txt",ios::in);

		clearForm();
		box(21,7,79,24," MEMBER ");
		textcolor(BLUE);

			gotoxy(30,9);		cprintf("ID   NAME     ADDRESS     TYPE     PHONE  ");
			gotoxy(30,10);		cout<<"---------------------------------------------";
			menuCol();
			gotoxy(22,23);		cprintf("         ADD  DELETE  UPDATE  BACK           MORE         ");
			textcolor(RED);	gotoxy(31,23);     cprintf("A");gotoxy(36,23);cprintf("D");gotoxy(44,23);cprintf("U");gotoxy(52,23);cprintf("B");gotoxy(67,23);cprintf("M");
		   count=11;

	    Cont:
		while(file.read((char*)this,sizeof(mb)))
		{
				gotoxy(30,count);cout<<id;
				gotoxy(35,count);cout<<name;
				gotoxy(44,count);cout<<address;
				gotoxy(56,count);cout<<type;
				gotoxy(65,count);cout<<phone;

			    if(count==20)
				   break;

			   count++;
		}

		file.close();

		switch(getch())
		{
			case 'a':
					addMember();
					break;
			case 'd':
					delMember();
					break;
			case 'u':
					modifyMember();
					break;
			case 'm':
					if(count>=20)
					{
						clearForm();
						textcolor(BLUE);
							gotoxy(30,9);		cprintf("ID   NAME     ADDRESS     TYPE     PHONE");
							gotoxy(30,10);		cprintf("---------------------------------------------");

							menuCol(); gotoxy(22,23);  cprintf("         ADD  DELETE  UPDATE  BACK           MORE         ");
							selCol(); gotoxy(31,23);   cprintf("A");gotoxy(36,23);cprintf("D");gotoxy(44,23);cprintf("U");gotoxy(52,23);cprintf("B");gotoxy(67,23);cprintf("M");

						count=11;
						goto Cont;
					}
					else
						msgBox("   NO MORE DATA EXIST   ",'a');

					break;

			case 'b':
			case '\b':
						system("cls");
						mainMenu(NULL);
					break;
		}//end switch

	showMember();
}//end of show member

/* FUNCTION FOR ADD A NEW MEMBER  */
void Member::addMember()
{
	char cow[5]={'C','O','W'};
	char buff[5]={'B','U','F','F'};
	char temp_phone[10],ch;
	int cnt=0;

	Reenter:

		clearForm();
		box(21,7,79,24," ADD MEMBER ");

	    fstream file,file1;

	    file1.open("member.txt",ios::in);
			while(file1.read((char*)this,sizeof(mb))){}
	    file1.close();

			 menuCol();  gotoxy(40,23); 	cout<<"Press [Ctlr+x] for Exit ";
			 selCol(); gotoxy(46,23);cprintf("[Ctrl+x]");

	    file.open("member.txt",ios::out | ios :: app );
    //	id=100;
		box(30,9,72,21,"");
		id++;
		gotoxy(32,11);	cout<<"Member Id               : "<<id;
		gotoxy(32,13);cout<<"Enter Name              : ";

						do
						{
								name[cnt]=getch();
								if(name[cnt]==24)
								    goto Exit;

								if(cnt=='\r')
									break;

								else if(name[cnt]=='\b' && cnt>0)
								{
									printf("%c%c%c",8,32,8);
									cnt--;
								}
								else if(name[cnt]>=65 && name[cnt]<=122)
								{
								printf("%c",name[cnt]);
								cnt++;
								}
						}while(name[cnt]!='\r');
						name[cnt]='\0';

					    if(strlen(name)==0)
						{
						msgBox("NAME CANN'T BE  LEFT BLANK",'a');
						   goto Reenter;
						}

						cnt=0;
	    gotoxy(32,15);cout<<"Enter Address           : ";
					    do
						{
								address[cnt]=getch();
								if(address[cnt]==24)
								goto Exit;

								if(cnt=='\r')
									break;

								else if(address[cnt]=='\b' && cnt>0)
								{
									printf("%c%c%c",8,32,8);
									cnt--;
								}
								else if(address[cnt]>=65 && address[cnt]<=122)
								{
								printf("%c",address[cnt]);
								cnt++;
								}
						}while(address[cnt]!='\r');
						address[cnt]='\0';

					    if(strlen(address)==0)
					    {
						  msgBox("ADDRESS CANN'T BE LEFT BLANK",'a');
						  goto Reenter;
					    }

	    gotoxy(32,17);	cout<<"Enter Type([C]ow/[B]uf) : ";
					gotoxy(58,17);
					while(1)
					{
						ch=getch();
						if(ch==24)
							 goto Exit;

						if(ch=='c')
						{
							cout<<"COW";
							strcpy(type,cow);
							break;
						}
						else if(ch=='b')
						{
							cout<<"BUFF";
							strcpy(type,buff);
							break;
						}
					}

	    gotoxy(32,19);	cout<<"Enter Phone             : ";
				cnt=0;
					do
					{
						phone[cnt]=getch();
							if(phone[cnt]==24)
							goto Exit;
						if(cnt==10)
							break;

						else if(phone[cnt]=='\b' && cnt>0)
						{
							printf("%c%c%c",8,32,8);
							cnt--;
						}
						else if(phone[cnt]>=48 && phone[cnt]<=57)
						{
							printf("%c",phone[cnt]);
							cnt++;
						}
					}while(cnt!=10);
				   phone[cnt]='\0';

					 tot_milk=0;
					 tot_rs=0;
					 gotoxy(35,23);	cout<<"                        ";
					 gotoxy(22,23);

	    menuCol();gotoxy(44,23); cprintf("SAVE    CANCLE");
	    selCol();gotoxy(44,23); cprintf("S");gotoxy(52,23);cprintf("C");

				while(1)
				{
					switch(getch())
					{
						case 's':
						case '\r':
								file.write((char*)this,sizeof(mb));
								file.flush();
								file.close();

								msgBox("    RECORD INSERTED     ",'m');
								system("cls");
								mainMenu('\r');
							break;
						case 'c':
						case '\b':
								Exit:
								file.close();
								system("cls");
								mainMenu('\r');
							break;
					}
				}
 }//end add Member

//TO Delete Member//
void Member::delMember()
{

   char ch;
   int inputId;
   int  flag=0;

     fstream file1,file2;

     clearForm();
     box(21,7,79,24," DELETE MEMBER ");

	gotoxy(37,22);	cout<<"Press Enter to Continue.....";
	box(23,9,77,13,"");
	gotoxy(42,11);	cout<<"Enter ID: ";
					scanf("%d",&inputId);
    clearForm();
	box(38,9,62,19,"");

		  file1.open("member.txt",ios::in);
		  file2.open("membertemp.txt",ios::out);

			while(file1.read((char*)this,sizeof(mb)))
			{
					if(inputId==id)
					{
						flag=1;

						gotoxy(42,11);  cout<<"Name    : "<<name;
						gotoxy(42,13);  cout<<"Address : "<<address;
						gotoxy(42,15);  cout<<"Type    : "<<type;
						gotoxy(42,17);  cout<<"Phone   : "<<phone;
					}
					else
						file2.write((char*)this,sizeof(mb));
			}

			file2.close();
			file1.close();

		if(flag==0)
			msgBox("       Invalid ID        ",'a');
		else
		{

			box(23,19,77,22,"");
			gotoxy(28,20);
			cout<<"Are You Sure You Want To Delete This Record ?";
		    textbackground(7);textcolor(BLACK); gotoxy(24,21);cprintf("                                                      ");
			gotoxy(46,21);cprintf("YES   NO");
			selCol();gotoxy(46,21);cprintf("Y");gotoxy(52,21);cprintf("N");
			ch=getch();
			gotoxy(26,17);
			cout<<"                                                    ";

			if(ch=='y')
			{
				gotoxy(37,22);
				msgBox("    RECORD DELETED     ",'m');

					file1.open("member.txt",ios::out);
					file2.open("membertemp.txt",ios::in);

				while(file2.read((char*)this,sizeof(mb)))
				{
				file1.write((char*)this,sizeof(mb));
				}

				file1.close();
				file2.close();
				mainMenu('\r');
				showMember();
			}
			else
			{
				mainMenu('\r');
				showMember();
			}
	}

	 mainMenu('\r');
	 showMember();

}//END OF DELETE MEMBER

//TO MODIFY MEMBER//
void Member::modifyMember()
{
	int  input_id,i,j;
	int  flag=0,remodify=0;
	char ch;
	char cow[5]={'C','O','W'};
	char buff[5]={'B','U','F','F'};
	char tempname[25];
	clearForm();

		textcolor(BLUE);
		box(21,7,79,24," UPDATE MEMBER ");
		gotoxy(37,22);
		cout<<"Press Enter to Continue.....";

		box(23,9,77,13,"");
	    gotoxy(42,11);	cout<<"Enter ID: ";

		scanf("%d",&input_id);

		fstream file1,file2;

		file1.open("member.txt",ios::in);
		file2.open("tempmember.txt",ios::out);

		while(file1.read((char*)this,sizeof(mb)))
		{
			if(input_id==id)
			{
			    Name:
				clearForm();
				flag=1;
				textcolor(BLUE);
				gotoxy(24,9);	cprintf("ID    NAME        ADDRESS        TYPE        PHONE");
				gotoxy(24,10);	cout<<"-------------------------------------------------------";
				gotoxy(24,11);	cout<<id;
				gotoxy(30,11);	cout<<name;
				gotoxy(42,11);	cout<<address;
				gotoxy(57,11);	cout<<type;
				gotoxy(69,11);	cout<<phone;
				if(remodify==1)
				{
				goto Remodify;
				}
				
					box(23,14,77,17,"");
					gotoxy(42,15);
					cout<<"Modify This Record ?";
					textbackground(7);textcolor(BLACK); gotoxy(24,16);cprintf("                                                      ");
					gotoxy(46,16);cprintf("YES   NO");
					selCol();gotoxy(46,16);cprintf("Y");gotoxy(52,16);cprintf("N");
					textcolor(WHITE);textbackground(BLACK);

				ch=getch();
				gotoxy(23,14);cprintf("                                                        ");
				gotoxy(23,15);cprintf("                                                        ");
				gotoxy(23,16);cprintf("                                                        ");
				gotoxy(23,17);cprintf("                                                        ");
			     

				 if(ch=='y')
				 {
				 Remodify:
				 menuCol();  gotoxy(40,23); 	cout<<"Press [Ctlr+x] for Exit ";
				 selCol(); gotoxy(46,23);cprintf("[Ctrl+x]");

				   gotoxy(30,14);
				   textcolor(WHITE);

				   cout<<"Enter the member's modification details..";

				   while(1)
				   {
					box(23,15,77,22,"");

					gotoxy(26,16);
					cout<<"NAME       : ";
							textbackground(GREEN+BLUE);
							cprintf(name);
							i=strlen(name);

						do
							{
							name[i]=getch();
								if(name[i]==24)

								goto Exit;
								if(name[i]=='\r')
								{
									break;
								}
								else if(name[i]=='\b' && i>0)
								{
									cprintf("%c%c%c",8,32,8);
									i--;
								}
								else if(name[i]>=65 && name[i]<=122)
								{
								cprintf("%c",name[i]);
								i++;
								}

						}while(name[i]!='\r');
						name[i]='\0';
						if(strlen(name)==0)
					{
					remodify=1;
					msgBox("NAME CANN'T BE  LEFT BLANK",'a');
					goto Name;

					}
						gotoxy(26,17);  cout<<"ADDRESS    : ";
						cprintf(address);
					    i=strlen(address);

						do
						{
							address[i]=getch();
							if(address[i]==24)
								goto Exit;
							if(address[i]=='\b' && i>0)
							{
								cprintf("%c%c%c",8,32,8);
								i--;
							}
							else if(address[i]=='\r')
							{
								break;
							}
							else if(address[i]>=65 && address[i]<=122)
							{
								cprintf("%c",address[i]);
								i++;
							}
					}while(address[i]!='\r');
					address[i]='\0';
					if(strlen(address)==0)
					{
					remodify=1;
					msgBox("ADDRESS CANN'T BE LEFT BLANK",'a');
					goto Name;
					}

					gotoxy(26,18);	cout<<"TYPE [C/B] : ";
					cprintf(type);
					i=strlen(type);

					while(1)
					{
					char ch=getch();
						if(ch==24)
								goto Exit;
					    if(ch=='\r')
						break;
					    else if(ch=='c')
						{

						gotoxy(36,18);cout<<"    " ;
					    gotoxy(36,18);	cout<<"COW";
						strcpy(type,cow);
						break;
						}
						else if(ch=='b')
						{
						gotoxy(36,18); cout<<"    ";
						 gotoxy(36,18); cout<<"BUFF";
						 strcpy(type,buff);
						 break;
						}
					}

					gotoxy(26,19);
					cout<<"PHONE      : ";
					cprintf(phone);
					i=strlen(phone);
						do
						{
						phone[i]=getch();
						if(phone[i]==24)
						goto Exit;

						if(phone[i]=='\b' && i>0)
						{
						cprintf("%c%c%c",8,32,8);
						i--;
						}
						else if(i==10)
							break;
						else if(phone[i]>=48 && phone[i]<=57)
						{
							cprintf("%c",phone[i]);
							i++;
						}

					}while(i!=10);
					phone[i]='\0';

					break;

				   }
				}
			}
		    file2.write((char*)this,sizeof(mb));
		}
		file1.close();
		file2.close();
		
		if(ch=='n')
		{
			mainMenu('\r');
			showMember();
		}

		if(flag==0)
		 msgBox("     NO RECORD FOUND     ",'a'); 
		 
		else
		{
	    menuCol();gotoxy(44,23); cprintf("SAVE    CANCLE");
	    selCol();gotoxy(44,23); cprintf("S");gotoxy(52,23);cprintf("C");

			ch=getch();
		    switch(ch)
			{
			case 's':
				   gotoxy(34,21);
				   msgBox("   RECORD MODIFIED",'m');
				file1.open("member.txt",ios::out);
				file2.open("tempmember.txt",ios::in);
				
				while(file2.read((char*)this,sizeof(mb)))
				file1.write((char*)this,sizeof(mb));

				file1.close();
				file2.close();
				mainMenu('\r');

			case 'c':
				Exit:
				mainMenu('\r');
			}
		}

		system("cls");
		mainMenu('\r');
} //End OF Modify


//SHOW PAYMENT DETAIL//
void Member::showPayment()
{
	clearForm();
	float temp_milk=0,temp_rs=0;
	int count;
	
	box(21,7,79,24," PAYMENT ");
	textcolor(BLUE);
	gotoxy(30,8);cprintf("ID   NAME     TOTAL MILK    TOTAL RS.");
	gotoxy(30,9);cout<<"--------------------------------------";
	
	menuCol();
	gotoxy(22,23);cprintf("         PAYMENT  BACK               MORE                 ");
	selCol();
	gotoxy(31,23);cprintf("P");gotoxy(40,23);cprintf("B");gotoxy(59,23);cprintf("M");
	
	
			fstream file;
			count=10;

			file.open("member.txt",ios::in);

			while(file.read((char*)this,sizeof(mb)))
			{
					if(count==20)
						break;
				 
				Cont:

				gotoxy(30,count); 	cout<<id;
				
				gotoxy(35,count);	cout<<name;
				 
				gotoxy(44,count);	cout<<tot_milk;

				temp_milk+=tot_milk;
				
				gotoxy(58,count);	cout<<tot_rs;
				
				temp_rs+=tot_rs;
				count++;
			}
			
		    gotoxy(30,20);cout<<"______________________________________";
		    gotoxy(30,21);cout<<"total : 	   "<<temp_milk<<"	         "<<temp_rs;
		    
		    file.close();

			switch(getch())
			{
				case 'p':
					payment();
					break;
				case 'm':
					if(count>=20)
					{
						clearForm();

					   textcolor(BLUE);
					   gotoxy(30,9);cprintf("ID   NAME     TOTAL MILK     TOTAL RS.");
					   gotoxy(30,10);cprintf("--------------------------------------");
						
						menuCol(); 	gotoxy(22,23);	cprintf("         PAYMENT  BACK               MORE                 ");
						selCol();	gotoxy(31,23);	cprintf("P");gotoxy(40,23);cprintf("B");gotoxy(59,23);cprintf("M");

					count=11;
					goto Cont;
					}
					else
					{
						 msgBox("NO MORE DATA EXIST!",'a');
					}
					break;

				case 'b':
				case '\b':
					 mainMenu(NULL);
					break;
			}
    showPayment();
}

//FOR DISPALY PAYMENT REPORT IN NOTEPAD //
void Member::payment()
{
	  char *day,*mon,*div="-";
	  char *temp_date;
	  float temp_milk=0,temp_rs=0;
	  char *command="call notepad ";

	  struct date d;
	  
	  getdate(&d);

	  box(21,7,79,24," PAYMENT REPORT ");
	  clearForm();
	 
	 ofstream fw;

	 day=getDay(d.da_day);
	 mon=getMon(d.da_mon);
	 pay_date=NULL;

	 
	  strcpy(pay_date,"PAYMENT\\");//CREATE PATH
	  strcat(pay_date,day);
	  strcat(pay_date,div);
	  strcat(pay_date,mon);
	  strcat(pay_date,".txt");//CREATE DATEWISE REPORT

	  fw.open(pay_date,ios::app);

	temp_date=searchFile();

	
	
	fstream file1,file2,file3;
	file1.open("member.txt",ios::in);

	   box(23,14,77,19,"");
					textbackground(7);textcolor(BLACK); gotoxy(24,18);cprintf("                                                      ");
					gotoxy(38,18);cprintf("Press Any Key To Continue..");
					textcolor(WHITE);textbackground(BLACK);

	  gotoxy(30,15);	cout<<"1. After open notepad press Ctrl+P for print"<<endl;
	  gotoxy(30,16);	cout<<"2. Must Close notepad after print or view "<<endl;
	  getch();

	  gotoxy(40,8); fw<<"	                  Payment Report COW BUFF "<<endl;
	  gotoxy(35,9); fw<<"     	     "<<temp_date<<"-"<<d.da_year<<"  MOR to "<<getDay(d.da_day)<<"-"<<getMon(d.da_mon)	<<"-"<<d.da_year<<" EVE"<<endl;
	  gotoxy(23,10);fw<<"---------------------------------------------------------------------------------------------------------------"<<endl;

	 gotoxy(30,11);fw<<" ID\tNAME\t\tTOTAL MILK\tTOTAL RS.\t\tSIGN "<<endl;
	 gotoxy(30,12);fw<<"----------------------------------------------------------------------------------------------------------------"<<endl;

	  while(file1.read((char*)this,sizeof(mb)))
		{
				fw<<"   "<<id;
				fw<<"\t"<<name;
				fw<<"\t\t"<<tot_milk;

					temp_milk+=tot_milk;

				fw<<"\t        	         "<<tot_rs;

					temp_rs+=tot_rs;

				fw<<endl<<"______________________________________________________________________"<<endl;
	    }

		cout<<"______________________________________";
	    fw<<"total : \t\t\t"<<temp_milk<<"\t\t"<<temp_rs;
	    file1.close();
		fw.close();

		strcat(command,pay_date);
		system(command);

		file1.open("member.txt",ios::in);
		file2.open("tempmember.txt",ios::out);

		while(file1.read((char *)this,sizeof(mb)))
		{
			tot_milk=0;
			tot_rs=0;
			file2.write((char *)this,sizeof(mb));
		}

	  file2.close();
	  file1.close();

	  msgBox("  Payment Successfully  ",'m');

	 file1.open("member.txt",ios::out);
	 file2.open("tempmember.txt",ios::in);
	
	while(file2.read((char*)this,sizeof(mb)))
		file1.write((char*)this,sizeof(mb));

	  file2.close();
	  file1.close();
	  system("cls");
	  mainMenu('\r');

}

//FOR SEARCH FILE//
char *searchFile()
{
	  int i_day,i_mon;
	  char *day,*mon,*div="-";
	  char *temp_date;
	
	struct date d;
	  getdate(&d);

	  i_day=d.da_day;
	  i_mon=d.da_mon;
	  fstream file;

	  Search:
			if(i_day==1)
			{
				i_day=31;
					if(i_mon==1)
						i_mon=12;
					else
						i_mon--;
			}
			else
				i_day--;

	  day=getDay(i_day);
	  mon=getMon(i_mon);
	  
	  strcpy(temp_date,"PAYMENT\\");
	  strcat(temp_date,day);
	  strcat(temp_date,div);
	  strcat(temp_date,mon);
	  strcat(temp_date,".txt");

	  file.open(temp_date,ios::app | ios::nocreate) ;
	  if(file.fail())
		goto Search;
	  else
	  {
		if(i_day==31)
		{
			i_day=1;
				if(i_mon==12)
					i_mon=1;
				else
					i_mon++;
		}
		else
			i_day++;
	  
	  day=getDay(i_day);
	  mon=getMon(i_mon);

	  strcpy(temp_date,day);
	  strcat(temp_date,div);
	  strcat(temp_date,mon);
	    return temp_date;
	  }
}

// FOR GET FAT VALUES //
float Fat:: getRs(float inpval)
{
	float value=0;
	fstream file;
	file.open("fatdata.txt", ios::in);
	
	while( file.read((char*)this,sizeof(ft)))
	{
		if(inpval==fat)
		{
			value=fvalue;
			break;
		}
	}
    file.close();
    gotoxy(33,23);
    return value;
}

// FOR COLLECT MILK //
void Milk::collectMilk()
{
	char ch;
	int flag=0,cnt=0;
	char temp_value[4];
	char sesm[4]="MOR",sese[4]="EVE";
	char *day,*mon,*div="-";


	box(21,7,79,24," COLLECT MILK ");
	clearForm();
	
	struct date d;
	struct time t;
	gettime(&t);
	getdate(&d);

	gotoxy(30,22);	cout<<"Press Enter to Continue after entring ID";

	if(AddData==0)
	{
		box(23,9,77,13,"");
		gotoxy(42,11);	cout<<"Enter ID: ";
		scanf("%d",&input_id);

		gotoxy(38,12);	cout<<"                   ";
		AddData=1;
	}
	 
	 clearForm();
	 fstream file1;
	 fstream file2;
	 fstream file3;


	  file1.open("member.txt", ios::beg | ios::in );
	  file2.open("paytemp.txt",ios::out);

	 while(file1.read((char*)this,sizeof(mb)))
	{
		if(input_id==id)
		{
			 menuCol();  gotoxy(40,23); 	cout<<"Press [Ctlr+x] for Exit ";
			 selCol(); gotoxy(46,23);		cprintf("[Ctrl+x]");

				textbackground(BLACK);
				textcolor(WHITE);
				day= getDay(d.da_day);
				mon= getMon(d.da_mon);

				  strcpy(date,day);
				  strcat(date,div);
				  strcat(date,mon);

				 if(t.ti_hour<=12)
					strcpy(ses,sesm);
				 else
					strcpy(ses,sese);
					
			gotoxy(65,8);	cprintf("%s-%d",date,d.da_year);
			
			box(58,12,79,21,"");
			
			 gotoxy(65,9);	cout<<"SESSION: "<<ses;
			 gotoxy(25,10);	cout<<"ID              : "<<id;
			 gotoxy(25,12);	cout<<"NAME           : "<<name;
			 gotoxy(60,14);	cout<<"TYPE       : "<<type;
		   
		   strcpy(cname,name);
		   strcpy(ctype,type);
			
			gotoxy(60,16); 	cout<<"Total Milk : "<<tot_milk;
			gotoxy(60,18);	cout<<"Total Rs.  : "<<tot_rs;
			
			gotoxy(25,15);  cout<<"Enter Milk (Ltr) : ";
			do
			{
				temp_value[cnt]=getch();
				
				if(temp_value[cnt]==24)
				{
					 invalid=1;
					 file1.close();
					 file2.close();
					 file3.close();
					 mainMenu(NULL);
				}
				if( cnt==5 || temp_value[cnt]=='\r')
					break;
			
				else if(temp_value[cnt]=='\b' && cnt>0)
				{
				cprintf("%c%c%c",8,32,8);
				cnt--;
				}
				else if((temp_value[cnt]>=48 && temp_value[cnt]<=57) || temp_value[cnt]=='.')
				{
				cprintf("%c",temp_value[cnt]);
				cnt++;
				}
			}while(cnt<5);
			
			temp_value[cnt]='\0';
			input_milk=atof(temp_value);
	    
			if(input_milk<1 || input_milk>15)
			{
				AddData=1;
				msgBox("Enter 1 to 15 Ltr Milk",'a');
				collectMilk();
			}
			else
				AddData=0; 	
			
			cnt=0;
			temp_value[4]=NULL;
			
			gotoxy(25,17);	cout <<"Enter Fet        : ";
			do
			{
				temp_value[cnt]=getch();
				if(temp_value[cnt]==24)
				{
					invalid=1;
					file1.close();
					file2.close();
					file3.close();
					mainMenu(NULL);
				}
				if(cnt==5 || temp_value[cnt]=='\r')
					break;
				else if(temp_value[cnt]=='\b' && cnt>0)
				{
					cprintf("%c%c%c",8,32,8);
					cnt--;
				}
				else if((temp_value[cnt]>=48 && temp_value[cnt]<=57) || temp_value[cnt]=='.')
				{
				cprintf("%c",temp_value[cnt]);
				cnt++;
				}
			}while(cnt<5);
		
			temp_value[cnt]='\0';
			input_fet=atof(temp_value);
	  
			temp_value[4]=NULL;

		   if(input_fet<4 || input_fet>10.2)
			{
			 msgBox("Enter FAT 4 to 10.2 ",'a');
			 AddData=1;
			 collectMilk();
			}
			else
				AddData=0; 

			tot_milk+=input_milk;
			tot_amt= ft.getRs(input_fet);
			tot_amt=input_milk*tot_amt;

			gotoxy(30,20); cout<<"Total Amount: "<<tot_amt;
			
			menuCol();gotoxy(44,23); cprintf("SAVE    CANCLE");
			selCol();gotoxy(44,23); cprintf("S");gotoxy(52,23);cprintf("C");

			invalid=2;//for Exit The Collect Menu

			switch (getch())
			{
				 case 's':
				 case '\r':
					file3.open("SESSION.txt",ios::app | ios::out);
					if(file3.fail())
						msgBox("OPEN FAIL",'a');

					file3.write((char*)this,sizeof(ml));
					file3.close();
					tot_rs+=tot_amt;
					gotoxy(30,22);
					msgBox("  INSERTED SUCCESSFULLY",'m');

					file2.write((char*)this,sizeof(mb));
					break;

				case 'c':
			    case '\b':
						flag=1;
						file3.close();
						break;
		    }

		}
		else
		{
		file2.write((char*)this,sizeof(mb));
		}

	}
	
	file1.close();
	file2.close();
	  
	if(flag==0)
    {
	  file1.open("member.txt",ios::out);
	  file2.open("paytemp.txt",ios::in);
	  while(file2.read((char*)this,sizeof(mb)))
		file1.write((char*)this,sizeof(mb));

	  file1.close();
	  file2.close();
	}
	if(invalid==0)
	{
	  AddData=0;
	  msgBox("       Invalid ID       ",'a');
	  system("cls");
	  mainMenu(NULL);
    }
	else if(flag==1)
	{
	    system("cls");
	    mainMenu(NULL);
	}
	else if(invalid==1)
	{
		AddData=0;
		invalid=0;
		collectMilk();
	}
	  
	kn.addKen();
	system("cls");
	mainMenu(NULL);
}

// FOR SESSION SUMMARY //
void Milk::showSession()
{

	int count;
	char tempdate[15];
	char tempses[4];
	char sesm[4]="MOR",sese[4]="EVE";
	char *day,*mon,*div="-";
	
	fstream file1;

	struct date d;
	struct time t;
		getdate(&d);
		gettime(&t);
		  day= getDay(d.da_day);
		  mon= getMon(d.da_mon);

	  strcpy(tempdate,day);
	  strcat(tempdate,div);
	  strcat(tempdate,mon);

		 if(t.ti_hour<=12)
			strcpy(tempses,sesm);
		 else
			strcpy(tempses,sese);

	clearForm();
	box(21,7,79,24," SESSION REPORT ");
	
	file1.open("SESSION.txt",ios::in);
		   
		textcolor(BLUE);   gotoxy(30,10);cprintf("ID   NAME     MILK    FET    Rs/LTR   TYPE");
							gotoxy(30,11);cout<<"--------------------------------------------";
		
						menuCol();gotoxy(40,23); cprintf("SEARCH    BACK            MORE");
						selCol();gotoxy(40,23); cprintf("S");gotoxy(50,23);cprintf("B");gotoxy(66,23);cprintf("M");

	count=12;
	while(file1.read((char*)this,sizeof(ml)))
	{
		Cont:
		if((strcmp(date,tempdate)==0) && (strcmp(ses,tempses)==0))
		{
			gotoxy(48,9);cout<<date<<" "<<ses;
			gotoxy(30,count);cout<<input_id;
			gotoxy(35,count);cout<<cname;
			gotoxy(44,count);cout<<input_milk;
			gotoxy(52,count);cout<<input_fet;
			gotoxy(60,count);cout<<tot_amt;
			gotoxy(69,count);cout<<type;

			count++;
		}
		if(count==21)
		{
			 break;
		}
	 }

    while(1)
	{
			switch(getch())
			{
				case 's':
					file1.close();
					search();
					break;
				case 'm':
					if(count>=21)
					{
					   clearForm();
					   textcolor(BLUE);
					   gotoxy(30,10);	cprintf("ID   NAME     MILK    FET    Rs/LTR   TYPE");
					   gotoxy(30,11);	cout<<"--------------------------------------------";

						menuCol();gotoxy(40,23); 	cprintf("SEARCH    BACK            MORE");
						selCol();gotoxy(40,23); 	cprintf("S");gotoxy(50,23);cprintf("B");gotoxy(66,23);cprintf("M");

					count=12;
					goto Cont;
					}
					else
					{
						msgBox("  NO MORE DATA EXIST!  ",'a');
					}
				break;

				case 'b':
				case '\b':
					   file1.flush();
					   file1.close();
					   system("cls");
					   mainMenu(NULL);
					   break;
			}
	}

}

// FOR SERCH SESSION SUMMARY //
void Milk:: search()
{
	int count;
	int flag=0;
	char tempses[4];
	char sesm[4]="MOR",sese[4]="EVE";

	fstream file;

	char ch;
	char tempdate[6];
		
		clearForm();
		 menuCol();  gotoxy(40,23); cout<<"Press [Ctlr+x] for Exit ";
		 selCol(); gotoxy(46,23);	cprintf("[Ctrl+x]");
		 
	box(21,7,79,24," SESSION REPORT ");
	
	textcolor(BLUE);
	textbackground(BLACK);
	gotoxy(35,13);	cprintf("[Ex. 25-MAR]");
	
	  
	gotoxy(35,12);	cout<<"Enter Date(DD-MON) : ";
	int i=0;
	
	do
	{
		tempdate[i]=getch();
		
		if(i==6)
			break;

		if(tempdate[i]==24)
			mainMenu('\r');

		if(tempdate[i]=='\b' && i>0)
		{  
			textcolor(WHITE);
			cprintf("%c%c%c",8,32,8);
			i--;
		}
		else if(i<=1)
		{
		    if(i==0)
		    {
				 if(tempdate[i]>=48 && tempdate[i]<=51)
				 {
					cout<<tempdate[i];
					i++;
				 }
		    }
		    else if(tempdate[0]=='3')
		    {
				if(tempdate[i]>=48 && tempdate[i]<=49)
				{
					cout<<tempdate[i];
					i++;
				 }
				
				if(i==2)
				{
					tempdate[i]='-';
					cout<<"-";
					i++;
			    }
		    }
		    else if(tempdate[i]>=48 && tempdate[i]<=57)
			{
				cout<<tempdate[i];
				i++;
				if(i==2)
				{
					tempdate[i]='-';
					cout<<"-";
					i++;
			    }
			}

		}
	    else if(i>2)
		{
		    if(tempdate[i]>=65 && tempdate[i]<=122)
		    {
				tempdate[i]=toupper(tempdate[i]);
				textcolor(WHITE); cprintf("%c",tempdate[i]);
				i++;
		    }
		}
	}while(i!=6);

	tempdate[i]='\0';

	  gotoxy(35,15); cprintf("([M]or/[E]ve)");
	  gotoxy(35,14); cout<<"Enter Session      : ";

	gotoxy(56,14);
	while(1)
	{
		ch=getch();
		if(ch==24)
		{
			system("cls");
			mainMenu('\r');
		}
		if(ch=='m')
		{
			cout<<"MOR";
			strcpy(tempses,sesm);
			break;
		}
		else if(ch=='e')
		{
			cout<<"EVE";
			strcpy(tempses,sese);
			break;
		}
	}


		menuCol(); gotoxy(35,23); cout<<"Press Any Key To Continue.. ";
	getch();

	clearForm();
	file.open("session.txt",ios::in);
	    textcolor(BLUE);
		   gotoxy(30,10);cprintf("ID   NAME     MILK    FET    Rs/LTR   TYPE");
		   gotoxy(30,11);cout<<"--------------------------------------------";
		
			menuCol();gotoxy(40,23); cprintf("SEARCH    BACK            MORE");
			selCol();gotoxy(40,23); cprintf("S");gotoxy(50,23);cprintf("B");gotoxy(66,23);cprintf("M");

	count=12;
	while(file.read((char*)this,sizeof(ml)))
	{
		Cont:
		if(strcmp(date,tempdate)==0 && strcmp(ses,tempses)==0)
		{
			flag=1;
			gotoxy(48,9);cout<<date<<" "<<ses;
			gotoxy(30,count);cout<<input_id;
			gotoxy(35,count);cout<<cname;
			gotoxy(44,count);cout<<input_milk;
			gotoxy(52,count);cout<<input_fet;
			gotoxy(60,count);cout<<tot_amt;
			gotoxy(69,count);cout<<type;

			count++;
		 }
		if(count==22)
			 break;
	}
    
	file.close();
    if(flag==0)
    {
		msgBox("    NO DATA FOUND   ",'a');
		mainMenu('\r');
    }
	while(1)
	{
		switch(getch())
		{
		case 's':
			search();
			break;
		case 'm':
			if(count>=22)
			{
			   clearForm();
			   textcolor(BLUE);
			   gotoxy(30,10);cprintf("ID   NAME     MILK    FET    Rs/LTR   TYPE");
			   gotoxy(30,11);cout<<"--------------------------------------------";
				menuCol();gotoxy(40,23); cprintf("SEARCH    BACK            MORE");
				selCol();gotoxy(40,23); cprintf("S");gotoxy(50,23);cprintf("B");gotoxy(66,23);cprintf("M");

			count=12;
			goto Cont;
			}
			else
			{
				msgBox("  NO MORE DATA EXIST!  ",'a');
			}
			break;

		case 'b':
		case '\b':
			  system("cls");
			  mainMenu(NULL);
			 break;
		}
	}
}

// FOR DISPLAY FET VALUES //
void Fat::showFat()
{
	int row,col;
	box(21,7,79,24," FET ");
	fstream file;
	file.open("fatdata.txt", ios::in | ios::app | ios::out);

	  clearForm();
		   textcolor(BLUE);
		   gotoxy(23,9);cprintf("FET   VALUE    FET   VALUE    FET   VALUE    FET   VALUE");
		   gotoxy(23,10);cout<<"---------------------------------------------------------";
	    menuCol();gotoxy(22,23);		cprintf("                      UPDATE  BACK           MORE         ");
		selCol();	/*gotoxy(31,23);     cprintf("A");gotoxy(36,23);cprintf("D");*/ gotoxy(44,23);cprintf("U");gotoxy(52,23);cprintf("B");gotoxy(67,23);cprintf("M");

    Cont:
	row=11;
	col=23;
	
	while( file.read((char*)this,sizeof(ft)))
	{
		if(row==21)
		{
		   row=11;
		   col+=15;
		}
		
		gotoxy(col,row);cout<<fat;
		gotoxy(col+6,row);cout<<fvalue;
		row++;
		
		if(col==68 && row==21)
		{
		  break;
		}

	}
    file.close();
 
	while(1)
	{
	   switch(getch())
		{
			case 'u':
				updateFvalue();
				break;
			case 'm':
				if(col==68 && row==21)
				{
				   clearForm();
				  
					textcolor(BLUE);
				   gotoxy(23,9);cprintf("FET   VALUE    FET   VALUE    FET   VALUE    FET   VALUE");
				   gotoxy(23,10);cout<<"---------------------------------------------------------";
					
					menuCol();gotoxy(22,23);		cprintf("                      UPDATE  BACK           MORE         ");
					selCol(); gotoxy(44,23);cprintf("U");gotoxy(52,23);cprintf("B");gotoxy(67,23);cprintf("M");


				goto Cont;
				}
				else
				{
					gotoxy(30,22);
					msgBox("  NO MORE DATA EXIST!   ",'a');
					system("cls");
					mainMenu('\r');
				}
			case 'b':
			case '\b':
				system("cls");
				mainMenu(NULL);
				break;
		}
    }
}

// FOR UPDATE FET VALUES //
void Fat::updateFvalue()
{
	 int reenter=0;
	 float input_fat;
	 int flag=0,i;
	 char ch;
	 char *temp_value[6];
	 
	clearForm();
	box(21,7,79,24," UPDATE FET VALUE ");
	
	gotoxy(37,22);	cout<<"Press Enter to Continue.....";
		
		textcolor(BLUE);
		box(23,9,77,13,"");
		
	gotoxy(42,11);	cout<<"Enter FET : ";
					scanf("%f",&input_fat);
	
	gotoxy(37,22);	cout<<"                             ";
		
			Reenter:
			clearForm();

		fstream file1,file2;


		file1.open("fatdata.txt",ios::in);
		file2.open("tempfatdata.txt",ios::out);

		while(file1.read((char*)this,sizeof(ft)))
		{
			if(input_fat==fat)
			{
				flag=1;
				gotoxy(24,9);textcolor(BLUE);cprintf("FAT    FAT VALUE  ");
			    gotoxy(24,10);cout<<"------------------";
			    gotoxy(24,11);cout<<fat;
			    gotoxy(30,11);cout<<fvalue;
			
				if(reenter==1)
				{
					goto Entry;
				}
				
				box(23,14,77,17,"");
				gotoxy(42,15);
				cout<<"Modify This Record ?";
				   textbackground(7);textcolor(BLACK); gotoxy(24,16);cprintf("                                                      ");
				gotoxy(46,16);cprintf("YES   NO");
				selCol();gotoxy(46,16);cprintf("Y");gotoxy(52,16);cprintf("N");
				textcolor(WHITE);textbackground(BLACK);

				ch=getch();
				gotoxy(23,14);cprintf("                                                        ");
				gotoxy(23,15);cprintf("                                                        ");
				gotoxy(23,16);cprintf("                                                        ");
				gotoxy(23,17);cprintf("                                                        ");


				if(ch=='y')
				{
					Entry:
				 
				   textcolor(WHITE);
				    gotoxy(35,14);	 cout<<"Enter the NEW value of FAT.. ";
					box(22,15,78,24,"");
					
					gotoxy(37,18);	cout<<"FAT VALUE    : ";
									cin>>fvalue;
					
					if(fvalue<15 && fvalue<=70)
					{ 
						reenter=1;
						msgBox("Enter Valid Value",'a');
					   goto Reenter;
					}
				}

			}
		file2.write((char*)this,sizeof(ft));
		}
		file2.close();
		file1.close();

		if(ch=='n')
		{
			mainMenu('\r');
			showFat();
		}

		if(flag==0)
		{
			msgBox("     NO RECORD FOUND     ",'a');
		}
		else
		{
			menuCol();gotoxy(44,23); cprintf("SAVE    CANCLE");
			selCol();gotoxy(44,23); cprintf("S");gotoxy(52,23);cprintf("C");
			
			while(1)
			{
			  ch=getch();
			  switch(ch)
				{
					case 's':

						msgBox("   RECORD MODIFIED",'m');

						file1.open("fatdata.txt",ios::out);
						file2.open("tempfatdata.txt",ios::in);
						while(file2.read((char*)this,sizeof(ft)))
						file1.write((char*)this,sizeof(ft));

						file1.close();
						file2.close();
						mainMenu('\r');
						break;

					case 'c':
						mainMenu('\r');
						break;
				}
			}	
}
}

//FOR ADD KEN DETAIL//
void Ken::addKen()
{
	struct date d;
	struct time t;
	char ch;
    char tempses[4],tempdate[15];
	char sesm[4]="MOR",sese[4]="EVE";

	float temp_cfet=0,temp_ffet=0;
	float temp_cwgt=0,temp_fwgt=0;
	int ccount=0,fcount=0;
	int flag=0;

	fstream file1,file2,file3;
	
	file1.open("ken.txt",ios::in);
	file2.open("SESSION.txt",ios::in);
	file3.open("tempken.txt",ios::out);

	getdate(&d);
	gettime(&t);

	  char *day,*mon,*div="-";
	  day= getDay(d.da_day);
	  mon= getMon(d.da_mon);

	  strcpy(tempdate,day);
	  strcat(tempdate,div);
	  strcat(tempdate,mon);

	  if(t.ti_hour<=12)
	    strcpy(tempses,sesm);
	  else
	    strcpy(tempses,sese);

	    clearForm();

	while(file2.read((char*)this,sizeof(ml)) )
	{
		if((strcmp(date,tempdate)==0) && (strcmp(ses,tempses)==0))
		{
		    if(input_fet<=5)
		    {
		      temp_cwgt+=input_milk;
		      temp_cfet+=input_fet;
		      ccount++;
		    }
		    else
		    {
			temp_fwgt+=input_milk;
			temp_ffet+=input_fet;
			fcount++;
		    }
		} //end If

	} //end while


	file2.close();
	if(file1.read((char*)this,sizeof(kn))==NULL)
	{
		goto Flag;
	}
	else
	{
		file1.close();
		file1.open("ken.txt",ios::in);
		while(file1.read((char*)this,sizeof(kn)))
		{
					if(strcmp(kdate,tempdate)==0 && strcmp(kses,tempses)==0)
					{
							cweight=temp_cwgt;
							if(cweight==0)
							  cfat=0;
							
							else
								cfat=(temp_cfet/ccount);
							
							cKen=1;
							do
							{
								if(temp_cwgt<30)
									break;
							
								else
									cKen++;
							
								temp_cwgt-=30;
							}while(temp_cwgt>30);

							fweight=temp_fwgt;
							if(fweight==0)
								ffat=0;
							
							else
								ffat=(temp_ffet/fcount);
								
								fKen=1;	
								do
								{
									if(temp_fwgt<30)
										break;
										
									else
									fKen++;
											
									temp_fwgt-=30;
								}while(temp_fwgt>30);

						file3.write((char*)this,sizeof(kn));
						flag=1;
				       break;
					}
					file3.write((char*)this,sizeof(kn));

		}
	}

	file1.close();
	file2.close();
	file3.close();

	Flag:
    	 if(flag==0)
	    {
				file1.open("ken.txt",ios::app);
				strcpy(kdate,tempdate);
				strcpy(kses,tempses);
					cweight=temp_cwgt;
					if(cweight==0)
						cfat=0;
					  
					else
						cfat=(temp_cfet/ccount);
					
					cKen=1;
					
				    do
					{
						if(temp_cwgt<30)
						break;
						
						else
						cKen++;
						
						temp_cwgt-=30;
					}while(temp_cwgt>30);

					fweight=temp_fwgt;
					if(fweight==0)
					ffat=0;
					
					else
					ffat=(temp_ffet/fcount);

					fKen=1;
					do
					{
						if(temp_fwgt<30)
						break;
						
						else
						fKen++;
						
					temp_fwgt-=30;
					}while(temp_fwgt>30);

					file1.write((char*)this,sizeof(kn));
					file1.close();
		}
		else
		{
			file1.open("ken.txt",ios::out);
			file3.open("tempken.txt",ios::in);
			while(file3.read((char*)this,sizeof(kn)))
			{
			file1.write((char*)this,sizeof(kn));
			}

			file1.close();
			file3.close();
        }
		system("cls");
		mainMenu(NULL);
}

//FOR DISPLAY KEN SUMMARY//
void Ken::showKen()
{
	int count;
	fstream file;
	 box(21,7,79,24," KEN ");
	file.open("ken.txt",ios::in);
	 clearForm();
		   gotoxy(35,8);
					    cprintf("[--------COW------]  [--------BUFF------]");
				textcolor(BLUE);
		   gotoxy(23,9);cprintf("DATE   SES    KEN  FET  WEIGHT     KEN  FET  WEIGHT    ");
		   gotoxy(22,10);cout<<"----------------------------------------------------------";
			menuCol();gotoxy(40,23); cprintf("BACK      MORE");
			selCol();gotoxy(40,23); cprintf("B");gotoxy(50,23);cprintf("M");


	  count=11;

	while(file.read((char*)this,sizeof(kn)))
	{
		if(count==19)
		{
			 break;
		}
		Cont:
		cout.precision(1);

		gotoxy(23,count);cout<<kdate;
		gotoxy(30,count);cout<<kses;

		gotoxy(37,count);cout<<cKen;
		gotoxy(42,count);cout<<cfat;
		gotoxy(47,count);cout<<cweight;


		gotoxy(58,count);cout<<fKen;
		gotoxy(63,count);cout<<ffat;
		gotoxy(68,count);cout<<fweight;

		count++;
	}
    file.close();

    switch(getch())
    {
    case 'm':
		if(count==19)
		{
		   clearForm();
		   gotoxy(22,8);
				cprintf("[---------COW--------]  [---------BUFF-------]");
				textcolor(BLUE);
		   gotoxy(23,9);cprintf("KEN FET   WEIGHT  SNF  KEN  FET   WEIGHT  SNF  SES DATE");
		   gotoxy(22,10);cprintf("----------------------------------------------------------");
		   gotoxy(27,23);cprintf("[A]DD  [B]ACK      [M]ORE");

		  count=11;
		goto Cont;
		}
		else
		{
		msgBox("  NO MORE DATA EXIST!  ",'a');
		showKen();
		}
	break;

    case 'b':     cout.precision(3);
		  mainMenu(NULL);
		  break;
    }

}

//TO SET HEADER//
void header()
{
	int i,j;
	textcolor(WHITE);
	textbackground(BLACK);
	box(1,1,79,5,"-");

    textcolor(BLUE);

	for(i=2;i<=4;i++)
	{
		for(j=1;j<=78;j++)
		{
		gotoxy(j+1,i);
		cprintf("%c",176);
		}
	}

	gotoxy(35,3);
	textcolor(WHITE);
	cprintf("SARVOTTAM DAIRY");
	gotoxy(30,25);
	textcolor(8);
	cprintf("Developed By : Vishal Bheda & Kiran Bolaniya");	  
}

//to Display Main Menu//
void mainMenu(char select)
{
 clrscr();
 header();

 Member mb1;
 Milk ml1;

   char ch='0';
   int  choice,no=8;

    while(1)
    {
	switch(ch)
	{
	case 80:
	    count_menu++;
	    if (count_menu==no+1) count_menu=1;
	    break;
	case 72:
	    count_menu--;
	    if(count_menu==0) count_menu=no;
	    break;
	}

	highlight(count_menu);
	if(select=='\r')
	{
	ch=select;
	goto Select;
	}
	ch=getch();
	Select :
	if(ch=='\r')
	{
	choice=count_menu;
	select:
		 switch(choice)
		{
		case 1:
		cout.flush();
			ml1.collectMilk();
			break;
		case 2:
			mb1.showPayment();
			break;
		case 3:
			mb1.showMember();
			break;
		case 4:
			Fat ft1;
			ft1.showFat();
			break;
		case 5:
			ml1.showSession();
			break;
		case 6:
			Ken kn1;
			kn1.showKen();
			break;
		case 7:
			Login lg1;
			lg1.changePass();
			break;
		case 8:
		 exit(0);
		  }
	}

   } 
}

/*to change the poiter and highlight MENU*/
void highlight(int count_menu)
{
int i;
system("cls");
header();
logo();
textcolor(WHITE);

box(1,7,19,24,"MAIN MENU");


	 textcolor(BLUE);
gotoxy(4,9);
cprintf("COLLECT MILK  ");
gotoxy(4,11);
cprintf("PAYMENT       ");
gotoxy(4,13);
cprintf("MEMBER        ");
gotoxy(4,15);
cprintf("FET VALUES    ");
gotoxy(4,17);
cprintf("SESSION REPORT");
gotoxy(4,19);
cprintf("KEN SUMMARY   ");
gotoxy(4,21);
cprintf("CHANGE PASSWORD");
gotoxy(4,23);
cprintf("EXIT          ");

	textcolor(WHITE);

	switch(count_menu)
	{
	case 1:
	    gotoxy (1,9);
	    cprintf("[- COLLECT MILK    ]");
	    break;
	case 2:
	    gotoxy (1,11);
	    cprintf("[- PAYMENT         ]");
	    break;
	case 3:
	    gotoxy (1,13);
	    cprintf("[- MEMBER          ]");
	    break;
	case 4:
	    gotoxy (1,15);
	    cprintf("[- FET VALUES      ]");
	    break;
	case 5:
	    gotoxy (1,17);
	    cprintf("[- SESSION REPORT  ]");
	    break;
	case 6:
	    gotoxy (1,19);
	    cprintf("[- KEN SUMMARY     ]");
	    break;
	case 7:
	    gotoxy (1,21);
	    cprintf("[- CHANGE PASSWORD ]");
	    break;
	case 8:
	    gotoxy(1,23);
	    cprintf("[- EXIT            ]");
		break;
	}
}

//TO DISPLAY MESSAGE//
void msgBox(char msg[20],char type)
{

	int i,j;
	gotoxy(30,14);
	if(type=='a')
	{
	textcolor(WHITE);
	textbackground(RED);
	}
	else
	{
	textcolor(WHITE);
	textbackground(BLUE);
	}
	for(i=15;i<=17;i++)
	{
		for(j=38;j<=66;j++)
		{
		gotoxy(j+1,i);
		cprintf("%c",176);
		}
	}

	gotoxy(40,16);
	cout<<msg;

	box(38,14,67,18,"ออออออออ Message ");
	sleep(2);
	
	return;
}

//FOR DISPLAY MENU HEADER//
void menuCol()
{
	textcolor(BLACK);
	textbackground(7);
	gotoxy(22,23);
	cprintf("                                                          ");
}

//FOR DISPLAY RED CHARACTER//
void selCol()
{
	textcolor(RED);
}

//FOR GET DAY//
char *getDay(int day)
{
  switch(day)
  {
	case (1): return ("01");
	case (2): return ("02");
	case (3): return ("03");
	case (4): return ("04");
	case (5): return ("05");
	case (6): return ("06");
	case (7): return ("07");
	case (8): return ("08");
	case (9): return ("09");
	case (10): return ("10");
	case (11): return ("11");
	case (12): return ("12");
	case (13): return ("13");
	case (14): return ("14");
	case (15): return ("15");
	case (16): return ("16");
	case (17): return ("17");
	case (18): return ("18");
	case (19): return ("19");
	case (20): return ("20");
	case (21): return ("21");
	case (22): return ("22");
	case (23): return ("23");
	case (24): return ("24");
	case (25): return ("25");
	case (26): return ("26");
	case (27): return ("27");
	case (28): return ("28");
	case (29): return ("29");
	case (30): return ("30");
	case (31): return ("31");
  }
return NULL;
}

//FOR GET MONTH//
char *getMon(int mon)
{
  switch(mon)
  {
	case (1): return ("JAN");
	case (2): return ("FEB");
	case (3): return ("MAR");
	case (4): return ("APR");
	case (5): return ("MAY");
	case (6): return ("JUN");
	case (7): return ("JUL");
	case (8): return ("AUG");
	case (9): return ("SEP");
	case (10): return ("OCT");
	case (11): return ("NOV");
	case (12): return ("DEC");
  }
return NULL;
}

//FOR DISPALY LOGO//
void logo()
{
	box(21,7,79,24,"");
	textcolor(BLACK);
	textbackground(7);
	gotoxy(42,12);	cprintf("                   ");
	gotoxy(42,13);	cprintf("  %c%c%c%c%c%c%c %c%c%c%c%c%c%c  ",178,178,178,178,178,178,178,178,178,178,178,178,178,178);
	gotoxy(42,14);	cprintf("  %c%c        %c%c %c%c  ",178,178,178,178,178,178);
	gotoxy(42,15);	cprintf("  %c%c%c%c%c%c%c   %c%c %c%c  ",178,178,178,178,178,178,178,178,178,178,178);
	gotoxy(42,16);	cprintf("       %c%c   %c%c %c%c  ",178,178,178,178,178,178);
	gotoxy(42,17);	cprintf("  %c%c%c%c%c%c%c %c%c%c%c%c%c%c  ",178,178,178,178,178,178,178,178,178,178,178,178,178,178);

	gotoxy(42,18);	cprintf("  SARVOTTAM DAIRY  ");printf("\n");
	gotoxy(42,19);	cprintf("                   ");

	textbackground(BLACK);
}

//FOR CREATE BOX//
void box(int x, int y, int x1, int y1, char str[25])
{
int i;
//int x=25,y=12,x1=50,y1=16;
//	textbackground(BLACK);

	gotoxy(x,y);
	  //	cout<<"%c",218);//print Right upper Corner
	cout<<"ษ";
	for(i=x+1;i<=x1;i++)
	{
	gotoxy(i,y);
      //	cprintf("%c",196); //print upper Line
	 cout<<"อ";
	}

	  gotoxy(x1+1,y);
     //  cprintf("%c",191);//print Left Upper Corner
	 cout<<"ป";

	for(i=y+1;i<y1;i++)
	{
	gotoxy(x,i);
       //	cprintf("%c",179);//print right side line
       cout<<"บ";
	}

	for(i=y+1;i<y1;i++)
	{
	gotoxy(x1+1,i);
	//	cprintf("%c",179);//print left side line
     cout<<"บ";
	}

	gotoxy(x,y1);
       //	cprintf("%c",192);//print bottm right corner
	  cout<<"ศ";


	for(i=x+1;i<=x1;i++)
	{
	gotoxy(i,y1);
      //	cprintf("%c",196);//print bottom line
      cout<<"อ";
	}

	gotoxy(x1+1,y1);
      //	cprintf("%c",217);//print bottom left corner*/
       cout<<"ผ";
	gotoxy(x+2,y);

	cout<<str;
}

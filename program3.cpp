#include<iostream>
#include<iomanip>
#include<stdio.h>
#include<windows.h>
using namespace std;
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<fstream>
class book
{
	char bno[6];
	char bname[50];
	char aname[30];
	HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
	public:
	void createbook()
	{
		SetConsoleTextAttribute(h,2);
		cout<<"\nNEW BOOK ENTRY......\n";
		SetConsoleTextAttribute(h,12);
		cout<<"\nEnter The Book No: ";
		cin.ignore();
		cin>>bno;
		cin.ignore();
		cout<<"Enter The Book Name: ";
		gets(bname);
		//cin.ignore();
		cout<<"Enter The Author Name: ";
		gets(aname);
		SetConsoleTextAttribute(h,6);
		cout<<"\n\nBook Created.....";
	}
	void showbook()
	{
		SetConsoleTextAttribute(h,11);
		cout<<"\nBook Number:"<<bno;
		SetConsoleTextAttribute(h,15);
		cout<<"\nBook Name:";
		puts(bname);
		cout<<"\nAuthor Name:";
		puts(aname);
	}
	void modifybook()
	{
		SetConsoleTextAttribute(h,2);
		cout<<"\nBook Number:"<<bno;
		cin.ignore();
		SetConsoleTextAttribute(h,12);
		cout<<"\nModify Book Name:";
		gets(bname);
		cout<<"\nModify Author's Name:";
		gets(aname);
		
	}
	char* retbno()
	{
		return bno;
	}
	void report()
	{
		SetConsoleTextAttribute(h,6);
		cout<<bno<<setw(30)<<bname<<setw(30)<<aname<<endl;
	}
};
class student
{
	char admno[6];
	char name[20];
	char stbno[6];
	int token;
	public:
	void createstudent()
	{
		system("cls");
		HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h,2);
		cout<<"\nNEW STUDENT ENTRY....\n";
		SetConsoleTextAttribute(h,1);
		cout<<"\n\nEnter The Student Name: ";
		cin.ignore();
		gets(name);
		//cin.ignore();
		cout<<"\nEnter The Admission No.: ";
		cin>>admno;
		int token=0;
		stbno[0]='\0';
		SetConsoleTextAttribute(h,6);
		cout<<"\n\nStudent Record Created.....";
		getch();
		
	}
	void showstudent()
	{
		HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h,2);
		cout<<"\nAdmission Number:"<<admno;
		SetConsoleTextAttribute(h,1);
		cout<<"\nStudent Name:";
		puts(name);
		cout<<"\nNo of Book Issued:"<<token;
		if(token==1)
		{
			cout<<"\nBook Number"<<stbno;
		}
	}
	void modifystudent()
	{
		HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h,4);
		cout<<"\nAdmission No."<<admno;
		cin.ignore();
		cout<<"\nModify Student Name:";
		gets(name);
	}
	char* retadmno()
	{
		return admno;
	}
	char* retstbno()
	{
		return stbno;
	}
	int rettoken()
	{
		return token;
	}
	void addtoken()
	{
		token=1;
	}
	void resettoken()
	{
		token=0;
	}
	void getstbno(char t[])
	{
		strcpy(stbno,t);
	}
	void report()
	{
		HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(h,6);
		cout<<admno<<setw(30)<<name<<setw(30)<<token<<endl;
	}
};
fstream fp,fp1;
book bk;
student st;
HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
void writebook()
{
	char ch;
	fp.open("book.dat",ios::out|ios::app);
	do
	{
		system("cls");
		bk.createbook();
		fp.write((char*)&bk,sizeof(book));
		SetConsoleTextAttribute(h,6);
		cout<<"\n\nDo you want to add more record..(y/n?)";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}
void writestudent()
{
	char ch;
	fp.open("student.dat",ios::out|ios::app);
	do
	{
		system("cls");
		st.createstudent();
		fp.write((char*)&st,sizeof(student));
		SetConsoleTextAttribute(h,6);
		cout<<"\n\nDo you want to add more record..(y/n?)";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}
void displayspb(char n[])
{
	SetConsoleTextAttribute(h,2);
	SetConsoleTextAttribute(h,14);
	cout<<"\nBOOK DETAILS\n";
	int flag=0;
	fp.open("book.dat",ios::in);
	while(fp.read((char*)&bk,sizeof(book)))
	{
		if(strcmpi(bk.retbno(),n)==0)
		{
			bk.showbook();
			flag=1;
		}
	}
	fp.close();
	if(flag==0)
	{
		SetConsoleTextAttribute(h,6);
		cout<<"\n\nBook doesn't exist";
		
	}
	getch();
}

void displaysps(char n[])
{
	SetConsoleTextAttribute(h,1);
	cout<<"\nSTUDENT DETAILS\n";
	int flag=0;
	fp.open("student.dat",ios::in);
	while(fp.read((char*)&st,sizeof(student)))
	{
		if(strcmpi(st.retadmno(),n)==0)
		{
			st.showstudent();
			flag=1;
		}
	}
	fp.close();
	if(flag==0)
	{
		SetConsoleTextAttribute(h,6);
		cout<<"\n\nstudent doesn't exist";
		
	}
	getch();
}
void modifybook()
{
	char n[6];
	int found =0;
	system("cls");
	SetConsoleTextAttribute(h,1);
	cout<<"\n\nMODIFY BOOK RECORD...";
	SetConsoleTextAttribute(h,2);
	cout<<"\n\nEnter The Book No.";
	cin>>n;
	fp.open("book.dat",ios::in|ios::out);
	while(fp.read((char*)&bk,sizeof(book))&&found==0)
	{
		if(strcmpi(bk.retbno(),n)==0)
		{
			bk.showbook();
			SetConsoleTextAttribute(h,3);
			cout<<"\nEnter the new details of book"<<endl;
			bk.modifybook();
			int pos=-1*sizeof(bk);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&bk,sizeof(book));
			SetConsoleTextAttribute(h,6);
			cout<<"\n\n\tRecord updated";
			found=1;
			
		}
	}
	fp.close();
	if(found==0)
	{
		SetConsoleTextAttribute(h,6);
		cout<<"\n\nRecord Not Found";
	}
	getch();
}


void modifystudent()
{
	char n[6];
	int found =0;
	system("cls");
	SetConsoleTextAttribute(h,1);
	cout<<"\n\nMODIFY STUDENT RECORD...";
	SetConsoleTextAttribute(h,14);
	cout<<"\n\nEnter The Admission No.";
	cin>>n;
	fp.open("student.dat",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(student))&&found==0)
	{
		if(strcmpi(st.retadmno(),n)==0)
		{
			st.showstudent();
			SetConsoleTextAttribute(h,4);
			cout<<"\nEnter the new details of student"<<endl;
			st.modifystudent();
			int pos=-1*sizeof(st);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&st,sizeof(student));
			SetConsoleTextAttribute(h,6);
			cout<<"\n\n\tRecord updated";
			found=1;
			
		}
	}
	fp.close();
	if(found==0)
	{
		SetConsoleTextAttribute(h,6);
		cout<<"\n\nRecord Not Found";
	}
	getch();
}
void deletestudent()
{
	char n[6];
	int flag=0;
	system("cls");
	SetConsoleTextAttribute(h,1);
	cout<<"\n\n\n\tDELETE STUDENT....";
	SetConsoleTextAttribute(h,2);
	cout<<"\n\nEnter The admission no. :";
	cin>>n;
	fp.open("student.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*) &st,sizeof(student)))
	{
		if(strcmpi(st.retadmno(),n)!=0)
		{
			fp2.write((char*) &st,sizeof(student));
		}
		else
		{
			flag=1;
	    }
    }
			fp2.close();
			fp.close();
			remove("student.dat");
			rename("temp.dat","student.dat");
			if(flag==1)
			{
				SetConsoleTextAttribute(h,6);
				cout<<"\n\n\tRecord Deleted....";
			}
			else
			{
				SetConsoleTextAttribute(h,6);
				cout<<"\n\nRecord Not Found....";
			}
			getch();
		
}
void deletebook()
{
	char n[6];
	int flag=0;
	system("cls");
	SetConsoleTextAttribute(h,12);
	cout<<"\n\n\n\tDELETE BOOK....";
	SetConsoleTextAttribute(h,11);
	cout<<"\n\nEnter The book no. :";
	cin>>n;
	fp.open("book.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*) &st,sizeof(book)))
	{
		if(strcmpi(st.retadmno(),n)!=0)
		{
			fp2.write((char*) &st,sizeof(book));
		}
		else
		{
			flag=1;
	    }
    }
			fp2.close();
			fp.close();
			remove("book.dat");
			rename("temp.dat","book.dat");
			if(flag==1)
			{
				SetConsoleTextAttribute(h,6);
				cout<<"\n\n\tRecord Deleted....";
			}
			else
			{
				SetConsoleTextAttribute(h,6);
				cout<<"\n\nRecord Not Found....";
			}
			getch();
		
}
void displayalls()
{
	system("cls");
	fp.open("student.dat",ios::in);
	if(!fp)
	{
		SetConsoleTextAttribute(h,6);
		cout<<"File Could Not Be Open";
		getch();
		return;
	}
	SetConsoleTextAttribute(h,2);
	cout<<"\n\n\t\tstudent list\n\n";
	SetConsoleTextAttribute(h,1);
	cout<<"=================================================================================\n";
	cout<<"Admission No."<<setw(30)<<"Name"<<setw(30)<<"Book Issued\n";
	cout<<"=================================================================================\n";
	while(fp.read((char*)&st,sizeof(student)))
	{
		st.report();
	}
	fp.close();
	getch();
}

void displayallb()
{
	system("cls");
	fp.open("book.dat",ios::in);
	if(!fp)
	{
		SetConsoleTextAttribute(h,6);
		cout<<"File Could Not Be Open";
		getch();
		return;
	}
	SetConsoleTextAttribute(h,2);
	cout<<"\n\n\t\tBook list\n\n";
	SetConsoleTextAttribute(h,1);
	cout<<"===============================================================================\n";
	cout<<"Book Number"<<setw(30)<<"Book Name"<<setw(30)<<"Author\n";
	cout<<"===============================================================================\n";
	while(fp.read((char*)&bk,sizeof(book)))
	{
		bk.report();
	}
	fp.close();
	getch();
}
void bookissue()
{
	char sn[6],bn[6];
	int found =0,flag=0;
	system("cls");
	SetConsoleTextAttribute(h,8);
	cout<<"\n\nBOOK ISSUE....";
	SetConsoleTextAttribute(h,1);
	cout<<"\n\n\tEnter admission no. of student";
	cin>>sn;
	fp.open("student.dat",ios::in|ios::out);
	fp1.open("book.dat",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(student))&&found==0)
	{
		if(strcmpi(st.retadmno(),sn)==0)
		{
			found=1;
			if(st.rettoken()==0)
			{
				SetConsoleTextAttribute(h,14);
				cout<<"\n\n\tEnter The Book No.";
				cin>>bn;
				while(fp1.read((char*)&bk,sizeof(book))&&flag==0)
				{
					if(strcmpi(bk.retbno(),bn)==0)
					{
						flag=1;
						st.addtoken();
						st.getstbno(bk.retbno());
						int pos=-1*sizeof(st);
						fp.seekg(pos,ios::cur);
						fp.write((char*)&st,sizeof(student));
						SetConsoleTextAttribute(h,6);
						cout<<"\n\n\tBook issued successful\n\nPlease Note:write the book issue dat in backside of your book and \nreturn book within 15 days,Fine Rs. 1 for each day after 15 days period";
					
					}
				}
				if(flag==0)
				{
					SetConsoleTextAttribute(h,6);
					cout<<"Book no. does not exist";
				}
			}
			else
			{
				SetConsoleTextAttribute(h,6);
				cout<<"you have not returned the last book";
			}
			
		}
	}
	if(found==0)
	{
		SetConsoleTextAttribute(h,6);
		cout<<"student record does not exist....";
	}
	getch();
	fp.close();
	fp1.close();
}
void bookdeposit()
{
	char sn[6],bn[6];
	int found =0,flag=0,days,fine;
	system("cls");
	SetConsoleTextAttribute(h,1);
	cout<<"\n\nBOOK DEPOSIT....";
	SetConsoleTextAttribute(h,2);
	cout<<"\n\n\tEnter admission no. of student";
	cin>>sn;
	fp.open("student.dat",ios::in|ios::out);
	fp1.open("book.dat",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(student))&&found==0)
	{
		if(strcmpi(st.retadmno(),sn)==0)
		{
			found=1;
			if(st.rettoken()==1)
			{
				SetConsoleTextAttribute(h,14);
				cout<<"\n\n\tEnter The Book No.";
				cin>>bn;
				while(fp1.read((char*)&bk,sizeof(book))&&flag==0)
				{
					if(strcmpi(bk.retbno(),bn)==0)
					{
						flag=1;
						bk.showbook();
						SetConsoleTextAttribute(h,15);
						cout<<"\n\nBook deposited in no. of days";
						cin>>days;
						if(days>15)
						{
							fine=(days-15)*1;
							SetConsoleTextAttribute(h,6);
							cout<<"\n\nFine is depossited Rs."<<fine;
						}
						st.resettoken();
						int pos=-1*sizeof(st);
						fp.seekg(pos,ios::cur);
						fp.write((char*)&st,sizeof(student));
						SetConsoleTextAttribute(h,13);
						cout<<"\n\n\tBook Deposited successfully";
					
					}
				}
				if(flag==0)
				{
					SetConsoleTextAttribute(h,6);
					cout<<"Book no does not exist";
				}
			}
			else
			{
				SetConsoleTextAttribute(h,6);
				cout<<"No book is issued....";
			}
			
		}
	}
	if(found==0)
	{
		SetConsoleTextAttribute(h,6);
		cout<<"student record does not exist....";
	}
	getch();
	fp.close();
	fp1.close();
}
void gotoxy(int x,int y)
{
	COORD c;
	c.X=x;
	c.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
void start()
{
	HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h,6);
	system("cls");
	gotoxy(77,9);
	cout<<"LIBRARY";
	gotoxy(77,11);
	cout<<"MANAGEMENT";
	gotoxy(77,13);
	cout<<"SYSTEM";
	SetConsoleTextAttribute(h,13);
	cout<<"\n\n\tDeveloper: Usha Sharma";
	SetConsoleTextAttribute(h,1);
	cout<<"\n\n\tEnjoy Programming With usha sharma";
	SetConsoleTextAttribute(h,2);
	gotoxy(65,20);
	cout<<"PLEASE PRESS ANY KEY TO CONTINUE";
	getch();
}
void adminmenu()
{
	system("cls");
	int ch2;
	HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h,1);
	cout<<"\n\n\tADMINISTRATOR MENU";
	cout<<"\n\n\t1. CREATE STUDENT RECORD";
	cout<<"\n\n\t2. DISPLAY ALL STUDENTS RECORD";
	cout<<"\n\n\t3. DISPLAY SPECIFIC STUDENT RECORD";
	cout<<"\n\n\t4. MODIFY STUDENT RECORD";
	cout<<"\n\n\t5. DELETE STUDENT RECORD";
	cout<<"\n\n\t6. CREATE BOOK";
	cout<<"\n\n\t7. DISPLAY ALL BOOKS";
	cout<<"\n\n\t8. DISPLAY SPECIFIC BOOK";
	cout<<"\n\n\t9. MODIFY BOOK RECORD";
	cout<<"\n\n\t10. DELETE BOOK RECORD";
	cout<<"\n\n\t11. BACK TO MAIN MENU";
	SetConsoleTextAttribute(h,6);
	cout<<"\n\n\t Please Enter Your Choice(1-11)";
	cin>>ch2;
	switch(ch2)
	{
		case 1:
			writestudent();
			break;
		case 2:
			displayalls();
			break;
		case 3:
			system("cls");
			char num[6];
			cout<<"\n\n\tPlease Enter The Admission NO.";
			cin>>num;
			displaysps(num);
			break;
		case 4:
		    modifystudent();
			break;
		case 5:
		   deletestudent();
		   break;
		case 6:
		   writebook();
		   break;
		case 7:
			displayallb();
			break;
		case 8:
			{
			system("cls");
			char num[6];
			cout<<"\n\n\tPlease Enter The Book NO.";
			cin>>num;
			displayspb(num);
			break;
		    }
		case 9:
		    modifybook();
			break;
		case 10:
		   deletebook();
		   break;
		case 11:
			return;
		default:
			gotoxy(65,30);
			cout<<"INVALID CHOICE , PRESS ENTER TO TRY AGAIN";
			getch();
			break;
    }
    adminmenu();
}
int main()
{
	char ch;
	start();
	system("cls");
	HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h,11);
	do
	{
		system("cls");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t1. BOOK ISSUE";
		cout<<"\n\n\t2. BOOK DEPOSIT";
		cout<<"\n\n\t3. ADMINISTRATION MENU";
		cout<<"\n\n\t4. EXIT";
		SetConsoleTextAttribute(h,6);
		cout<<"\n\n\nPlease Select Your Option(1-4)";
		ch=getche();
		switch(ch)
		{
			case '1':
				bookissue();
				break;
			case '2':
			    bookdeposit();	
			    break;
			case '3':
				adminmenu();
				break;
			case '4':
				exit(0);
				break;
			default:
				cout<<"\nInvalid Choice, Try Again";
				getch();
				break;
				
		}
	}while(ch!=4);
	getch();
	return 0;
}

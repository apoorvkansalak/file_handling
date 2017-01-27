#include <process.h>
#include <iostream.h>
#include <conio.h>
#include <fstream.h>
#include <stdio.h>
#include <string.h>
class book 	
{
	char bno[6];
	char bname[50];
	char aname[20];
  public:
	void create_book()
	{
		cout<<"\nNEW BOOK ENTRY...\n";
		cout<<"\nEnter The book no.";
		cin>>bno;
		cout<<"\n\nEnter The Name of The Book ";
		gets(bname);
		cout<<"\n\nEnter The Author's Name ";
		gets(aname);
		cout<<"\n\n\nBook Created..";
	}

	void show_book()
	{
		cout<<"\nBook no. : "<<bno;
		cout<<"\nBook Name : ";
		puts(bname);
		cout<<"Author Name : ";
		puts(aname);
	}

	void modify_book()
	{
		cout<<"\nBook no. : "<<bno;
		cout<<"\nModify Book Name : ";
		gets(bname);
		cout<<"\nModify Author's Name of Book : ";
		gets(aname);
	}

	char* retbno()
	{
		return bno;
	}
};

void indata()
{
	ofstream fout("book.dat",ios::binary|ios::app);
	book bk;

	bk.create_book();
	fout.write((char*)&bk,sizeof(book));
}  
void showdata()
{
	ifstream fin("book.dat",ios::binary);
	book bk;
	if (!fin)
	{
		cout<<"\nFile cannot be opened\n";
		getch();
		exit(0);
	}
	else
	{
		while(fin.read((char*)&bk,sizeof(book)))
		{
			bk.show_book();
		}
	}
}
void search()
{
	ifstream fin("book.dat",ios::binary);
	book bk;
	if (!fin)
	{
		cout<<"\nFile cannot be opened\n";
		getch();
		exit(0);
	}
	else
	{	char temp_bno[6];
		cout<<"\nEnter book no to be searched\n";
		gets(temp_bno);
		int count=0;
		while(!fin.eof())
		{
			fin.read((char*)&bk,sizeof(book));
			if(strcmp(bk.retbno(),temp_bno)==0)
			{
				bk.show_book();
				count++;
			}
		}
		if(count==0)
		{
			cout<<"\nRecord not found\n";
		}
	}
}
void deldata()
{	char temp_bno[6];
	fstream fin("book.dat",ios::in|ios::binary);
	fstream fout("temp.dat",ios::binary|ios::out);
	book bk;
	if(!fin)
	{
		cout<<"\nError in opening file";
		getch();
		exit(0);
	}
	cout<<"\nEnter the book no to be deleted\n";
	gets(temp_bno);
	while(fin.read((char*)&bk,sizeof(book)))
	{
		
		if (strcmp(bk.retbno(),temp_bno)!=0)
		{
			fout.write((char*)&bk,sizeof(book));
		}
	}
	remove("book.dat");
	rename("temp.dat","book.dat");
	fin.close();
	fout.close();
	
}

void main()
{
	clrscr();
	char ch='y';
	int n;
	do{
		clrscr();
		cout<<"\nEnter your choice";
		cout<<"\n1.Add Record\n2.Delete Record\n3.Show all Record\n4.Find Record\n5.Exit\n";
		cin>>n;
		switch(n)
		{
			case 1:
			indata();
			break;
			
			case 2:
			deldata();
			break;
			
			case 3:
			showdata();
			break;

			case 4:
			search();
			break;

			case 5:
			exit(0);

			default:
			cout<<"\nWrong choice!";
			getch();
		}
		cout<<"\nWant to enter again?";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
}
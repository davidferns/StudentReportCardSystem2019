#include<fstream.h>
#include<iomanip.h>
#include<stdio.h>
#include<conio.h>
class student
{
int rollno;
char name[50];
int p_marks, c_marks, m_marks, e_marks, cs_marks;
int per;
char grade;

void calculate();	//function to calculate grade
public:
void getdata();		//function to accept data from user
void showdata();	//function to show data on screen
void show_tabular();
int retrollno();
};
void student::calculate()
{
per=(p_marks+c_marks+m_marks+e_marks+cs_marks)/5.0;
if(per>=90)
grade='A';
else if(per>=80)
grade='B';
else if(per>=70)
grade='C';
else if(per>=50)
grade='D';
else if(per>=33)
grade='E';
else
grade='F';
}
void student::getdata()
{
cout<<"Enter The roll number of student "<<endl;
cin>>rollno;
cout<<"\nEnter The Name of student ";
gets(name);
cout<<"\nENTER THE MARKS OUT OF 100";
cout<<"\nEnter the marks in Physics: ";
cin>>p_marks;
cout<<"\nEnter the marks in Chemistry : ";
cin>>c_marks;
cout<<"\nEnter the marks in Maths : ";
cin>>m_marks;
cout<<"\nEnter the marks in English : ";
cin>>e_marks;
cout<<"\nEnter the marks in Computer Science : ";
cin>>cs_marks;
calculate();
}

void student::showdata()
{
cout<<"\nRoll number of student : "<<rollno;
cout<<"\nName of student : "<<name;
cout<<"\nMarks in Physics : "<<p_marks;
cout<<"\nMarks in Chemistry : "<<c_marks;
cout<<"\nMarks in Maths : "<<m_marks;
cout<<"\nMarks in English : "<<e_marks;
cout<<"\nMarks in Computer Science :"<<cs_marks;
cout<<"\nPercentage of student is  :"<<per;
cout<<"\nGrade of student is :"<<grade;
}
void student::show_tabular()
{
cout<<rollno<<setw(6)<<" "<<name<<setw(20)<<p_marks<<setw(4)<<c_marks<<setw(4)<<m_marks<<setw(4)
<<e_marks<<setw(4)<<cs_marks<<setw(6)<<per<<setw(6)<<" "<<grade<<endl;
}
int student::retrollno()
{
return rollno;
}
void write_student();	//write the record in binary file
void display_all();	//read all records from binary file
void display_sp(int);	//accept rollno and read record from binary file
void modify_student(int);	//accept rollno and update record of binary file
void delete_student(int);	//accept rollno and delete selected records from binary file
void class_result();	//display all records in tabular format from binary file
void result();		//display result menu
void intro();		//display welcome screen
void entry_menu();	//display entry menu on screen
int main()
{
char ch;
cout.setf(ios::fixed|ios::showpoint);
cout<<setprecision(2); // program outputs decimal number to two decimal places
clrscr();
intro();
do
{
clrscr();
cout<<"\n\tMAIN MENU";
cout<<"\n\t01. RESULT MENU";
cout<<"\n\t02. ENTRY/EDIT MENU";
cout<<"\n\t03. EXIT";
cout<<"\n\n\tPlease Select Your Option (1-3) ";
cin>>ch;
clrscr();
switch(ch)
{
case '1': result();
break;
case '2': entry_menu();
break;
case '3':
break;
default :
cout<<"\a";
}
}while(ch!='3');
return 0;
}

void write_student()
{
student st;
fstream f;
f.open("student.dat",ios::binary|ios::app);
st.getdata();
f.write((char *) &st, sizeof(st));
f.close();
cout<<"\nStudent record Has Been Created ";
cin.ignore();
getch();
}
void display_all()
{
student st;
fstream f;
f.open("student.dat",ios::in/ios::binary);
if(!f)
{
cout<<"File could not be opened. Press any key!";
getch();
return;
}
cout<<"\n\t DISPLAY ALL RECORD! \n";
while(f.read((char *) &st, sizeof(st)))
{
st.showdata();
}
f.close();
getch();
}
void display_sp(int n)
{
student st;
ifstream f;
f.open("student.dat",ios::in/ios::binary);
if(!f)
{
cout<<"File could not be opened. Press any key!";
getch();
return;
}
int flag=0;
while(f.read((char *) &st, sizeof(st)))
{
if(st.retrollno()==n)
{
st.showdata();
flag=1;
}
}
f.close();
if(flag==0)
cout<<"\nRECORD DOES NOT EXIST";
getch();
}
void modify_student(int n)
{
int found=0;
student st;
fstream f;
f.open("student.dat",ios::binary|ios::in|ios::out);
if(!f)
{
cout<<"File could not be opened. Press any key!";
getch();
return;
}
while(f.read((char *) &st, sizeof(st)) && found==0)
{
if(st.retrollno()==n)
{
st.showdata();
cout<<"\n\nPlease Enter The New Details of student"<<endl;
st.getdata();
int pos=(-1)*sizeof(st);
f.seekp(pos,ios::cur);
f.write((char *) &st, sizeof(st));
cout<<"\n\t Record Updated";
found=1;
}
}
f.close();
if(found==0)
cout<<"\n\n Record Not Found ";
getch();
}
void delete_student(int n)
{
student st;
fstream f;
f.open("student.dat",ios::in|ios::binary);
if(!f)
{
cout<<"File could not be open !! Press any Key...";
getch();
return;
}
fstream g;
g.open("Temp.dat",ios::out|ios::binary);
g.seekg(0,ios::beg);
while(g.read((char *) &st, sizeof(st)))
{
if(st.retrollno()!=n)
{
g.write((char *) &st, sizeof(st));
}
}
g.close();
f.close();
remove("student.dat");
rename("Temp.dat","student.dat");
cout<<"\n\tRecord Deleted!";
getch();
}
void class_result()
{
student st;
ifstream inFile;
inFile.open("student.dat",ios::binary);
if(!inFile)
{
cout<<"File could not be opened. Press any key!";
getch();
return;
}
cout<<"\n\tALL STUDENTS RESULT\n";
cout<<"R.No       Name        P   C   M   E   CS   %age   Grade"<<endl;
while(inFile.read((char *) &st, sizeof(student)))
{
st.show_tabular();
}
getch();
inFile.close();
}

//***************************************************************
//    	function to display result menu
//****************************************************************

void result()
{
char ch;
int rno;
cout<<"\n\n\n\tRESULT MENU";
cout<<"\n\n\n\t1. Class Result";
cout<<"\n\n\t2. Student Report Card";
cout<<"\n\n\t3. Back to Main Menu";
cout<<"\n\n\n\tEnter Choice (1/2/3)? ";
cin>>ch;
clrscr();
switch(ch)
{
case '1' :class_result(); break;
case '2' :cout<<"\n\n\tEnter Roll Number Of Student : ";
cin>>rno;
display_sp(rno); break;
case '3' :break;
default :cout<<"\a";
}
}
void intro()
{
cout<<"\n\tSTUDENT REPORT CARD PROJECT\n";
cout<<"\n\tMADE BY: RAZEEN/DAVID";
cout<<"\n\tSCHOOL : SEPS";
getch();
}
void entry_menu()
{
char ch;
int num;
clrscr();
cout<<"\n\tENTRY MENU";
cout<<"\n\t1.CREATE STUDENT RECORD";
cout<<"\n\t2.DISPLAY ALL STUDENTS RECORDS";
cout<<"\n\t3.SEARCH STUDENT RECORD ";
cout<<"\n\t4.MODIFY STUDENT RECORD";
cout<<"\n\t5.DELETE STUDENT RECORD";
cout<<"\n\t6.BACK TO MAIN MENU";
cout<<"\n\tPlease Enter Your Choice (1-6) ";
cin>>ch;
clrscr();
switch(ch)
{
case '1':	write_student(); break;
case '2':	display_all(); break;
case '3':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
display_sp(num); break;
case '4':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
modify_student(num);break;
case '5':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
delete_student(num);break;
case '6':	break;
default:	cout<<"\a"; entry_menu();
}
}
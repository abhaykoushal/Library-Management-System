#include <iostream>
#include <string.h>
#include <string>
#include <windows.h>
#include <iomanip>
#include <fstream>

using namespace std;

void gotoxy(int x,int y)
{
    COORD coord = {x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

class book
{
    char bno[6];
    string bname;
    string aname;

public:
    void createbook()
    {
        cout << "\n\t\tNew book entry...\n";
        cout << "\nEnter the book no.: ";
        cin >> bno;
        cin.get();
        cout << "\nEnter the book name: ";
        getline(cin,bname);
        cout << "\nEnter the author's name: ";
        getline(cin,aname);
        cout << "\n\n\tBook Created Successfully... ";
    }

    void showbook()
    {
        cout << "\nBook No: " << bno;
        cout << "\nBook Name: ";
        cout << bname;
        cout << "\nAuthor's Name: ";
        cout << aname;
    }

    void modifybook()
    {
        cout << "\nBook No.: " << bno;
        cout << "\nModify Book Name: ";
        cin.get();
        getline(cin,bname);
        cout << "Modify Author's Name: ";
        getline(cin,aname);
    }

    char* retbno()
    {
        return bno;
    }

    void report()
    {
        cout << "\t" << bno << setw(25) << bname << setw(20) << aname << endl;
    }
};

class student
{
    char admno[6];
    string name;
    char stbno[6];
    int token;
public:
    void createstudent()
    {
        system("Cls");
        cout << "\nNEW STUDENT ENTRY... ";
        cout << "\nEnter Admission No.: ";
        cin >> admno;
        cin.get();
        cout << "\nEnter the student name: ";
        getline(cin, name);
        token = 0;
        stbno[0] = '/0';
        cout << "\n\n Student Record Created... ";
    }

    void showstudent()
    {
        cout << "\nAdmission No.: " << admno;
        cout << "\nStudent Name: ";
        cout << name;
        cout << "\nNo. of books issued: " << token;
        if(token == 1)
        {
            cout << "\nBook No.: " << stbno;
        }
    }

    void modifystudent()
    {
        cout << "\nAdmission No.: " << admno;
        cout << "\nModify Student Name: ";
        cin >> name;
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
        token = 1;
    }

    void resettoken()
    {
        token = 0;
    }

    void getstbno(char t[])
    {
        strcpy(stbno, t);
    }

    void report()
    {
        cout << "\t" << admno << setw(27) << name << setw(15) << token << endl;
    }
};

fstream fp, fp1;
book bk;
student st;

void writebook()
{
    char ch;
    fp.open("book.dat", ios::out|ios::app);
    do
    {
        system("Cls");
        bk.createbook();
        fp.write((char*)&bk, sizeof(book));
        cout << "\n\nDo you want to add more record... [y/n]\n";
        cin >> ch;
    }while(ch == 'y' || ch == 'Y');
    fp.close();
}

void writestudent()
{
    char ch;
    fp.open("student.dat", ios::out|ios::app);
    do
    {
        system("Cls");
        st.createstudent();
        fp.write((char*)&st, sizeof(student));
        cout << "\n\nDo you want to add more record... [y/n]\n";
        cin >> ch;
    }while(ch == 'y' || ch == 'Y');
    fp.close();
}

void displayspb(char n[])
{
    cout << "\nBOOK DETAILS\n";
    int flag = 0;

    fp.open("book.dat", ios::in);

    while(fp.read((char*)&bk, sizeof(book)))
    {
        if(strcmpi(bk.retbno(), n) == 0)                             //strcmpi is not case sensitive
        {
            bk.showbook();
            flag = 1;                   // flag will be set to 1 if book is found
        }
    }
    fp.close();
    if(flag == 0)
    {
        cout << "\n\nBook does not exist";
    }
    cin.get();
    cin.get();
}

void displaysps(char n[])
{
    cout << "\nSTUDENT DETAILS\n";
    int flag = 0;

    fp.open("student.dat", ios::in);

    while(fp.read((char*)&st, sizeof(student)))
    {
        if(strcmpi(st.retadmno(), n) == 0)                             //strcmpi is not case sensitive
        {
            st.showstudent();
            flag = 1;                   // flag will be set to 1 if book is found
        }
    }
    fp.close();
    if(flag == 0)
    {
        cout << "\n\nStudent does not exist";
    }
    cin.get();
    cin.get();
}

void displayalls()
{
    system("Cls");
    fp.open("student.dat", ios::in);
    if(!fp)
    {
        cout << "Can't open file";
        cin.get();
        cin.get();
        return;
    }
    cout << "\n\n\t\t\tSTUDENT LIST\n";
    cout << "=======================================================\n";
    cout << "      Adm. No." << setw(20) << "Name" << setw(20) << "Books Issued\n";
    cout << "=======================================================\n";

    while(fp.read((char*)&st, sizeof(student)))
    {
        st.report();
    }
    fp.close();
    cin.get();
    cin.get();
}

void displayallb()
{
    system("Cls");
    fp.open("book.dat", ios::in);
    if(!fp)
    {
        cout << "Can't open file";
        cin.get();
        cin.get();
        return;
    }
    cout << "\n\n\t\t\tBOOK LIST\n";
    cout << "===========================================================\n";
    cout << "     Book No." << setw(20) << "Book Name" << setw(20) << "Author\n";
    cout << "===========================================================\n";

    while(fp.read((char*)&bk, sizeof(book)))
    {
        bk.report();
    }
    fp.close();
    cin.get();
    cin.get();
}

void modifybook()
{
    char n[6];
    int found = 0;
    system("Cls");

    displayallb();

    cout << "\nEnter the Book No. that you want to modify: ";
    cin >> n;
    fp.open("book.dat", ios::in|ios::out);
    while(fp.read((char*)&bk, sizeof(book)) && found == 0)       //it will read first book and the pointer will move on to the next book
    {
        if(strcmpi(bk.retbno(),n) == 0)
        {
            bk.showbook();
            cout << "\n\nEnter the new details of the book: " << endl;
            bk.modifybook();
            int pos = -1*sizeof(bk);                            //we bring back the pointer to one book back where book was found
            fp.seekp(pos, ios::cur);
            fp.write((char*)&bk, sizeof(book));
            cout << "\n\nRECORD UPDATED";
            found = 1;
        }
    }
    fp.close();
    if(found == 0)
    {
        cout << "\n\nRecord not found.";
    }
    cin.get();
    cin.get();
}

void modifystudent()
{
    char n[6];
    int found = 0;
    system("Cls");

    displayalls();

    cout << "\nEnter the Admission No. that you want to modify: ";
    cin >> n;

    fp.open("student.dat", ios::in|ios::out);
    while(fp.read((char*)&st, sizeof(student)) && found == 0)       //it will read first student and the pointer will move on to the next student
    {
        if(strcmpi(st.retadmno(),n) == 0)
        {
            st.showstudent();
            cout << "\n\nEnter the new details of the student: " << endl;
            st.modifystudent();
            int pos = -1*sizeof(st);                            //we bring back the pointer to one student back where student was found
            fp.seekp(pos, ios::cur);
            fp.write((char*)&st, sizeof(student));
            cout << "\n\nRECORD UPDATED";
            found = 1;
        }
    }
    fp.close();
    if(found == 0)
    {
        cout << "\n\nRecord not found.";
    }
    cin.get();
    cin.get();
}


void deletestudent()
{
    char n[6];
    int flag = 0;
    system("Cls");

    displayalls();
    cout << "\nEnter the admission No. of the student that you want to delete: ";
    cin >> n;

    fp.open("student.dat", ios::in|ios::out);
    fstream fp2;
    fp2.open("temp.dat", ios::out);
    fp.seekg(0, ios::beg);              //changing position of pointer to beginning of the file

    while(fp.read((char*)&st, sizeof(student)))
    {
        if(strcmpi(st.retadmno(),n) != 0)               //admission no. not matched
        {
            fp2.write((char*)&st, sizeof(student));     //read from student.dat & written to temp.dat
        }
        else
        {
            flag = 1;       //student found
        }
    }
    fp.close();
    fp2.close();

    //removing file that had all students
    remove("student.dat");

    //making the temp file as original file thus deleting the STUDENT
    rename("temp.dat","student.dat");

    if(flag == 1)
    {
        cout << "\n\n\tSTUDENT RECORD DELETED SUCCESSFULLY...";
    }
    else
    {
        cout << "\n\n\tRecord not found...";
    }
    cin.get();
    cin.get();
}

void deletebook()
{
    char n[6];
    int flag = 0;
    system("Cls");

    displayallb();
    cout << "\nEnter the book No. that you want to delete: ";
    cin >> n;


    fp.open("book.dat", ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat", ios::out);
    fp.seekg(0, ios::beg);              //changing position of pointer to beginning of the file

    while(fp.read((char*)&bk, sizeof(book)))
    {
        if(strcmpi(bk.retbno(),n) != 0)               //book no. not matched
        {
            fp2.write((char*)&bk, sizeof(book));     //read from book.dat & written to temp.dat
        }
        else
        {
            flag = 1;       //book found
        }
    }
    fp2.close();
    fp.close();

    //removing file that had all books
    remove("book.dat");

    //making the temp file as original file thus deleting the BOOK
    rename("Temp.dat","book.dat");

    if(flag == 1)
    {
        cout << "\n\n\tBOOK RECORD DELETED SUCCESSFULLY...";
    }
    else
    {
        cout << "\n\n\tRecord not found...";
    }
    cin.get();
    cin.get();
}

void bookissue()
{
    char sn[6], bn[6];
    int found = 0, flag = 0;
    system("Cls");

    cout << "\n\nBOOK ISSUE";
    cout << "\n\n\tEnter Admission No. of Student: ";
    cin >> sn;
    displayallb();
    fp.open("student.dat", ios::in | ios::out);
    fp1.open("book.dat", ios::in | ios::out);
    while(fp.read((char*)&st, sizeof(student)) && found == 0)
    {
        if(strcmpi(st.retadmno(),sn) == 0)
        {
            found = 1;
            if(st.rettoken() == 0)
            {
                cout << "\n\n\tEnter Book No. that you want to issue: ";
                cin >> bn;

                while(fp1.read((char*)&bk, sizeof(book)) && flag == 0)
                {
                    if(strcmpi(bk.retbno(),bn) == 0)
                    {
                        bk.showbook();
                        flag = 1;
                        st.addtoken();
                        st.getstbno(bk.retbno());
                        int pos = -1*sizeof(st);
                        fp.seekg(pos, ios::cur);
                        fp.write((char*)&st, sizeof(student));
                        cout << "\n\n\tBook issued Successfully...";
                    }
                }
                if(flag == 0)
                {
                    cout << "\nBook Does not exist";
                }
            }
            else
            {
                cout << "\nYou haven't returned the last book.";
            }
        }

    }
    if(found == 0)
    {
        cout << "Student Record does not exist...";
    }
    cin.get();
    cin.get();
    fp.close();
    fp1.close();
}

void bookdeposit()
{
    char sn[6], bn[6];
    int found = 0, flag = 0, day, fine;
    system("Cls");

    cout << "\n\nBOOK DEPOSIT";
    cout << "\n\n\tEnter Admission No. of Student: ";
    cin >> sn;
    fp.open("student.dat", ios::in | ios::out);
    fp1.open("book.dat", ios::in | ios::out);
    while(fp.read((char*)&st, sizeof(student)) && found == 0)
    {
        if(strcmpi(st.retadmno(),sn) == 0)
        {
            found = 1;
            if(st.rettoken() == 1)
            {
                while(fp1.read((char*)&bk, sizeof(book)) && flag == 0)
                {
                    if(strcmpi(bk.retbno(),st.retstbno()) == 0)
                    {
                        flag = 1;
                        bk.showbook();
                        cout << "\n\nBook Deposited in ___ days?\n";
                        cin >> day;
                        if(day > 15)
                        {
                            fine = (day-15)*5;
                            cout << "\n\nFine to be deposited is Rs." << fine;
                        }
                        st.resettoken();
                        int pos = -1*sizeof(st);
                        fp.seekg(pos, ios::cur);
                        fp.write((char*)&st, sizeof(student));
                        cout << "\n\n\tBook deposited Successfully...";
                    }
                }
                if(flag == 0)
                {
                    cout << "\nBook Does not exist";
                }
            }
            else
            {
                cout << "\nNo book is issued.";
            }
        }
    }
    if(found == 0)
    {
        cout << "Student Record does not exist...";
    }
    cin.get();
    cin.get();
    fp.close();
    fp1.close();
}

void start()
{
    system("Cls");

    gotoxy(50,11);
    cout << "LIBRARY MANAGEMENT SYSTEM";
    gotoxy(50,13);

    getchar();
}

void administrator()
{
    system("Cls");
    int x;
    gotoxy(50, 4);
    cout << "\tADMINISTRATOR MENU";
    gotoxy(50, 6);
    cout << " 1. CREATE STUDENT RECORD";
    gotoxy(50, 7);
    cout << " 2. DISPLAY ALL STUDENTS RECORD";
    gotoxy(50, 8);
    cout << " 3. DISPLAY SPECIFIC STUDENT'S RECORD";
    gotoxy(50, 9);
    cout << " 4. MODIFY STUDENT RECORD";
    gotoxy(50, 10);
    cout << " 5. DELETE STUDENT RECORD";

    gotoxy(50, 11);
    cout << " 6. CREATE BOOK";
    gotoxy(50, 12);
    cout << " 7. DISPLAY ALL BOOKS";
    gotoxy(50, 13);
    cout << " 8. DISPLAY SPECIFIC BOOKS";
    gotoxy(50, 14);
    cout << " 9. MODIFY BOOK RECORD";
    gotoxy(50, 15);
    cout << "10. DELETE BOOK RECORD";
    gotoxy(50, 16);
    cout << "11. BACK TO MAIN MENU";
    gotoxy(50, 18);
    cout << "ENTER YOUR CHOICE: ";

    cin >> x;

    switch(x)
    {
        case 1:
            writestudent();
            break;
        case 2:
            displayalls();
            break;
        case 3:
            char num[6];
            system("Cls");
            cout << "Enter admission No.: ";
            cin >> num;
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
            char book[6];
            system("Cls");
            cout << "Enter book No.: ";
            cin >> book;
            displayspb(book);
            break;
        case 9:
            modifybook();
            break;
        case 10:
            deletebook();
            break;
        case 11:
            return;
        default:
        {
            system("Cls");
            cout << "\n\n\n\n\n\t\t\t\t\t\tInvalid Choice\n";
            cin.get();
            cin.get();
        }
    }
    administrator();
}

int main()
{
    start();
    int ch;

    do
    {
        system("Cls");
        gotoxy(50, 7);
        cout << "MAIN MENU";
        gotoxy(50, 9);
        cout << "1. BOOK ISSUE";
        gotoxy(50, 10);
        cout << "2. BOOK DEPOSIT";
        gotoxy(50, 11);
        cout << "3. ADMINISTRATOR MENU";
        gotoxy(50, 12);
        cout << "4. EXIT";
        gotoxy(50, 14);
        cout << "ENTER YOUR CHOICE: ";

        cin >> ch;

        switch(ch)
        {
            case 1:
                bookissue();
                break;
            case 2:
                bookdeposit();
                break;
            case 3:
                administrator();
                break;
            case 4:
                exit(0);
                break;
            default:
            {
                system("Cls");
                cout << "\n\n\n\n\n\t\t\t\t\t\tInvalid Choice\n";
                cin.get();
                cin.get();
            }
        }
    }while(ch != 4);
}

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <functional>
using namespace std;

// LIBRARY MANAGEMENT SYSTEM

class Book
{

public:
    int book_no;
    char title[100], author[100];
    int dd, mm, yy;
    int cur_Student;
};

class Student
{

public:
    char name[100], address[100], branch[4];
    int id, age;
    int dd, mm, yy;
};

bool Valid_Date(int d, int m, int y)
{
    bool v = (d > 32 or m > 13 or y > 2024) ? false : true;
    return v;
}

bool Verify_Id(int id)
{
    FILE *fp;
    Student stu;
    fp = fopen("libStudent.txt", "rb");
    if (!fp)
    {
        cout << " TECHNICAL EROOR!!!";
        return false;
    }

    while (fread(&stu, sizeof(stu), 1, fp) == 1)
    {
        if (stu.id == id)
        {
            return false;
        }
    }
    fclose(fp);
    return true;
}

void Create_Student()
{
    FILE *fp;
    Student stu;
    fp = fopen("libStudent.txt", "ab+");
    if (!fp)
    {
        cout << " TECHNICAL EROOR!!!";
        return;
    }
    int n;
    cout << " Enter the number of Student :-" << endl;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        if (i < 1)
        {
            cout << i + 1 << "ST STUDENT :";
        }
        else if (i < 3)
        {
            cout << i + 1 << "ND STUDENT :";
        }
        else
        {
            cout << i + 1 << "TH STUDENT :";
        }
        getchar();
        fflush(stdin);
        cout << " Enter the Student Name :-" << endl;
        gets(stu.name);
        cout << " Enter the Student Id/Roll no. :-" << endl;
        cin >> stu.id;
        bool vId = Verify_Id(stu.id);
        if (!vId)
        {
            cout << " This Student Allready Registered " << endl;
            system("pause");
            return;
        }
        cout << " Enter the Student Age :-" << endl;
        cin >> stu.age;
        getchar();
        cout << " Enter the Student Branch :-" << endl;
        gets(stu.branch);
        cout << " Enter the Student Address :-" << endl;
        gets(stu.address);
        cout << " Enter the Date of Registration  (dd / mm / yy):-" << endl;
        cin >> stu.dd >> stu.mm >> stu.yy;
        bool v = Valid_Date(stu.dd, stu.mm, stu.yy);
        if (!v)
        {
            cout << " Entered Date Not Valid!!! " << endl;
            return;
        }
        fwrite(&stu, sizeof(stu), 1, fp);
    }
    cout << " Student Registrationed !" << endl;
    fclose(fp);
    system("pause");
}

void Remove_Student()
{
    Student stu;
    FILE *fp, *fp1;
    int id;
    bool flag = false;
    fp = fopen("libStudent.txt", "rb");
    fp1 = fopen("libStudentnew.txt", "ab+");
    if (!fp or !fp1)
    {
        cout << " TECHNICAL EROOR!!!";
        return;
    }

    cout << " Enter the Roll no or Id of a Student which you want to Remove :-" << endl;
    cin >> id;

    while (fread(&stu, sizeof(stu), 1, fp) == 1)
    {
        if (id != stu.id)
        {
            fwrite(&stu, sizeof(stu), 1, fp1);
        }
        else
            flag = true;
    }

    if (!flag)
    {
        cout << " This Student not FOUND!! " << endl;
    }
    else
    {
        cout << " Student Record Deleted " << endl;
    }

    fclose(fp);
    fclose(fp1);
    remove("libStudent.txt");
    rename("libStudentnew.txt", "libStudent.txt");
    system("pause");
}

void List_Of_Student()
{
    Student stu;
    FILE *fp;
    int i = 1;
    fp = fopen("libStudent.txt", "rb");
    if (!fp)
    {
        cout << " error ";
        return;
    }

    while (fread(&stu, sizeof(stu), 1, fp) == 1)
    {
        cout << i << " :: Student Name : " << stu.name << "    Student Id : " << stu.id << "    Date Of Registraction : " << stu.dd << " \\ " << stu.mm << " \\ " << stu.yy << endl
             << endl;
        i++;
    }

    fclose(fp);
    system("pause");
}

void Issue_Book()
{
    FILE *fp, *fw;
    Student stu;
    Book bok;
    int id;
    bool flag;
    fp = fopen("libBookStore.txt", "ab+");
    fw = fopen("libStudent.txt", "rb");

    if (!fp and !fw)
    {
        cout << " TECHNICAL EROOR!!!";
        return;
    }

    cout << " Enter the Id/Roll no of student :-" << endl;
    cin >> id;

    while (fread(&stu, sizeof(stu), 1, fw) == 1)
    {
        if (stu.id == id)
        {
            int n;
            cout << " Name : " << stu.name << endl
                 << endl;
            cout << " Enter the Number of Books :-" << endl;
            cin >> n;

            for (int i = 0; i < n; i++)
            {
                bok.cur_Student = id;
                getchar();
                cout << " Enter the Book Title :-" << endl;
                gets(bok.title);
                cout << " Enter the Book Number :-" << endl;
                cin >> bok.book_no;
                getchar();
                cout << " Enter the Name of the Author of the Book :-" << endl;
                gets(bok.author);
                cout << " Enter the Issue Date of Book :-" << endl;
                cin >> bok.dd >> bok.mm >> bok.yy;
                fwrite(&bok, sizeof(bok), 1, fp);
            }
            flag = true;
        }
    }

    if (!flag)
    {
        cout << " This Student not FOUND!!" << endl;
    }
    else
    {
        cout << " All books Issued :" << endl;
    }
    system("pause");
    fclose(fp);
    fclose(fw);
}

void Book_Detail()
{
    FILE *fp;
    Book bok;
    int i = 1;
    fp = fopen("libBookStore.txt", "rb");
    if (!fp)
    {
        cout << " TECHNICAL EROOR!!!";
        return;
    }

    while (fread(&bok, sizeof(bok), 1, fp) == 1)
    {
        cout << i << " :: Book Name : " << bok.title << "\t\tBook Number : " << bok.book_no << "\t\tBook Author : " << bok.author << endl
             << endl;
        i++;
    }

    fclose(fp);
    system("pause");
}

void Search_Book()
{
    Book bok;
    FILE *fp;
    int bookNo;
    bool flag;
    fp = fopen("libBookStore.txt", "rb");
    if (!fp)
    {
        cout << " TECHNICAL EROOR!!! ";
        return;
    }

    cout << " Enter the Book no. :-" << endl;
    cin >> bookNo;

    while (fread(&bok, sizeof(bok), 1, fp) == 1)
    {
        if (bok.book_no == bookNo)
        {
            cout << " Book Found : " << endl
                 << endl;
            cout << " Book Name : " << bok.title << endl
                 << endl;
            cout << " Book Number : " << bok.book_no << endl
                 << endl;
            cout << " Book Author Name : " << bok.author << endl
                 << endl;
            flag = true;
            break;
        }
    }

    if (!flag)
    {
        cout << " Book not Found " << endl;
    }
    fclose(fp);
    system("pause");
}

void Return_Book()
{
    FILE *fp, *fs, *fp1;
    Book bok;
    Student stu;
    int id, bn;
    bool flag1, flag2;
    fp = fopen("libBookStore.txt", "rb");
    fp1 = fopen("libBookStorenew.txt", "ab+");
    fs = fopen("libStudent.txt", "rb");

    if (!fp)
    {
        cout << " TECHNICAL EROOR!!!";
        return;
    }

    cout << " Enter the Id/Roll no of student :-" << endl;
    cin >> id;

    while (fread(&stu, sizeof(stu), 1, fs) == 1)
    {
        if (id == stu.id)
        {
            cout << " Student Name : " << stu.name << endl
                 << endl;
            cout << " Enter the Book Number " << endl;
            cin >> bn;
            while (fread(&bok, sizeof(bok), 1, fp) == 1)
            {
                if (bok.cur_Student != id or bok.book_no != bn)
                {
                    fwrite(&bok, sizeof(bok), 1, fp1);
                }
                else
                {
                    flag1 = true;
                }
            }
            flag2 = true;
            break;
        }
    }

    if (!flag2)
    {
        cout << " This Student not Found !!! " << endl;
    }
    else if (!flag1)
    {
        cout << " This Book not Found !!! " << endl;
    }
    else
    {
        cout << " Book Return Successfully " << endl;
    }

    fclose(fp);
    fclose(fp1);
    remove("libBookStore.txt");
    rename("libBookStorenew.txt", "libBookStore.txt");
    system("pause");
}

void Librarian_Menu()
{
    bool choose = true;
    int ch;

    while (choose)
    {
        cout << " 1 : Create Student :" << endl
             << endl;
        cout << " 2 : Remove Student :" << endl
             << endl;
        cout << " 3 : Issue Books :" << endl
             << endl;
        cout << " 4 : Return Books :" << endl
             << endl;
        cout << " 5 : List of Students :" << endl
             << endl;
        cout << " 6 : Books Details :" << endl
             << endl;
        cout << " 7 : Search Books :" << endl
             << endl;
        cout << " 8 : Back From This Menu :" << endl
             << endl;

        cout << " Enter the choice at (1-8) ::" << endl;
        cin >> ch;
        system("cls");
        switch (ch)
        {

        case 1:
        {

            Create_Student();
        }
        break;

        case 2:
        {
            Remove_Student();
        }
        break;

        case 3:
        {
            Issue_Book();
        }
        break;

        case 4:
        {
            Return_Book();
        }
        break;

        case 5:
        {
            List_Of_Student();
        }
        break;

        case 6:
        {
            Book_Detail();
        }
        break;
        case 7:
        {
            Search_Book();
        }
        break;
        default:
        {
            choose = false;
            cout << " exit ";
        }
        }
        system("cls");
    }
}

void Search_Student()
{
    Student stu;
    FILE *fp;
    int i = 1, id;
    bool flag;
    fp = fopen("libStudent.txt", "rb");
    if (!fp)
    {
        cout << " error ";
        return;
    }

    cout << " Enter the Id/Roll no. of Student :-" << endl;
    cin >> id;

    while (fread(&stu, sizeof(stu), 1, fp) == 1)
    {
        if (id == stu.id)
        {
            cout << " Student " << id << " Found :" << endl
                 << endl;
            cout << " Name : " << stu.name << endl
                 << endl;
            cout << " Roll No : " << stu.id << endl
                 << endl;
            cout << " Date Of Registraction : " << stu.dd << " \\ " << stu.mm << " \\ " << stu.yy << endl
                 << endl;
            flag = true;
        }
    }

    if (!flag)
    {
        cout << " Student Not Found " << endl;
    }
    fclose(fp);
    system("pause");
}

void Update_Student_Date()
{
    Student stu;
    FILE *fp;
    int i = 1, id;
    bool flag;
    fp = fopen("libStudent.txt", "rb+");

    if (!fp)
    {
        cout << " error ";
        return;
    }

    cout << " Enter the Id/Roll no. of Student :-" << endl;
    cin >> id;
    bool flag2 = true;
    while (fread(&stu, sizeof(stu), 1, fp) == 1)
    {
        if (id == stu.id)
        {
            int ch;
            cout << " Student Name : " << stu.name << endl
                 << endl;
            cout << " 1 : Update Name :-" << endl
                 << endl;
            cout << " 2 : Update Branch :-" << endl
                 << endl;
            cout << " 3 : Update Address :-" << endl
                 << endl;
            cout << " 4 : Update Age :-" << endl
                 << endl;
            cout << " 5 : Back form the Menu :-" << endl
                 << endl;

            cout << " Enter the choice at (1-5) ::" << endl;
            cin >> ch;

            switch (ch)
            {
            case 1:
            {
                cout << " Enter the Name " << endl;
                getchar();
                gets(stu.name);
            }
            break;
            case 2:
            {
                cout << " Enter the Id " << endl;
                cin >> stu.id;
            }
            break;
            case 3:
            {
                cout << " Enter the Branch " << endl;
                cin >> stu.branch;
            }
            break;
            case 4:
            {
                cout << " Enter the Age " << endl;
                cin >> stu.age;
            }
            break;
            default:
            {
                cout << " Exit ";
                flag2 = false;
            }
            }

            fseek(fp, -(long)sizeof(stu), 1);
            fwrite(&stu, sizeof(stu), 1, fp);
            flag = true;
            break;
        }
    }

    if (!flag)
    {
        cout << " Student Not Found " << endl;
    }
    fclose(fp);
    system("pause");
}

void Book_Detail_of_Student()
{
    Student stu;
    Book bok;
    FILE *fp, *fb;
    int i = 1, id;
    bool flag;
    fp = fopen("libStudent.txt", "rb");
    fb = fopen("libBookStore.txt", "rb");
    if (!fp)
    {
        cout << " error ";
        return;
    }

    cout << " Enter the Id/Roll no. of Student :-" << endl;
    cin >> id;

    while (fread(&stu, sizeof(stu), 1, fp) == 1)
    {
        if (stu.id == id)
        {
            cout << " Name : " << stu.name << endl
                 << endl;
            while (fread(&bok, sizeof(bok), 1, fb) == 1)
            {
                if (bok.cur_Student == id)
                {
                    cout << " Book Name : " << bok.title << "\t Book Number : " << bok.book_no << endl
                         << endl;
                }
            }
            flag = true;
            break;
        }
    }

    if (!flag)
    {
        cout << " Student not Found !!!" << endl;
    }
    fclose(fp);
    fclose(fb);
    system("pause");
}

void Student_Menu()
{
    bool choose = true;
    int ch;

    while (choose)
    {
        cout << " 1 : Search Student :" << endl
             << endl;
        cout << " 2 : Update Student Data :" << endl
             << endl;
        cout << " 3 : Books Details of Student :" << endl
             << endl;
        cout << " 4 : List of Students :" << endl
             << endl;
        cout << " 5 : Back From This Menu :" << endl
             << endl;

        cout << " Enter the choice at (1-5) ::" << endl;
        cin >> ch;
        system("cls");
        switch (ch)
        {

        case 1:
        {
            Search_Student();
        }
        break;

        case 2:
        {
            Update_Student_Date();
        }
        break;

        case 3:
        {
            Book_Detail_of_Student();
        }
        break;

        case 4:
        {
            List_Of_Student();
        }
        break;

        default:
        {
            cout << " Exit ";
            choose = false;
        }
        }
        system("cls");
    }
}

int main()
{
    system("cls");
    bool choose = true;
    int ch;

    while (choose)
    {
        cout << "<<<<<---- LIBRARY MANAGEMENT SYSTEM ---->>>>> " << endl
             << endl;
        cout << " 1 : LIBRARIAN " << endl;
        cout << " 2 : STUDENT  " << endl;
        cout << " 3 : EXIT " << endl;

        cout << " Enter the choice :" << endl;
        cin >> ch;

        switch (ch)
        {
        case 1:
        {
            system("cls");
            cout << " <<<<<----  LIBRARIAN  ---->>>>> " << endl
                 << endl;
            Librarian_Menu();
            system("cls");
        }
        break;

        case 2:
        {
            system("cls");
            cout << " <<<<<----  STUDENT  ---->>>>> " << endl
                 << endl;
            Student_Menu();
            system("cls");
        }
        break;

        case 3:
        {
            cout << " <<<<<----  EXIT  ---->>>>> " << endl
                 << endl;
            choose = false;
        }
        break;

        default:
        {
            system("cls");
            cout << " Your choice is INVALID!!! PLEASE select a valid option " << endl;
        }

        } // end switch
    }     // end while(choose)

    cout << " <<<<---- THANK YOU FOR VISITING ---->>>> ";
    return 0;
}
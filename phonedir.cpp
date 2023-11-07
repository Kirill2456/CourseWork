#include <iostream>
#include <string>
#include <fstream>
#include <list>

using namespace std;

struct Sub
{
string surname;
string phone_number;

};

list<Sub> lst;

ifstream& operator>> (ifstream &in, Sub &obj)
{
in >> obj.surname;
in >> obj.phone_number;
return in;
}

istream& operator>> (istream &in, Sub &obj)
{
cout << "Add new entries:\n\n";
cout << "Full name: "; in >> obj.surname;
cout << "Phone number: "; in >> obj.phone_number;
return in;
}

ostream& operator<< (ostream &out, Sub &obj)
{
out << obj.surname << "\n";
out << obj.phone_number <<"\n";
return out;
}
//////////////////////////////////////////////
void clear()
{
ofstream in("input.txt", ios::out | ios::trunc);
in.close();
}
//////////////////////////////////////////////
bool is_file_empty()
{
ifstream in ("input.txt");
in.seekg(0,ios::end);
if (in.tellg()==0)
{
return true;
}
in.close();
return false;
}
//////////////////////////////////////////////
void save_into_file()
{
clear();
ofstream out("input.txt");
for (const Sub &data : lst)
{
out << data.surname <<"\n";
out << data.phone_number <<"\n";
}
out.close();
}
//////////////////////////////////////////////
void read_from_file(Sub &data)
{
ifstream in("input.txt");
while (in >> data)
{
lst.push_back(data);
}
in.close();
}
//////////////////////////////////////////////
void output_from_file(Sub &data)
{
if (!is_file_empty())
{
ifstream in ("input.txt");
if (in)
{
int k = 0;
while (in >> data)
{
k++;
cout << "Write # " << k << ":\n\n";
cout << data;
cout << "\n";
}
in.close();
}
else
{
cout << "File input.txt not found!!!\n\n";
}
}
else
{
cout << "File input.txt zero entryes!!!\n\n";
}
}

//////////////////////////////////////////////
void add_client(Sub &data)
{
int k;
cout << "print count entry: ";
cin >> k;
for (int i=1; i<=k; i++)
{
cout << "\nEntry #" << i << ":\n";
cin >> data;
lst.push_back(data);
}
cout << "\n good entry!\n\n";
save_into_file();
}
//////////////////////////////////////////////
void del_client(string const &key)
{
bool flag = false;
for (auto it = lst.begin(); it!= lst.end();)
{
if (it->surname == key)
{
it = lst.erase(it);
flag = true;
}
else
{
it++;
}
}
if (!flag)
{
cout << "\nNo record with this name found!!!\n\n";
return;
}
else
{
cout << "\nEntries deleted OK!!!\n\n";
}
save_into_file();
}
//////////////////////////////////////////////
void output_client()
{
ifstream in("input.txt");
bool flag = false;
string digits;
cout << "Enter two phone number digits: ";
cin >> digits;
for (auto it = lst.begin(); it != lst.end(); ++it)
{
if (it->phone_number.find(digits)==0)
{
cout << it->surname << "\n";
cout << it->phone_number << "\n";
flag = true;
}
}
in.close();
if (!flag)
{
cout << "not found!!\n\n";
}
}
//////////////////////////////////////////////
void replace_client(string const &key)
{
int k = 0;
for (auto it = lst.begin(); it!=lst.end(); ++it)
{
if (it->surname == key)
{
k++;
cout << "entries #" << k << ":\n";
cout << it->phone_number << " => ";
cin >> it->phone_number;
it->phone_number = it->phone_number;
cout << "\n";
}
}
if (!k)
{
cout << "\nNo record with this name found!!!\n\n";
return;
}
else
{
cout << "\nEntries deleted OK!!!\n\n";
}
save_into_file();
}

//////////////////////////////////////////////
int main()
{
Sub person;
read_from_file(person);
menu:
int choice,back;
string surname;
cout << "Select an action\n\n";
cout << "0 - Exit\n";
cout << "1 - Add new entry\n";
cout << "2 - Delete entry\n";
cout << "3 - Change phone number\n";
cout << "4 - List of clients\n";
cout << "5 - Displaying information about all clients\n";
cout << "Your choice\n";
cin >> choice;
cout << endl;

switch (choice)
{
case 0:
exit(0);
break;
case 1:
add_client(person);
break;
case 2:
cout << "Print Full name :\n";
cin >> surname;
del_client(surname);
break;
case 3:
cout << "Print Full name :\n";
cin >> surname;
cout <<"\n";
replace_client(surname);
break;
case 4:
output_client();
break;
case 5:
output_from_file(person);

default :
cout << "item selected incorrectly\n";
} 
cout << "Do you want to return to the MENU???\n";
cout << "1 - Yes\n";
cout << "2 - No\n";
cout << "You choice: ";
cin >> back;
if (back == 1)
{
system("cls");
goto menu;
}
else
{
exit(0);
}
system("pause");
return 0;
}

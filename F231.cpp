#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

class student
{
	typedef struct stud
	{
		int roll; 
		char name[10];
		char div;
		char add[10];
		
	}stud;
	stud rec;
	
	public:
		void create();
		void display();
		int search();
		void Delete();
};

void student :: create()
{
	char ans;
	ofstream fout;
	fout.open("stud.dat",ios :: out | ios :: binary);
	do
	{
		cout<<"\n\t Enter Roll no of student: ";
		cin>>rec.roll;
		cout<<"\n\t Enter a name of student: ";
		cin>>rec.name;
		cout<<"\n\t Enter a div of student: ";
		cin>>rec.div;
		cout<<"\n\t Enter a address of student: ";
		cin>>rec.add;
	}while(ans == 'y' || ans == 'Y');
	fout.close();
}

void student :: display()
{
	ifstream fin;
	fin.open("stude.dat", ios::in | ios :: binary);
	fin.seekg(0, ios::beg);
	cout<<"\n\t The content of the file are: \n";
	cout<<"\n\t Roll\tName\tDIv\t\tAddress: ";
	while(fin.read((char*)&rec, sizeof(stud)))
	{
		if(rec.roll != -1)
			cout<<"\n\t"<<rec.roll<<"\t"<<rec.name<<"\t"<<rec.div<<"\t"<<rec.add;
	}
	fin.close();
}

int student :: search()
{
	int r,i=0;
	ifstream fin;
	fin.open("stud.dat", ios::in | ios::binary);
	fin.seekg(0, ios::beg);
	cout<<"\n\t Enter a roll no: ";
	cin>>r;
	while(fin.read((char*)&rec, sizeof(stud)))
	{
		if(rec.roll == r)
		{
			cout<<"\n\t Record Found....\n";
			cout<<"\n\t Roll\tName\tDiv\tAddress";
			cout<<"\n\t"<<rec.roll<<"\t"<<rec.name<<"\t"<<rec.div<<"\t"<<rec.add;
			return i;
		}
		i++;
	}
	fin.close();
	return 0;
}

void student :: Delete()
{
	int pos;
	pos = search();
	fstream f;
	f.open("stud.dat", ios::in | ios::out | ios::binary);
	f.seekg(0, ios::beg);
	if(pos == 0)
	{
		cout<<"\n\t Record Not Found";
		return;
	}
	int offset = pos*sizeof(stud);
	f.seekp(offset);
	rec.roll;
	strcpy(rec.name, "NULL");
	rec.div = 'N';
	strcpy(rec.add, "NULL");
	f.write((char*)&rec, sizeof(stud));
	f.seekg(0);
	f.close();
	cout<<"\n\tRecord Deleted";
}

int main()
{
	student obj;
	int ch, key;
	char ans;
	
	do
	{
		cout << endl;
        cout << "--- MAIN MENU ---" << endl;
        cout << "1 -> Add record" << endl;
        cout << "2 -> Delete record" << endl;
        cout << "3 -> Search record" << endl;
        cout << "4 -> Display all records" << endl;
        cout << "5 -> Exit" << endl << endl;
        cout << "Choose an option (0-4):\t";
        cin >> ch;
        switch (ch) 
        {
        	case 1: obj.create();
        		break;
    		case 2: obj.display();
    			break;
			case 3: obj.Delete();
				break;
			case 4:
				key = obj.search();
				if(key == 0)
				break;
			case 5:
				break;			
		}
		cout<<"\n\t.....Do you Want to CONTINUE(y/Y)";
		cin>>ans;
	}while(ans == 'y' || ans == 'Y');
	
	return 1;
}

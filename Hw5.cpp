// Rohan Uppuluri
// Hw5.cpp: Main file for Hw 5

#include <iostream>
#include "HashedDictionary.h"
#include "Toy.h"

// displayKey: displays the unique key, the name of each toy
void displayKey(string &s)
{
    cout<<s<<endl;
}

// displayItems: displays the unique key with indenting
void displayItems(string &s,int spaces,int index)
{
    if(index != -1)
        cout<<"Index "<<index<<": "<<s<<endl;
    else
    {
        string str = "Index :";
        str += index;

        int k = str.length();


        for(int i=0;i<spaces+k+1;i++)
        {
            cout<<" ";
        }
        cout<<s<<endl;
    }

}

bool readFile(string fileName,HashedDictionary<string,Toy> *hashTable);
void showMenu(HashedDictionary<string,Toy> *hashTable);

int main()
{
    HashedDictionary<string,Toy> *hashTable = new HashedDictionary<string,Toy>(31);

    bool success = readFile("toys.txt",hashTable);

    showMenu(hashTable);

    delete hashTable;

    return 0;
}

// readFile: reads the input file and adds inputted items into hash table and creates an output file for rejected items
bool readFile(string fileName,HashedDictionary<string,Toy> *hashTable)
{
    ifstream infile;
    infile.open(fileName);
    if(!infile)
    {
        cout<<"Error opening input file "<<endl;
        return false;

    }

    ofstream ofile;
    ofile.open("rejected.txt");
    if(!ofile)
    {
        cout<<"Error opening output file "<<endl;
        return false;
    }

    string line;
    while(getline(infile,line))
    {

        string name;
        double age;
        double price;
        string award;
        unsigned long index1 = line.find(';');
        name = line.substr(0,index1);
        index1 = line.find(' ',index1);
        unsigned long index2 = line.find(' ',index1+1);
        string temp = line.substr(index1,index2-index1);
        age = stod(temp);
        index1 = line.find(' ',index2);
        index2 = line.find(' ',index1+1);

        temp = line.substr(index1,index2-index1);
        price = stod(temp);

        award = line.substr(index2,line.length());



        Toy t1(name,age,price,award);
        if(!hashTable->add(name,t1))
        {

        }else{
            cout<<"Accepted"<<name<<endl;
        }
    }
    ofile.close();
    infile.close();
    return true;
}

// showMenu: displays the menu options to user
void showMenu(HashedDictionary<string,Toy> *hashTable)
{
    bool done = false;

    cout<<"\n\n";

    cout<<"(S)Search by name"<<endl;
    cout<<"(D)Display list"<<endl;
    cout<<"(P)Print the hashed table"<<endl;
    cout<<"(T)Show statistics"<<endl;
    cout<<"(M)Show Menu"<<endl;
    cout<<"(Q)Quit"<<endl;

    do
    {
        char option;
        cout<<"\nSelect Option :";
        cin>>option;

        //cin.clear();
        option = tolower(option);
        switch(option)
        {
            case 's':
            {
                string key;
                cout<<"Enter Key to search :";
                cin.ignore();
                getline(cin,key);
                Toy * found = hashTable->getItem(key);
                if(found)
                {
					cout << "Found Item: " << found->getName() << "; " << found->getAge() << " " << found->getPrice() << " " << found->getAward() << endl;
                }
                else
                    cout<<"Key not found "<<endl;


                break;
            }
            case 'm':
            {
                cout << "(S)Search by name" << endl;
                cout << "(D)Display list" << endl;
                cout << "(P)Print the hashed table" << endl;
                cout << "(T)Show statistics" << endl;
                cout << "(M)Show Menu" << endl;
                cout << "(Q)Quit" << endl;
                break;
            }
            case 'p':
            {
                cout << endl;
                hashTable->printHashTable(displayItems);

                break;
            }
            case 'd':
            {
                cout << endl;
                hashTable->displayHashTableList(displayKey);

                break;
            }
            case 't':
            {
                int c = hashTable->getColissions();
                int full = hashTable->getNumOfFullBuckets();
                int empty = hashTable->getNumOfEmptyBuckets();

                cout<<endl<<"Statistics:"<<endl;
                cout<<"Number of Collisions at Index 1 :"<<hashTable->getColissionsAtIndex(1)<<endl;


                cout << "Total number of Collisions: " << hashTable->getColissions() << endl;

                cout << "Load Factor: " << hashTable->getLoadFactor() << "%" << endl;

                cout<<"Number of Full Buckets:  "<<full<<endl;
                cout<<"Number of Empty Buckets:  "<<empty<<endl;
                cout<<"Average Number of nodes stored per bucket: "<<hashTable->getAverageNumofNodes()<<endl;


                break;
            }
            case 'q':
            {
                ifstream infile;
                infile.open("rejected.txt");

                if(!infile)
                {
                    cout<<"Error opening input file "<<endl;

                }
                else
                {
                    string line;
                    cout<<"Rejected - "<<endl;
                    while(getline(infile,line))
                    {
                        cout<<line<<endl;

                    }
                }
                done = true;
                break;
            }

            default:
                cout<<"Incorrect option try again "<<endl;
                break;

        }
    }while(!done);
}

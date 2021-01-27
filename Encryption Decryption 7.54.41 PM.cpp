//
//  main.cpp
//  encryptFinalCode
//
//  Created by Tushar Pandey on 21/04/18.
//  Copyright © 2018 Tushar Pandey. All rights reserved.
//


/*
this version takes in text input from the console itself. The user has to input th text specifically, but has the facility to use all the punctuaton and
other text formatting styles that are in use in normal text writing styles.
in order to teminate te text typing process, you have to spontaneously input the escape sequence text predecided by you.
*/
//#include<iostream>                                            //no iostream needed, we are including the fstream file already
//#include<theconio.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
//#include<cstdlib>                                             //no effect on the existing code, maybe earlier it was usefull

/* using std::cout;
using std::cin;
//using std::endl;                                              // obsolete, i don't use it.
using std::string;
using std::ofstream;
using std::ifstream;
*/
class passkey
{				//we dont need any class to run the program actually.


private:
    std::string password="noidavilla";
    int key;

public:
    passkey();
    void getkey();
    friend void encrypt(passkey);                               //friend function for encrypt
    friend void decrypt(passkey);                               //friend function for decryption

}file1;                                                         //global object of the passkey class

passkey::passkey()                                              //constructor initialising the password
{
    key=0;

}

void passkey::getkey()                                          //taking the password from user
{
    cout << "\nEnter the key: ";
    cin >> key;
    std::cin.clear();                                           //to clear the cin stream buffer
}

char filenaam[40];                                              //space for the name of file

/*****************************************************************************************************************************************************************
*********************************************************************MAIN Program********************************************************************************
*****************************************************************************************************************************************************************/
int main()
{
    int a, pw, x, k;                                            //pw for password
    //string c;                                                 //user string c
    char sample,escapeSequence[6];                              //to input file,char by char from user
    cout<<"\nEnter the correct password: ";
    cin>>pw;
    if(pw!=100)
    {
        cout<<"\nSorry you entered the wrong password" << endl;
        getch();
        return 0;
    }
    cout<<"\nFor ENCRYPTION enter 1\nFor DECRYPTION enter 2\nTo terminate the program enter 3" << endl;
    cin>> a;
    if(a==1)
    {
        file1.getkey();                                         //authentication

        cout<<"\nGive your file a name\neg: \'Input_Data\'";
        cin >> filenaam;
        strcat(filenaam,".txt");
        cout<<"\nPlease enter an escape sequence, a maximum 5 character word, enter '\n' if you have no special choice.";
        cin>>escapeSequence;                                    //getting the escape sequence
        for (int i = 0; i < 6; ++i)
        {
            cout<<"\n"<<escapeSequence[i];
        }
        cout<<"\nEnter data to the file\n";
        getInput(sample,escapeSequence);              //a target character to receive line & another character array
                                                                //listing the escape expression ,less that 5 effective characters



        inputData.close();
        encrypt(file1);                                         //calling encrypt function
        getch();

        return 0;
    }
    else if(a==2)
    {
        file1.getkey();

        cout<<"\nEnter name of your file\neg: Input_Data.txt" << endl;
        cin >> filenaam;
        strcat(filenaam,".txt");
        decrypt(file1);
        getch();

        return 0;
    }
    else if (a==3)
    {
        return 0;
    }
}

/*****************************************************************************************************************************************************************
*********************************************************************EndOfMain***********************************************************************************
*****************************************************************************************************************************************************************/
void encrypt(passkey file)
{
    char encfilenaam[50] = "Encrypted_";
    strcat(encfilenaam,filenaam);

    int n;

    srand(file.key);

    ifstream OutputData(filenaam);

    char ch[50] = "";

    ofstream inputData(encfilenaam);

    OutputData.getline(ch,49);
    do
    {
        n= 1+rand()%9;
        for(int i=0; i<strlen(ch); i++)
        {
            ch[i] = ch[i] + n;                                  //adding
        }
        inputData << ch;
    }
    while(OutputData.getline(ch,49));

    OutputData.close();
    inputData.close();

    cout << "File is successfully encrypted"  << endl;
    cout << "Encrypted data is stored in file with name: " << encfilenaam << endl;
}

void decrypt(passkey file)
{
    char decfilenaam[50] = "Decrypted_";
    strcat(decfilenaam,filenaam);

    int m;

    srand(file.key);                                            //default seeding starts with key value

    ifstream OutputData(filenaam);                              //ifstream It is used for reading input from the file

    char ch[50] = "";

    ofstream inputData(decfilenaam);                            //putting data back into the file

    OutputData.getline(ch,49);
    do
    {
        m= 1 + rand()%9;                                        //formula is going to be same for both encryption and decryption
        for(int i=0; i<strlen(ch); i++)
        {
            ch[i] = ch[i] - m;                                  //subtracting
        }
        inputData << ch;
    }
    while(OutputData.getline(ch,49));

    OutputData.close();
    inputData.close();

    cout << "File successfully decrypted" << endl;
    cout << "Decrypted text is stored in " << decfilenaam << endl;


}
void getInput(char sample,char escapeSequence[])
{
    ofstream inputData(filenaam);                           //inputData object to send data to the file
    int flag=0;
    while(getch(sample)!='&')
    {
        flag=1;
        inputData<<sample;

    }
    if (flag==0)
    {
        char testEscape[6];
        testEscape[0]='&';
        cin>>testEscape[1];
    }
}

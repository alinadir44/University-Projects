#include<iostream>
#include<string.h>
#include<cstring>
#include<cctype>
#include<cstdio>
#include<stdlib.h>
#include<Windows.h>
using namespace std;
int main()
{
	
	char n1[50],n2[]="ali nadir";
	cout << "Enter a name: ";
	cin.getline(n1,50);
	for (int i=0;i<strlen(n1);i++)
	{
		n1[i]=tolower(n1[i]);
	}
	Sleep(500);
	cout << "\nname: " << n1;
	if(strcmp(n1,n2)==0)
	cout << "\nchosen one!";
	else
	cout << "\npathetic";
}

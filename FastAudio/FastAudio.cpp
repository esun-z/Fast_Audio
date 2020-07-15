// FastAudio.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <conio.h>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
//#pragma comment(lib, "winmm.lib")            //For MCI(Media Control Interface，媒体控制接口)
#pragma warning(disable : 4996)
using namespace std;
#define LODATA 512
#define LOLIST 128


struct node1 {
	char file_name[LODATA];
	int key;
};
node1 file_list[LOLIST];
node1 adding;
node1 deleting;

char com[LODATA],rubbish[LODATA];

int kbcd,ch,num;

int lolist;

bool same(char a[], char b[]) {
	if (strcmp(a, b) == 0) {
		return true;
	}
	else {
		return false;
	}
}


void readfilelist(node1 file_list[LODATA]) {
	//read file list from file_list.txt
	freopen("file_list.txt", "r", stdin);
	scanf("%d", &lolist);
	for (int i = 0; i < lolist; ++i) {
		cin.getline(rubbish, LODATA);
		cin.getline(file_list[i].file_name,LODATA);
		scanf ("%d",&file_list[i].key);
	}
	if (lolist == 0) {
		cout << "\nNo file has been found.\nYou need to add some files first\n";
	}
	else {
		cout << "\nFile reading finished.\n" << lolist << " file(s) has been loaded.\n";
	}
	freopen("CON", "r", stdin);
	return;
}

void printfilelist() {
	//print file list to CON
	cout << "\nShowing file list\nLongth of file list : " << lolist << "\n";
	cout << "\nnumber	file_name	key\n";
	for (int i = 0; i < lolist; ++i) {
		cout << i+1 << "	" <<file_list[i].file_name << "	" << file_list[i].key << "\n";
	}
	cout << "\nList showing finished\n";
	return;
}

void writefilelist() {
	//write file list
	freopen("file_list.txt", "w", stdout);
	cout << lolist ;
	for (int i = 0; i < lolist; ++i) {
		cout <<"\n"<< file_list[i].file_name << "\n" << file_list[i].key ;
	}
	freopen("CON", "w", stdout);
	cout << "\nList writing finished\n";
	return;
}

void addtolist(char name[LODATA],int key){
	// add a file to the list
	strcpy(file_list[lolist].file_name, name);
	file_list[lolist].key = key;
	cout << "\nFile adding finished\nName = " << file_list[lolist].file_name << "	key = " << file_list[lolist].key << "\n";
	lolist++;
	writefilelist();
	return;
}

void helplist() {
	cout << "\nType main to enter the main function\nType print to show the file list\nType add to add file(s)\nType delete to delete file(s) (only from the list)\n";
	return;
}

void deletefromlist(int n/*,node1 file_liset[]*/) {
	n--;
	lolist--;
	for (int i = n; i < lolist; ++i) {
		file_list[i] = file_list[i + 1];
	}
	strcpy(file_list[lolist].file_name, "");
	file_list[lolist].key = 0;
	cout << "File deleted.";
	writefilelist();
	return;
}


void mainfunction() {
	
	while (1) {
		
		if (KEY_DOWN(27) && LEFT_CTRL_PRESSED && kbcd <= 10) {
			break;
			//kbcd += 50;
		}
		
		
		if (kbcd <= 10) {
			for (int i = 0; i < lolist; ++i) {
				if (KEY_DOWN(file_list[i].key)) {
					cout << file_list[i].file_name << "\n";
					system(file_list[i].file_name);
					kbcd += 25;
					break;
				}
			}
		}
		if (kbcd > 0) {
			kbcd--;
		}
		
		Sleep(20);
	}
	return;
}




int main()
{
	readfilelist(file_list);
	
	cout << "Type help to see the help list \nType main to enter the main function\n";

	while (1) {
		//main CON loop

		scanf("%s", com);

		if (same(com, "main")) {
			if (lolist > 0) {
				cout << "\nEnter main function\n";
				mainfunction();
			}
			else {
				cout << "\nNo file has been found.\nYou need to add some files first\n";
			}
		}
		else if (same(com, "add")) {
			cout << "\nEnter file name :\n";
			scanf("%s", com);
			cout << "\nNow Press the key you want to link with the file\n";
			Sleep(100);
			bool flagbreak;
			while (1) {
				for (int i = 0; i<256; ++i) {
					if (KEY_DOWN(i)) {
						//cout << i << "	";
						ch = i;
						flagbreak = true;
						break;
					}
				}
				if (flagbreak == true) {
					flagbreak = false;
					break;
				}
				Sleep(20);
			}
			cout << "Name = " << com << "	" << "key = " << ch;
			cout << "\nType 1 to continue";
			cout << "\nType any other number to cancel\n";
			scanf("%d", &num);
			if (num == 1) {
				addtolist(com, ch);
			}
			else {
				cout << "\nCanceled\n";
			}
		}
		else if (same(com, "delete")) {
			printfilelist();
			cout << "Now type the number before file that you want to delete from the list : \n";
			scanf("%d", &ch);
			cout << "Ready to delete the file : " << file_list[ch-1].file_name << "\n";
			cout << "Type 1 to delete the file;\nType any other number to cancel.\n";
			scanf("%d", &num);
			if (num == 1) {
				deletefromlist(ch);
			}
			else {
				cout << "\nCanceled\n";
			}
		}
		else if (same(com, "print")) {
			printfilelist();
		}
		else if (same(com, "exit") || same(com, "esc") || same(com, "quit") || same(com, "escape")) {
			break;
		}
		else if (same(com, "help") || same(com, "Help")) {
			helplist();
		}
		else {
			cout << "Unknown command.\nType help to get all the commands.\n";
		}

	}
	

	return 0;
}

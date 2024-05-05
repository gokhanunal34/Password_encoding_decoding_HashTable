//
// Created EMPTY by Gokhan Unal 3/25/2024
// Referenced from homework insturctions on 3/29/2024
// All function descriptions are in the .cpp file; I like my .h files clean
// without comments but if I am wrong in adopting this style, please let me know.
//
#ifndef PASSSERVER_H
#define PASSSERVER_H
#include "hashtable.h"
#include<iostream>
#include<stdio.h>
#include "base64.h"
#include <cstring>

const int MAXSIZE = 256;
using namespace std;
using namespace cop4530;

class PassServer
{
public:
	PassServer(size_t serverSize = 101);
	~PassServer();
	bool load(const char* filename);
	bool addUser(pair<string, string>& kv);
	bool addUser(pair<string, string>&& kv);
	bool removeUser(const string& k);
	bool changePassword(const pair<string, string>& p, const string& newpassword);
	bool find(const string& user);
	void dump();
	size_t size();
	bool write_to_file(const char* filename);
private:
	string encrypt(const string& str);
	//string decrypt(const string& str);
	HashTable<string, string> newhtable;
};
#endif//PASSSERVER_H end

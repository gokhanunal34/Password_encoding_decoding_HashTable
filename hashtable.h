//
// Created by Gokhan Unal 3/25/2024
// Referenced from Dr. Gaitros' video and homework insturctions
//
#ifndef HASHTABLE_H
#define HASHTABLE_H
#include<vector>
#include<list>
#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<algorithm>
#include<cctype>
#include<utility>
#include<iterator>
#include "base64.h"

using namespace std;
namespace cop4530
{
	template<typename K, typename V>
	class HashTable
	{
	public:
		//this type of iterator is not used, but I am still keeping it.
		//It displays my battle with decoding process. I was in the brink of 
		//writing my own operator overloads to make this thing work which would
		// :) 
		//using iterator = std::list<std::pair<std::string, std::string>>::iterator;
		
		size_t MAXTABLESIZE = 101;
		const int MAXSIZE = 256;

		HashTable(size_t size = 101);
		~HashTable();
		bool contains(const K& k) const;
		bool match(const std::pair<K, V>& kv) const;
		bool insert(const std::pair<K, V>& kv);
		bool insert(std::pair<K, V>&& kv);
		bool remove(const K& k);
		void clear();
		bool load(const char* filename);
		void dump() const;
		bool write_to_file(const char* filename) const;
		void resizeServer(size_t size);//public so that I can access it from passserver
		int numUserPair() const;
		int VecSize() const;
		//inline begin() and end()
		//not used, but displays my battle with the decode, I will keep these
		//as battle trophies :D
		//iterator begin() { return htable.begin(); }
		//iterator end() { return htable.end(); }

	private:
		//string decrypt(const string& str);
		size_t myhash(const K& k) const;
		std::vector< std::list< std::pair<K, V> > > htable;
		int htSize = 0;
		int vecSize = 0;
		void makeEmpty();
		void rehash();
		unsigned long prime_below(unsigned long);
		void setPrimes(std::vector<unsigned long>&);
		static const unsigned int max_prime = 1301081;
		static const unsigned int default_capacity = 11;
	};//class HashTable<K,V>

#include "hashtable.hpp"
}//namespace bracket
#endif
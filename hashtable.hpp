#include "hashtable.h"

using namespace cop4530;//Visual studio 2022 community addition doesn't let
//me compile this without declaring the namespace. In linprog it didn't 
// matter whether I declared the namespace in the hpp or not. 

// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below(unsigned long n)
{
	if (n > max_prime)
	{
		std::cerr << "** input too large for prime_below()\n";
		return 0;
	}
	if (n == max_prime)
	{
		return max_prime;
	}
	if (n <= 1)
	{
		std::cerr << "** input too small \n";
		return 0;
	}

	// now: 2 <= n < max_prime
	std::vector <unsigned long> v(n + 1);
	setPrimes(v);
	while (n > 2)
	{
		if (v[n] == 1)
			return n;
		--n;
	}

	return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K, V>::setPrimes(vector<unsigned long>& vprimes)
{
	int i = 0;
	int j = 0;

	vprimes[0] = 0;
	vprimes[1] = 0;
	int n = vprimes.capacity();

	for (i = 2; i < n; ++i)
		vprimes[i] = 1;

	for (i = 2; i * i < n; ++i)
	{
		if (vprimes[i] == 1)
			for (j = i + i; j < n; j += i)
				vprimes[j] = 0;
	}
}
// *********************************************************************************
// * Some assumptions: Each line is limited to 85 characters for consistency and   *
// * readability. I also left some functions and processes commented out because   *
// * I want to work on this project later on to implement it in a better way. So   *
// * I humbly ask for your forgiveness on those comment outs, I know it takes away *
// * the clean look.                                                               *
// * I am trying to write a primitive contract management program for my lawyer    *
// * friend overseas, and this program will help me a lot in writing the login     *
// * logout process in that program. I know it is an impossible feat to write      *
// * software by myself but I will keep writing it to my best abilities.           *
// * ANY usage of auto& iterator, itr->first and second                            *
// * or htable[].first and second;and other vector and pair nuances                *
// * are first learned from Dr. Gaitros' list of pairs video.                      *
// * His other videos for this module also inspired blocks of code, updates and    *
// * modifications.                                                                * 
// * Bugs to be fix as of 4/2/2024: Linprog doesn't decode the last user for       *
// * some reason yet if I run the same code on Visual Studio 2022, it decodes      *
// * the last user/password too.                                                   *
// * UPDATE: Dr. Gaitros changed the instructions so the bug needs not to be fixed * 
// *********************************************************************************

// *********************************************************************************
// * Function Name: HashTable(size_t size = 101)                                   *
// * Description:constructor. Create a hash table, where the size of the vector is *
// * set to prime_below(size) (where size is default to 101), where                *
// * prime_below() is a private member funct of the HashTable and provided to you. *
// * Date: 3/25/2024                                                               *
// * Author: Gokhan Unal                                                           *
// * References:Instructions above:)                                               *
// *********************************************************************************
template<typename K, typename V>
HashTable<K, V>::HashTable(size_t size)
{
	htable.resize(prime_below(size));
	htSize = 0;
}

// *********************************************************************************
// * Function Name: ~HashTable()                                                   *
// * Description:Destructor. Deletes all elements in hash table. Calls public      *
// * helper clear() which calls the private helper makeEmpty() as discussed in the *
// * in 3/25/2024 class.                                                           *
// * Date: 3/25/2024                                                               *
// * Author: Gokhan Unal                                                           *
// * References: N/A                                                               *
// *********************************************************************************
template<typename K, typename V>
HashTable<K, V>::~HashTable()
{
	clear();
}

// *********************************************************************************
// * Function Name: clear()                                                        * 
// * Description: Deletes all elements in hash table. Calls private helper         *
// * makeEmpty()                                                                   *
// * Date: 3/25/2024                                                               *
// * Author: Gokhan Unal                                                           *
// * References: N/A                                                               *
// *********************************************************************************
template<typename K, typename V>
void HashTable<K, V>::clear()
{
	makeEmpty();
}

// *********************************************************************************
// * Function Name: int getsize() const                                            * 
// * Description: Returns the actual hashtable size, not the vector size           *
// * Date: 3/25/2024                                                               * 
// * Author: Gokhan Unal                                                           *
// * References: Dr. Gaitros' implementation took track of the size of the actual  * 
// * hashtable as well, so will I.                                                 *
// *********************************************************************************
template<typename K, typename V>
int HashTable<K, V>::numUserPair() const
{
	return htSize;
}

// *********************************************************************************
// * Author: Gokhan Unal                                                           *
// * Function name: VecSize() const                                                *
// * Date: 3/31/2024                                                               *
// * Author: Gokhan Unal                                                           *
// * Description: returns vector size NOT the total number of pairs in the htable  *
// *********************************************************************************
template<typename K, typename V>
int HashTable<K, V>::VecSize() const
{
	return htable.size();
}

// *********************************************************************************
// * Function Name: bool contains(const K& k)                                      * 
// * Description: Checks if the key is in the hash table                           *
// * Date: 3/25/2024 - Updates made on 3/27/2024 to tackle bool == error           *
// * Author: Gokhan Unal                                                           *
// * References: Weiss C++ figure 5.9 - The same logic as match function, I just   *
// * inserted a for loop                                                           *
// *********************************************************************************
template<typename K, typename V>
bool HashTable<K, V>::contains(const K& k) const
{
	for (auto itr = htable[myhash(k)].begin(); itr != htable[myhash(k)].end(); ++itr)
	{
		//check each iterator's key and if the key is found, return true
		if (itr->first == k) { return true; }
	}
	//if not found in the iteration, return false
	return false;
}

// *********************************************************************************
// * Function Name: bool match(const pair<K, V>& kV)                               * 
// * Description: Checks if the key/value combo is in the hash table               *
// * Date: 3/27/2024                                                               *
// * Author: Gokhan Unal                                                           *
// * References: Weiss C++ figure 5.9 verbatim, it is named contains on there      *
// * and it also proceeds in the return as begin(whichList), end(whichList) but    *
// * for this project it must be accessed as whichList.begin() since it is a vec   *
// *********************************************************************************
template<typename K, typename V>
bool HashTable<K, V>::match(const pair<K, V>& kv) const
{
	auto& whichList = htable[myhash(kv.first)];
	return std::find(whichList.begin(), whichList.end(), kv) != whichList.end();
}

// *********************************************************************************
// * Function Name: insert(const pair<K, V>& kv)                                   * 
// * Description:dd the key-value pair kv into the hash table.                     *
// * Don't add if kv is already in the hash table. If the key is in the hash       *
// * table but with a different value, the value should be updated to the new one  *
// * with kv.Return true if kv is inserted or the value is updated; return false   *
// * Date: 3/25/2024                                                               *
// * Author: Gokhan Unal                                                           *
// * References: Weiss C++ figure 5.10                                             *
// *********************************************************************************
template<typename K, typename V>
bool HashTable<K, V>::insert(const pair<K, V>& kv)
{
	//alread y in the table case
	if (match(kv)) { return false; }
	//if the key is found
	else if (contains(kv.first))
	{
		// if key is found, but the value is different, update the table with a
		//different value
		auto& whichList = htable[myhash(kv.first)];//link it to the curr table
		//iterate over the list, and upon finding the key, erase its value
		//then insert the new value into the table as per instructions
		for (auto itr = whichList.begin(); itr != whichList.end(); ++itr)
		{
			if (itr->first == kv.first)
			{
				auto tempItr = whichList.erase(itr);
				whichList.insert(tempItr, kv);//insert at the same place
			}
		}
		//succesfully inserted
		return true;
	}
	//not in the list at all case
	else
	{
		//if htSize + 1 > the vector size, rehash
		if (++htSize > htable.size()) { rehash(); }
		htable[myhash(kv.first)].push_back(kv);
		return true;
	}
}

// *********************************************************************************
// * Function Name: insert(const pair<K, V>&& kv) MOVE                             * 
// * Description:dd the key-value pair kv into the hash table.                     *
// * Don't add if kv is already in the hash table. If the key is in the hash       *
// * table but with a different value, the key value should be updated to a new    *
// * value. Return true if kv is inserted or the value is updated; return false    *
// * Date: 3/25/2024                                                               *
// * Author: Gokhan Unal                                                           *
// * References: calls the normal copy constructor of insert                       *
// *********************************************************************************
template<typename K, typename V>
bool HashTable<K, V>::insert(pair<K, V>&& kv)
{
	//move the key value pair to kvp and then insert it to the list
	const pair<K, V> kvp = move(kv);
	return insert(kvp);
}

// *********************************************************************************
// * Function Name: remove(const K& k)                                             *  
// * Description:                                                                  *
// * Date: 3/25/2024                                                               *
// * Author: Gokhan Unal                                                           *
// * References: Weiss C++ figure 5.9 - a for loop added as extra and changed      *
// * to vector access with .                                                       *
// *********************************************************************************
template<typename K, typename V>
bool HashTable<K, V>::remove(const K& k)
{
	auto& whichList = htable[myhash(k)];
	for (auto itr = whichList.begin(); itr != whichList.end(); ++itr)
	{
		//if the key is found
		if (itr->first == k)
		{
			itr = whichList.erase(itr);
			--htSize;
			return true;
		}
	}
	//if not found in the table, it cannot be removed
	return false;
}

// *********************************************************************************
// * Function Name: load(const char* filename)                                     * 
// * Description:load the input from the file                                      *
// * Date: 3/25/2024                                                               *
// * Author: Gokhan Unal                                                           *
// * References: Dr. Works' LoadData function(modified) from Fall 2023             *
// *********************************************************************************
template<typename K, typename V>
bool HashTable<K, V>::load(const char* filename)
{
	ifstream fin;
	fin.open(filename, ifstream::in);
	if (fin.fail())
	{
		cout << "*****Failed opening file" << std::endl;
		return false;
	}
	//create the pair
	std::pair<K, V> kvp;
	while (fin >> std::ws) //discard whitespace while looping
	{
		//tackle line by line
		getline(fin, kvp.first, ' ');
		getline(fin, kvp.second);
		//insert key/value pair to the table
		insert(kvp);
	}
	//close inputstream from file
	fin.close();
	//return true upon successful insertion
	return true;
}

// ***********************************************************************************
// * Function Name: dump()const                                                      * 
// * Description:dump the table unencrypted                                          *
// * Date: 3/27/2024 - Updated 3/28/2024 & 4/2/2024(unsuccessful update, reverted)   *
// * Author: Gokhan Unal                                                             *
// * References:https://stackoverflow.com/questions/19228994/how-to-print-a-type-vectorpairchar-int-to-screen-c*   
// ***********************************************************************************
template<typename K, typename V>
void HashTable<K, V>::dump() const
{
	for (int i = 0; i < htable.size(); i++)
	{
		//decorate for readability
		cout << "htable[" << i << "] = ";
		for (auto itr = htable[i].begin(); itr != htable[i].end(); itr++)
		{
			BYTE charin[256]{};
			BYTE charout[256]{};
			//if the the pointer of the token is not equal to htable[i].begin()
			//chain it at the same location and seperate pairs with '-'
			//for better distinction between pairs
			if (itr != htable[i].begin())
			{
				cout << " - ";
			}
			/*
			for (int i = 0; i < encrypted_pass.size(); i++)
			{
				charin[i] = encrypted_pass[i];
			}
			base64_decode(charin, charout, strlen(charin));
			*/
			//if it is the first hash, just print out the kv pair in the location
			//seperate the key from value with a space
			cout << itr->first << ' ' << itr->second;
		}
		cout << endl;
	}
}

// *********************************************************************************
// * Function Name: write_to_file(const char* filename)                            * 
// * Description:  write all elements in the hash table                            *
// * into a file with name filename.Similar to the file format in the load function,
// * each line contains a pair of key - value pair, separated by a white space.    *
// * Date: 3/28/2024 - Updated to decode while writing to file on 4/2/2024         *
// * MAJOR INSTRUCTIONS CHANGE on 4/3/2024. It is writing to file encoded instead  *
// * of decoded.                                                                   *
// * Dr. Gaitros stated it is more like real life and spared me from the linprog   *
// * line ending error.                                                            *
// * Author: Gokhan Unal                                                           *
// * References: Derived from load and my own sweat                                *
// *********************************************************************************
template<typename K, typename V>
bool HashTable<K, V>::write_to_file(const char* filename) const
{
	//create the ofstream object
	ofstream fout;
	fout.open(filename);
	//if it fails to open, return false
	if (fout.fail())
	{
		cout << "*****Failed opening file" << std::endl;
		return false;
	}
	//iterate over the full vector
	for (int i = 0; i < htable.size(); i++)
	{
		//iterate over each linked list in the vector
		for (auto itr = htable[i].begin(); itr != htable[i].end(); ++itr)
		{
			BYTE charin[256]{};
			BYTE charout[256]{};

			fout << itr->first << " " << itr->second << endl;
			/*************************************************************** 
			* Please ignore the multiple line comment out. I still want to *
			* work on it and see why I cannot force the last password to   *
			* decode on my own time.                                       *
			* **************************************************************
			/The routine below is same as my encrypt function in my PassServer.h
			I know this looks ugly. But I couldn't get it to work as 
			a seperate function created both in PassServer and Hashtable.
			I kept getting the << operator error. 
			copy the encrypted password/

			string encrypted_pass = itr->second;
			dump the encrypted pass into charin
			
			for (int i = 0; i < encrypted_pass.size(); i++)
			{
				charin[i] = encrypted_pass[i];
			}
			
			decode it
			base64_decode(charin, charout, strlen(charin)); 
			*/
		}
	}
	//close the stream
	fout.close();
	//return true if written successfully
	return true;
}

// *********************************************************************************
// * Function Name: resizeServer(size_t size)                                           * 
// * Description: Resizes the vector approprietly                                  *
// * Date: 3/25/2024                                                               *
// * Author: Gokhan Unal                                                           *
// * References:                                                                   *
// *********************************************************************************
template<typename K, typename V>
void HashTable<K, V>::resizeServer(size_t size)
{
	//if the list size is not equal to the input size; 
	//resize the vector
	if (numUserPair() != size)
	{
		htable.resize(prime_below(size));
		htSize = 0;
	}
}

// *********************************************************************************
// * Function Name: MakeEmpty()                                                    * 
// * Description:                                                                  *
// * Date: 3/25/2024                                                               *
// * Author: Gokhan Unal                                                           *
// * References: Weiss C++ Figure 5.9 verbatim                                     *
// *********************************************************************************
template<typename K, typename V>
void HashTable<K, V>::makeEmpty()
{
	for (auto& k : htable)
	{
		k.clear();
	}
	htSize = 0;
}

// *********************************************************************************
// * Function Name: rehash()                                                       * 
// * Description: Rehash function. Called when the number of elements in the hash  *
// * table is greater than the size of the vector.                                 *
// * Date: 3/25/2024                                                               *
// * Author: Gokhan Unal                                                           *
// * References: WEISS C++ Figure 5.22 verbatim                                    *
// *********************************************************************************
template<typename K, typename V>
void HashTable<K, V>::rehash()
{
	auto oldLists = htable;
	htable.resize(prime_below(2 * htable.size()));
	for (auto& h : htable)
	{
		h.clear();
	}

	//reset the list size(hash table, not vector) for copy purposes
	htSize = 0;
	// go into each row of lists
	for (auto& htable : oldLists)
	{
		//iterate the list (row) and insert accordingly with move
		for (auto& x : htable)
		{
			insert(move(x));
		}
	}
}

// *********************************************************************************
// * Function Name: myhash(const K& k)                                             * 
// * Description: return the index of the vector entry where k should be stored    *
// * Date: 3/25/2024                                                               *
// * Author: Gokhan Unal                                                           *
// * References: WEISS C++ Figure 5.7 verbatim                                     *
// *********************************************************************************
template<typename K, typename V>
size_t HashTable<K, V>::myhash(const K& k) const
{
	std::hash<K> h;
	return h(k) % htable.size();
}
#include "passserver.h"

using namespace std;
using namespace cop4530;
// *********************************************************************************
// * I literally used the instructions on canvas to write this .cpp. Therefore;    *
// * I want to cite the canvas instructions as reference for all of the functions. *
// * here at the top for reducing the redundant references and a cleaner look.     *
// * Some of the simple functions such as encrpyt was written by me, no reference  *
// * for those but me :)                                                           *
// * *******************************************************************************

// *********************************************************************************
// * Author: Gokhan Unal                                                           *
// * Function name: PassServer(size_t = 101)                                       *
// * Date: 3/29/2024                                                               *
// * Description: create a hash table of thespecified size.You just need to pass   *
// * this size parameter  to the constructor of the HashTable.Therefore, the real  *
// * hash table size could be different from the parameter size(because prime_below() 
// * will be called in the constructor of the HashTable).                          *
// * Reference: Instructions above :)                                              *
// *********************************************************************************
PassServer::PassServer(size_t s)
{
	newhtable.resizeServer(s);
}

// *********************************************************************************
// * Author: Gokhan Unal                                                           *
// * Function name: ~PassServer()                                                  *
// * Date: 3/29/2024                                                               *
// * Author: Gokhan Unal                                                           *
// * Description: Destructor. Call clear() from HashTable                          * 
// *********************************************************************************
PassServer::~PassServer()
{
	newhtable.clear();
}

// *********************************************************************************
// * Author: Gokhan Unal                                                           *
// * Function name: load(const char* filename)                                     *
// * Date: 3/29/2024 - Updated on 4/1/2024 following Dr. Gaitros' advice.          *
// * Author: Gokhan Unal                                                           *
// * Description:Same as load in HashTable class, this one is different in that it *
// * encrypts the password and then inserts it into the hashtable. Since we will   *
// * use load only on PassServer objects, I just wrote it here instead of writing  *
// * the encrypted version in HashTable class. The only one I couldn't manage to   *
// * write decrypted in PassServer class is write_to_file, which is implemented    * 
// * in HashTable class                                                            * 
// *********************************************************************************
bool PassServer::load(const char* filename)
{
	std::ifstream fin;
	fin.open(filename, std::ifstream::in);
	if (fin.fail())
	{
		std::cout << "*****Failed opening file" << std::endl;
		return false;
	}
	//create the pair
	std::pair<string, string> kvp;
	while (fin >> std::ws) //discard whitespace while looping
	{
		//tackle line by line
		std::getline(fin, kvp.first, ' ');
		std::getline(fin, kvp.second);
		kvp.second = encrypt(kvp.second);
		//insert key/value pair to the table
		newhtable.insert(kvp);
	}
	//close inputstream from file
	fin.close();
	//return true upon successful insertion
	return true;
}

// *********************************************************************************
// * Author: Gokhan Unal                                                           *
// * Function name: encrypt(const string& str) //private                           *
// * Date: 3/29/2024                                                               *
// * Author: Gokhan Unal                                                           *
// * Description: acesses base64 function                                          * 
// *********************************************************************************
string PassServer::encrypt(const string& str)
{
	BYTE charin[MAXSIZE]{};
	BYTE charout[MAXSIZE]{};

	for (int i = 0; i < str.size(); i++)
	{
		//copy the string chars to charin
		charin[i] = str[i];
	}
	base64_encode(charin, charout, strlen(charin), 1);
	return charout;
}

// *********************************************************************************
// * Author: Gokhan Unal                                                           *
// * Function name: decrypt(const string& str)//private                            *
// * Date: 3/29/2024                                                               *
// * Author: Gokhan Unal                                                           *
// * Description: acesses base64 functions                                         * 
// *********************************************************************************
/*
string PassServer::decrypt(const string& str)
{
	BYTE charin[MAXSIZE]{};
	BYTE charout[MAXSIZE]{};
	for (int i = 0; i < str.size(); i++)
	{
		//copy the string chars to charin
		charin[i] = str[i];
	}

	base64_decode(charin, charout, strlen(charin));
	return charout;
}
*/

// *********************************************************************************
// * Author: Gokhan Unal                                                           *
// * Function name: addUser(pair<string, string>& kv)                              *
// * Date: 3/30/2024                                                               *
// * Author: Gokhan Unal                                                           *
// * Description:add a new username and password.The password passed in is in      *
// * plaintext, it should be encrypted before insertion.                           *
// *********************************************************************************
bool PassServer::addUser(pair<string, string>& kv)
{
	string enc = encrypt(kv.second); //encrypt the password of the user
	pair<string, string> mypair(kv.first, enc);
	return newhtable.insert(mypair);
}

// *********************************************************************************
// * Author: Gokhan Unal                                                           *
// * Function name: addUser(pair<string, string>&& kv) MOVE                        *
// * Date: 3/30/2024                                                               *
// * Author: Gokhan Unal                                                           *
// * Description:add a new username and password.The password passed in is in      *
// * plaintext, it should be encrypted before insertion.                           *
// *********************************************************************************
bool PassServer::addUser(pair<string, string>&& kv)
{
	pair<string, string> mypair(move(kv));
	return addUser(mypair);//call the copy version of the same function
}

// *********************************************************************************
// * Author: Gokhan Unal                                                           *
// * Function name: removeUser(const string& key)                                  *
// * Date: 3/30/2024                                                               *
// * Author: Gokhan Unal                                                           *
// * Description: delete an existing user with username k. Calls remove from       *
// * HashTable class.                                                              *
// *********************************************************************************
bool PassServer::removeUser(const string& k)
{
	return newhtable.remove(k);
}

// *********************************************************************************
// * Author: Gokhan Unal                                                           *
// * Function name: changePassword(const pair<string, string>& p,                  *
// *                const string& newpassword)                                     *
// * Date: 3/30/2024                                                               *
// * Author: Gokhan Unal                                                           *
// * Description: change an existing user's password. Note that both passwords     *
// * passed in are in plaintext.They should be encrypted before you interact with  *
// * the hash table.If the user is not in the hash table, return false.If p.second *
// * does not match the current password, return false.Also return false if the    *
// * new password and the old password are the same(i.e., we cannot update the     *
// * password).                                                                    * 
// * References: Dr. Gaitros' canvas instructions above.                           *
// *********************************************************************************
bool PassServer::changePassword(const pair<string, string>& p, const string& newpassword)
{
	//create the pair first
	pair<string, string> mypair = make_pair(p.first, encrypt(p.second));
	if (newhtable.match(mypair) && mypair.second != encrypt(newpassword))
	{ 
		//delete the matched pair
		newhtable.remove(mypair.first);
		//create the pair with same key and the new password encrypted
		pair<string, string> newpair = make_pair(mypair.first, encrypt(newpassword));
		newhtable.insert(newpair);
		return true;
	}
	return false;

}

// *********************************************************************************
// * Author: Gokhan Unal                                                           *
// * Function name: find(const string& user)                                       *
// * Date: 3/31/2024                                                               *
// * Author: Gokhan Unal                                                           *
// * Description:Find whether user exists. Calls contains from HashTable           *
// * Reference:N/A                                                                 *
// *********************************************************************************
bool PassServer::find(const string& user)
{
	return newhtable.contains(user);
}

// *********************************************************************************
// * Author: Gokhan Unal                                                           *
// * Function name: dump()                                                         *
// * Date: 3/31/2024                                                               *
// * Author: Gokhan Unal                                                           *
// * Description:show the structure and contents of the HashTable object to        *
// * the screen.Same format as the dump() function in the HashTable class          *
// * Reference:N/A                                                                 *
// *********************************************************************************
void PassServer::dump()
{
	newhtable.dump();
}

// *********************************************************************************
// * Author: Gokhan Unal                                                           *
// * Function name: size()                                                         *
// * Date: 3/31/2024                                                               *
// * Author: Gokhan Unal                                                           *
// * Description: Return the number of user/password pairs in the newhtable        *
// * Reference:N/A                                                                 *
// *********************************************************************************
size_t PassServer::size()
{
	return newhtable.numUserPair();
}

// *********************************************************************************
// * Author: Gokhan Unal                                                           *
// * Function name: write_to_file(const char* filename)                            *
// * Date: 3/31/2024                                                               *
// * Author: Gokhan Unal                                                           *
// * Description: Un-encrypt the password from the data structrure                 *
// * and save the username and password combination into a file. Same format       *
// * as the write_to_file() function in the HashTable class template.              *
// * Reference:N/A - Calls HashTable class' fout function                          *
// *********************************************************************************
bool PassServer::write_to_file(const char* filename)
{
	return newhtable.write_to_file(filename);
	
	/* ******************************************************************************
	 * my first failed attempt to do it in passserver. It didn't work for a day     * 
	 * of me battling it. I even added iterators for it to my .h file to no avail   *
	 * It created huge operator issues since the iterator comes from a template class
	 * Then I decided to encrypt it in HashTable class and just call it from here   *
	 * ******************************************************************************
	//create the ofstream object
	std::ofstream fout;
	fout.open(filename);
	//if it fails to open, return false
	if (fout.fail())
	{
		std::cout << "*****Failed opening file" << std::endl;
		return false;
	}
	//iterate over the full vector
	for (size_t i = 0; i < newhtable.VecSize(); i++)
	{
		//iterate over each linked list in the vector
		for (auto itr = newhtable[i].begin(); itr != newhtable[i].end(); ++itr)
		{
			fout << itr->first << ' ' << decrypt(itr->second) << std::endl;
		}
	}
	//close the stream
	fout.close();
	//return true if written successfully
	return true;
	*/
}

/*
// *********************************************************************************
// * Author: Gokhan Unal                                                           *
// * Function name: passVecSize() const                                            *
// * Date: 3/31/2024                                                               *
// * Author: Gokhan Unal                                                           *
// * Description: returns vector size                                              *
// *********************************************************************************
int PassServer::passVecSize() const
{
	return newhtable.VecSize();
}
*/
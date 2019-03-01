#include "Cache.h"


namespace G 
{	
	typedef bitset<32> bits;
	Cache::~Cache() {
		
	}
	
	Cache::Cache(int& C, int&b, int&N) {
		capacity 	= C;
		block_size	= b;
		assoc		= N;

		createCache();
		
		cout << "Capacity: " << C << endl;
		cout << "Block Size: " << b << endl;
		cout << "Associativity: " << N << endl;
		cout << "Total blocks: " << blocks << endl;
		cout << "Total sets: " << sets << endl;
		cout << "Offset bits: " << offset << endl;
		cout << "Index bits: " << index << endl;
		cout << "Tag bits: " << tag << endl;
	}
	
	void Cache::createCache() {
		blocks = capacity/block_size;
		sets = blocks/assoc;
		offset = log(block_size)/log(2);
		index = log(sets)/log(2);
		tag = 32 - offset - index;
	}
	
	void Cache::readMemory() {
		ifstream file;
		string line;
		
		file.open("example.trc", ios::in);
		
		int j=0;
		while(!file.eof())
		{
			getline(file,line);
			
			
			memory.push_back(hexToBin(line));
			tags.push_back(getTag(memory.at(j)));
			intTags.push_back(bitsToInt(tags.at(j)));

//			cout << "FROM FILE: " << line << endl;
//			cout << "MEM: " << memory.at(j) << endl;
//			cout << "TAG: " << tags.at(j) << endl;
//			cout << "INTTAG : " << intTags.at(j) << endl;
			j++;
		}
		
		cout << "Read in " << j+1 << " memory addresses from the file" << endl;
		
		file.close();
	}
	/*Returns a bitset<32> for analyzing the memory address*/
	bits Cache::hexToBin(string s)
	{
		stringstream ss;
		ss << hex << s;
		unsigned n;
		ss >> n;
		bitset<32> b(n);
		
		return b;
	}
	
	bits Cache::getTag(bits h)
	{
//		stringstream ss;
//		string s = h.to_string();
//		char* test = (char*)malloc(32);
//		
//		
//		ss << hex << s;
//		unsigned n;
//		ss >> n;
//		bitset<32> b(n);
//		
//		delete test;
//		return b;


		bitset<32> b(h.to_string(), 0, tag);
		
		return b;
	}
	
	int Cache::bitsToInt(bits h)
	{
		int b = stoi(h.to_string(), nullptr, 2);

		return b;
	}
	
}

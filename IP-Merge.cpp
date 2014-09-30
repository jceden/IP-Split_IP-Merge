#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;
struct Store
	{
		int subnet;
		int first;
		int last;
	};

int main()
{
	//hardcoding input and output files
	ifstream ifs("in.txt", ios::in);
	if(!ifs)
	{
		cerr << "Error: could not open input file: " << "in.txt" << endl;
		return 1;
	}
	ofstream ofs("out.txt", ios::out);
	if(!ofs)
	{
		cerr << "Error: could not open output file: " << "out.txt" << endl;
		return 1;
	}
	
	string trash;
	int Subnet;
	string subnet_str;
	int firstIP;
	int lastIP;
	Store store;
	vector<Store> storage;
	//take in 3 IPs
	//compare the last two octects to determine if range exists
	//output range as xx.xx.xx.xx-xx.xx.xx.xy
	while(ifs.peek()!=EOF)
	{
		Subnet = 0;
		firstIP = 0;
		trash = "Unchanged";
		//assuming all IPs start with 132.241. We grab the first two octects of the IP
		for(int i = 0; i < 2; i++)
		{
		getline(ifs,trash,'.');
		//trash = ifs.get();
		}
		getline(ifs,subnet_str, '.');
		Subnet = atoi(subnet_str.c_str());
		getline(ifs,trash,'\n');
		firstIP = atoi(trash.c_str());
		store.subnet = Subnet;
		store.first = firstIP;
		bool used = false;
		
		if(storage.size()==0)
		{
			store.last = firstIP;
			storage.push_back(store);
		}
		else
		{
			for(int i = 0; i < storage.size()+1; i++)
			{
				used = false;
				//check if vector[i] is the same subnet if it is perform check on the IP
				if(storage[i].subnet == Subnet)
				{
					//check the first IP of the vector against the new IP. If the new IP is one less it is the new first
					if(storage[i].first-1 == firstIP)
					{
						storage[i].first = firstIP;
						used = true;
						break;
					}
					//check if the last IP of the vector against the new IP. If the new IP is one more than the last, it is the new last
					else if(storage[i].last+1 == firstIP)
					{
						storage[i].last = firstIP;
						used = true;
						break;
					}
				}
			}
			//checked all vector ranges, put in new range
			if(used == false)
			{
			store.last = firstIP;
			storage.push_back(store);
			}
		}
	}
	//output to the output file
	for(int i = 0; i < storage.size(); i++)
	{
		if(i+1 != storage.size())
		{
			if(storage[i].first == storage[i].last)
			{
				ofs << "132.241." << storage[i].subnet << "." << storage[i].first << "," << endl;
			}
			else
			{
				ofs << "132.241." << storage[i].subnet << "." << storage[i].first << "-132.241." << storage[i].subnet << "." << storage[i].last << "," << endl;
			}
		}
		else
		{
			if(storage[i].first == storage[i].last)
			{
				ofs << "132.241." << storage[i].subnet << "." << storage[i].first << endl;
			}
			else
			{
				ofs << "132.241." << storage[i].subnet << "." << storage[i].first << "-132.241." << storage[i].subnet << "." << storage[i].last << endl;
			}
		}
	}
	return 0;
}

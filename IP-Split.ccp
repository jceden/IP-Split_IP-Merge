/*Author: Justin Eden
Created in conjunction with Qualysguard scanner
IPs are presented in ranges or separated by comma which is annoying for spreadsheets
program separates all IP addresses onto their own lines despite spacing
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
/*
//program takes in two arguments, an input filename and an output filename
	if(argc < 3)
	{
		cout << "Not enough arguments, supply input file and output file" << endl;
		return 1;
	}
	*/
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

	//variables
	string IP;
	int inc = 0;
	int last_IP;
	int end_range;
	string IP_array[3];
	int counter = 0;

	while(!ifs.eof())//while the input stream is not empty
	{
		last_IP = 300;//initialize last_IP to 300 to prevent printing again on last iteration
		
		//retrieve the first 3 bits from IP address
		while(inc < 3)
		{
			getline(ifs, IP, '.');
			IP_array[inc] = IP;
			inc++;
		}
		//obtain last bit from IP address, compare if the next input is a dash
		ifs >> last_IP;
		
		//if the last bit is over 255 it is invalid
		if(last_IP > 255)
		{
		break;
		}
		
		if(ifs.peek() == '-')
		{
			//if true, reset the incrementer and grab the next IP address to determine range
			inc = 0;
			while(inc < 3)
			{
				getline(ifs, IP,'.');
				inc++;
			}
			ifs >> end_range;
			ifs.get();
			end_range = end_range+1 - last_IP;//to determine range, subract the last from first, add 1 to include the last IP in range
			
			//idea here is to take the first 3 octets, they should be the same
			//increment the last octet and print
			for(int i = 0; i < end_range;i++)
			{
				ofs << IP_array[0] << '.' << IP_array[1] << '.' << IP_array[2] << '.' << (last_IP + i) << '\n';
			}

		}
	
		else//not a range, extract newline at end then print
		{
			ifs.get();
			ofs << IP_array[0] << '.' << IP_array[1] << '.' << IP_array[2] << '.' << last_IP << '\n';
		}
		inc = 0;
		
		//while loops to eliminate extra bullshit some scumbag may insert after an IP
		while(ifs.peek() == ' ' || ifs.peek() == '\n' || ifs.peek() == ',')
		{
		ifs.get();
		}
	}
	ifs.close();
	ofs.close();
	return 0;
}

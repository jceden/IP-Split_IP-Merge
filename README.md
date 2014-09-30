IP-Split_IP-Merge
=================
Written in C++
IP-Split is written to take one or more IP ranges from a file and output them to newlines in a text file

IP-Merge is to take a list of IP addresses in a file and attempt to output the IP addresses in a file as ranges with commas.

The purpose of these programs is to use with the Qualys Vulnerability Management module. 
The problem being that Qualys deals strictly in IP ranges which makes analysis in a spreadsheet difficult. Upon completion of analysis of IPs Qualys can only handle so many IPs in a request and requires ranges if possible separated by a comma.

Program assumes two things:
1) There is already an input file which is hardcoded to look for in.txt
2) The first two octets of the IP address are 132.241.

There is code to eliminate the first assumption, it is commented out.
The second assumption is a lot of work that would not be of much use to eliminate.

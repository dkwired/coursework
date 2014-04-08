#include <iostream>
#include <stdio.h>
#include <unistd.h>

// David Klein
// 860880864
// CS 153
// Project 1
// 4/6/13

using namespace std;

void cpu_info();
void version();
void uptime();
void stat();
void diskstats();
void meminfo();

int main( int argc, char* argv[] )
{
	int period = atoi(argv[1]);
	int interval = atoi(argv[2]);

	for( int i = 0; i != interval/period; ++i )
	{
		cpu_info();
		version();
		uptime();
		stat();
		meminfo();
		sleep(period);
	}
}

void cpu_info()
{
	char buf[100];
	string cs;
	FILE* stream = popen( "head -n5 /proc/cpuinfo | grep \"model name\" | awk '{print $4,$5,$6,$7,$8,$9}'", "r" );

	while( fgets(buf, sizeof buf, stream) )
	{
		cs = buf;
	}
	fclose(stream);
	cout << "CPU type and model: "<< cs << endl;
}

void version()
{
	char buf[100];
	string cs;
	FILE* stream = popen( "head -n1 /proc/version | awk '{print $1,$2,$3}'", "r" );

	while( fgets(buf, sizeof buf, stream) )
	{
		cs += buf;
	}
	fclose(stream);
	cout << "Linux kernel version: "<< cs << endl;
}

void uptime()
{
	char buf[100];
	string cs;
	FILE* stream = popen( "head -n1 /proc/uptime | awk '{print $1}'", "r" );

	while( fgets(buf, sizeof buf, stream) )
	{
		cs += buf;
	}
	fclose(stream);
	float temp;
	int days, hrs, mins, secs;
	temp = atoi(cs.c_str());
	days = temp / (3600 * 24);
	temp = temp - (days * 3600 * 24);
	hrs = temp / 3600;
	temp = temp - (hrs * 3600);
	mins = temp / 60;
	temp = temp - (mins * 60);
	secs = temp;
	cout << "Amount of time since the system was last booted: " << days << ":" << hrs << ":" << mins << ":" << secs << endl;
}

void stat()
{
	char buf[100];
	string cs;
	FILE* stream = popen( "head -n1 /proc/stat | grep \"cpu\" | awk '{print $2,$4,$5}'", "r" );
	cout << endl;
	while( fgets(buf, sizeof buf, stream) )
	{
		cs += buf;
	}
	fclose(stream);
	cout << "CPU time in user mode, in system mode, and idle (seconds): " << cs << endl;
	
	diskstats();

	cs = "";
	stream = popen( "head -n11 /proc/stat | grep \"ctxt\" | awk '{print $2}'", "r" );
	while( fgets(buf, sizeof buf, stream) )
	{
		cs += buf;
	}
	fclose(stream);
	cout << "Number of context switches: " << cs << endl;

	cs = "";
	stream = popen( "last reboot | grep \"wtmp\" | awk '{print $3,$4,$5,$6,$7}'", "r" );
	while( fgets(buf, sizeof buf, stream) )
	{
		cs += buf;
	}
	fclose(stream);
	cout << "Last booted on " << cs << endl;

	cs = "";
	stream = popen( "head -n13 /proc/stat | grep \"processes\" | awk '{print $2}'", "r" );
	while( fgets(buf, sizeof buf, stream) )
	{
		cs += buf;
	}
	fclose(stream);
	cout << "Number of processes having been created: " << cs << endl;
}

void meminfo()
{
	char buf[100];
	string cs;
	FILE* stream = popen( "head -n1 /proc/meminfo | awk '{print $2,$3}'", "r" );

	while( fgets(buf, sizeof buf, stream) )
	{
		cs += buf;
	}
	fclose(stream);
	cout << "MemTotal: " << cs << endl;

	cs = "";
	stream = popen( "head -n2 /proc/meminfo | grep \"MemFree\" | awk '{print $2,$3}'", "r" );
	while( fgets(buf, sizeof buf, stream) )
	{
		cs += buf;
	}
	fclose(stream);
	cout << "MemFree: " << cs;
}

void diskstats()
{
	char buf[100];
	string cs;
	FILE* stream = popen( "head -n17 /proc/diskstats | grep \"sda\" | awk '{print $4}'", "r" );

	string reads, writes;
	while( fgets(buf, sizeof buf, stream) )
	{
		cs += buf;
	}
	fclose(stream);
	reads = cs;

	cs = "";
	stream = popen( "head -n17 /proc/diskstats | grep \"sda\" | awk '{print $8}'", "r" );

	while( fgets(buf, sizeof buf, stream) )
	{
		cs += buf;
	}
	fclose(stream);
	writes = cs;

	int diskTotal = 0;
	diskTotal = atoi(reads.c_str()) + atoi(writes.c_str());

	cout << "disk_io: " << diskTotal << endl << endl;
}

#include <signal.h>
#include <unistd.h>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include "proj1.h"
using namespace std;

/*
	function name: int_handler - handles  interrupt signal and take necessary action
	input: signal number
	output: none
*/

void int_handler(int signo)
{
	if(signo == SIGINT)
   	{
       	alarm(0); // Stop SIGALRM
       	string choice;

	string menu ="\nSelect one of the following: \nQ to Quit \nI to change free memory checking Interval \
	 \nT to change the Threshold  \nK to kill the receiver process\nC to Continue \nWaiting for user input:\n";
  

       	cout <<menu; 
      	cin >> choice;
        
       	// Ask for inputs until the user enters a valid response
       	while(true)
       	{
           	if(choice[0] == 'Q' || choice[0] == 'q')
           	{
			cout<< "program halted!"<<endl;
			exit(EXIT_SUCCESS);

           	}

           	else if(choice[0] == 'I' || choice[0] == 'i')
       		{
			cout << "Enter a new Interval (in seconds):\n ";
			cin >> choice;
			stringstream(choice) >> interval;
			break;
       		}

       		else if(choice[0] == 'T' || choice[0] == 't')
       		{
			cout << "Enter a new Threshold (in KB):\n ";
			cin >> choice;
			stringstream(choice) >> threshold;
			break;
       		}

       		else if(choice[0] == 'K' || choice[0] == 'k')
       		{
			kill_receiver();
			cout<< "Program continues.\n"<<endl;
			break;
       		}

       		else if(choice[0] == 'C' || choice[0] == 'c')
       		{	
			cout<< "Program continues.\n"<< endl;
			break; 
       		}

       		else
       		{
			cout << menu;
			cin >> choice;
       		}		
      	}
		cin.clear();
		cin.ignore();
		alarm(interval);
	}
}


/*
	function name: alarm_handler - handles alarm signal
	input: signal no
	output: none
*/	
void alarm_handler(int signo)
{
  // report free memory status with check_free_memory() and restart alarm
	check_free_memory();
	alarm(interval);

}

/* 
	main function
*/
int main(int argc, char* argv[])
{

  cout << "Monitoring Free Memory." << endl;
  cout << " Default frequency is " << interval << " seconds." << endl;
  cout << " Default threshold is " << threshold << " kB." << endl << endl;
  
  // register the signal handlers (SIGINT, SIGALARM)
  if (signal(SIGALRM, alarm_handler) == SIG_ERR)
  {
	  cout << "Failed to register alarm handler." << endl;
	  exit(EXIT_FAILURE);
  }

  if (signal(SIGINT, int_handler) == SIG_ERR)
  {
	cout << "Failed to register interupt handler." << endl;
	exit(EXIT_FAILURE);
  } 

  // set the first alarm 
  alarm(interval);
  while(true)
  {
	sleep(10);
  }
}

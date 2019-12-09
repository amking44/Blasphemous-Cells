#include <iostream>
using namespace std;

void bootMessage(int);
int endMessage(int);

int main() 
{
	int runCount = 1;
	do 
	{
		bootMessage(runCount);




		runCount = endMessage(runCount);
	}
	while (runCount != 0);

	return 0;
}

//change message later to explain more/give more detail
void bootMessage(int count)
{
	if (count == 0)
		cout << " Welcome to Blasphemous Cells!\n";
	cout << " The game will begin now.\n";
}

int endMessage(int count)
{
	int exitOrNaw = 0;
	cout << "You have reached the end of the game. Enter 0 to exit or 1 to continue.\n";
	cin >> exitOrNaw;
	if (exitOrNaw == 0)
	{
		count = 0; 
		return count;		
	}
	else if (exitOrNaw == 1)
	{
		count++;
		cout << count << endl;
		return count;
	}
}
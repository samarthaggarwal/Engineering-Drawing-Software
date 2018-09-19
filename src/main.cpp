#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
        // system("gnome-terminal");
        // system("cd");
		int ask=0;
		cout << "Type the GUI option and PRESS ENTER :" << endl;
		cout << "1 : Qt" << endl;
		cout << "2 : OpenGL" << endl;
		cout << "Any other key to quit" << endl;
		cin >> ask;
		if(ask==1)
			system("gnome-terminal -x sh -c 'pwd; ./bin/draw; exec bash'");
		else if(ask==2)
			system("gnome-terminal -x sh -c './bin/draw2; exec bash'");
		else
			return 0;
}
#include <iostream>
#include <sys/wait.h>

using namespace std;

int main()
{
    FILE* pipe = popen("pidof plasmashell", "r");
    if (!pipe) {
        cerr << "Error: popen failed." << endl;
        return 1;
    }

    char buffer[128];
    string output;
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        output.append(buffer);
    }

    int pclose_status = pclose(pipe);
    if (pclose_status != 0) {
        cerr << "Error: pclose failed with status " << pclose_status << endl;
        return 1;
    }

    output.erase(output.find_last_not_of(" \t\n") + 1); // Remove trailing whitespace
    kill(stoi(output), SIGKILL);

    return 0;
}

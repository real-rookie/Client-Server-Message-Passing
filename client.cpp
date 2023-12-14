// From: www.thegeekstuff.com/2011/12/c-socket-programming
// Note that port# 5002 is hard-coded into this implementation

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <string>
#include <iostream>
#include <assert.h>

void Sleep( int n );

int main(int argc, char *argv[])
{
    int sockfd = 0;
    char send_buffer[100];
    char read_buffer[100];
    struct sockaddr_in serv_addr; 

    if(argc != 3) {
        std::cout << "Wrong number of command-line args" << std::endl;
        return 1;
    }
    memset(&serv_addr, '\0', sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[1])); 

    if(inet_pton(AF_INET, argv[2], &serv_addr.sin_addr)<=0) {
        printf("\n inet_pton error occured\n");
        return 1;
    }

    std::cout << "Using port " << atoi(argv[1]) << std::endl;
    std::cout << "Using server address " << std::string(argv[2]) << std::endl;
    char hostname_buffer[100];
    gethostname(hostname_buffer, sizeof(hostname_buffer));

    int cmd_counter = 0;
    std::string cmd;
    std::string client_name = std::string(hostname_buffer) + "." + std::to_string(getpid());
    std::cout << "Host " << client_name << std::endl;
    while(true){
        std::cin >> cmd;
        if(std::cin.eof()){
            std::cout << "Sent " << cmd_counter << " transactions" << std::endl;
            return 0;
        }
        if(cmd[0] == 'T'){
            ++cmd_counter;
            memset(send_buffer, '\0',sizeof(send_buffer));
            memset(read_buffer, '\0',sizeof(read_buffer));
            assert(((sockfd = socket(AF_INET, SOCK_STREAM, 0)) > 0));
            assert((connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == 0));
            std::cout << "Send(" << cmd << ")" << std::endl;
            std::string send_content = client_name + "#" + cmd.substr(1).c_str();
            sprintf(send_buffer, send_content.c_str());
            assert((write(sockfd, send_buffer, strlen(send_buffer))) == strlen(send_buffer));
            assert((read(sockfd, read_buffer, sizeof(read_buffer)-1) > 0));
            std::cout << "Recv(" << read_buffer << ")" << std::endl;
            assert((close(sockfd) == 0));
        }else if(cmd[0] == 'S'){
            std::cout << "Sleep " << std::stoi(cmd.substr(1)) << " units" << std::endl;
        }
    }
}

// From: www.thegeekstuff.com/2011/12/c-socket-programming
// Note that port# 5002 is hard-coded into this implementation

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <iostream>
#include <netdb.h>
#include <assert.h>
#include <iomanip>

void Trans( int n );

int main(int argc, char *argv[])
{
    int listenfd, connfd;
    struct sockaddr_in serv_addr; 

    if(argc != 2) {
        std::cout << "Wrong number of command-line args" << std::endl;
        return 1;
    } 

    char sendBuff[100];
    char readBuff[100];

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1])); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 10); 

    int trans_counter = 0;
    std::cout << "Using port " << atoi(argv[1]) << std::endl;
    while(1){
        memset(sendBuff, '\0', sizeof(sendBuff));
        memset(readBuff, '\0', sizeof(readBuff));

        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 
        ++trans_counter;
        assert((read(connfd, readBuff, sizeof(readBuff)-1) > 0));
        std::string read_content = readBuff;
        int delimiter_index = read_content.find('#');
        std::string client_name = read_content.substr(0, delimiter_index);
        int trans = std::stoi(read_content.substr(delimiter_index+1));
        std::cout << "# " << trans_counter 
                  << "(T" << std::setw(3) << trans << ")"
                  << "\tfrom " << client_name << std::endl;
        Trans(trans);
        std::cout << "# " << trans_counter 
                  << "(Done)"
                  << "\tfrom " << client_name << std::endl;
        sprintf(sendBuff, "D%d", trans_counter);
        assert((write(connfd, sendBuff, strlen(sendBuff)) == strlen(sendBuff)));
    }
}

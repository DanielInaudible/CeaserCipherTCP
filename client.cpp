// C++ program to illustrate the client application in the
// socket programming
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(){
    // creating socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // specifying address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // sending connection request
    connect(clientSocket, (struct sockaddr*)&serverAddress,sizeof(serverAddress));

    //sending data
    std::string myString;
    std::getline(std::cin, myString);

    for(int i = 0; i < myString.length(); i++){
        myString[i] = myString[i] + 13;
        if(myString[i] > 126){
            myString[i] = 33 + (126 - myString[i]);
        } 
    }
    std::cout << "Encrypted message being sent: " << myString << "." << std::endl;

    // bottom - 33
    // top - 126

    const char* message = myString.c_str();

    send(clientSocket, message, strlen(message),0);

    // sending data
    //const char* message = "Hello, server!";
    //send(clientSocket, message, strlen(message), 0);

    // closing socket
    close(clientSocket);

    return 0;
}
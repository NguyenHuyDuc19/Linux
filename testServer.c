#include "controlCam.h"

#define PORT_NUM 7000
#define IP_Addr "127.0.0.1"

int serverSocket = -1;
int newSocket = -1;
struct sockaddr_in server_addr;


// char* getIpAddress(void)
// {
//     int n;
//     struct ifreq ifr;
//     char array[] = "br0";
//     n = socket(AF_INET, SOCK_DGRAM, 0);
//     //Type of address to retrieve - IPv4 IP address
//     ifr.ifr_addr.sa_family = AF_INET;
//     //Copy the interface name in the ifreq structure
//     strncpy(ifr.ifr_name , array , IFNAMSIZ - 1);
//     ioctl(n, SIOCGIFADDR, &ifr);
//     close(n);
//     char *str;
//     str = (char *)malloc(20*(sizeof(char*)));
//     //display result
//     strcpy(str, inet_ntoa(( (struct sockaddr_in *)&ifr.ifr_addr )->sin_addr));
//     return str;
// }


int main()
{
    //-------------------Variable-------------------
    uint8_t *buffer = (uint8_t *)malloc(1024 * sizeof(uint8_t));
    uint8_t *jsonData = (uint8_t *)malloc(sizeof(uint8_t) * 1024);
    header_package_t *hdPackage, pack;
    hdPackage = &pack;
    int readValue = 1;
    memset(buffer, 0, sizeof(buffer));
    memset(&server_addr, 0, sizeof(server_addr));

    // Get and print IP address
    // char *ipAddr = getIpAddress();
    // printf("My IP address is %s\n", ipAddr);
    

    //Config socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(IP_Addr);
    server_addr.sin_port = htons(PORT_NUM);
    bind(serverSocket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(serverSocket, 10);

    newSocket = accept(serverSocket, (struct sockaddr *)NULL, NULL);
    
    while(readValue)
    {
        readValue = read(newSocket, buffer, 1024);
        decodeData(buffer, hdPackage, jsonData);
        handleData(hdPackage, jsonData);
    }
    
    close(newSocket);
    close(serverSocket);
    free(buffer);
    free(jsonData);
    return 0;
}
#include "controlCam.h"



int clientSocket;
struct sockaddr_in serverAddr;
socklen_t addr_size;

int main()
{

    char *jsonData;
    
    clientSocket = socket(PF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
    addr_size = sizeof serverAddr;

    json_object *obj;
    uint8_t *sendBuffer = (uint8_t *)malloc(1024 * sizeof(uint8_t));

    unsigned short int messageID;
    
    if (!connect(clientSocket, (struct sockaddr *)&serverAddr, addr_size))
    {
        while(1)
        {
            printf("Message ID: ");
            scanf("%hd", &messageID);
            jsonData = readDataFromFile(messageID);
            printf("%hd \n", messageID);

            encodeData(sendBuffer, magic_Bytes, strlen(jsonData), messageID, 3, jsonData);
            write(clientSocket, sendBuffer, (strlen(jsonData) + 8));
        }
    }
    free(sendBuffer);
    return 0;
}
#include "controlCam.h"

char buff[1024];
FILE *fptr, *fp;

void decodeData(uint8_t *buffer, header_package_t *hdPackage, uint8_t *jsonTmp)
{
    hdPackage->magicBytes   = (buffer[1] << 8) | buffer[0];   
    hdPackage->size         = (buffer[3] << 8) | buffer[2];   
    hdPackage->messageID    = (buffer[5] << 8) | buffer[4];   
    hdPackage->sessionID    = (buffer[7] << 8) | buffer[6];
    sprintf(jsonTmp, "%s", &buffer[8]);
}

void encodeData(uint8_t *sendBuffer, unsigned short int magicBytes, unsigned short int size, unsigned short int messID, unsigned short int sessID,const char *jsonData)
{
    sendBuffer[0] = magicBytes & 0x0FF;
    sendBuffer[1] = magicBytes >> 8;
    sendBuffer[2] = size & 0x0FF;
    sendBuffer[3] = size >> 8;
    sendBuffer[4] = messID & 0x0FF;
    sendBuffer[5] = messID >> 8;
    sendBuffer[6] = sessID & 0x0FF;
    sendBuffer[7] = sessID >> 8;
    printf("%hd \n", messID);
    memcpy(sendBuffer + 8, jsonData, strlen(jsonData));
}


char *readDataFromFile(uint16_t messID)
{
    char *jsonData;
    json_object *objClient;
    switch (messID)
    {
        case CHANGE_PWD: 
            fptr = fopen(CHANGE_PWD_PATH,"r");
            jsonData = fgets(buff, 1024, fptr);
            fclose(fptr);
            break;
        case GET_INFO:
            break;
        case GET_ISP:
            break;
        case GET_URL:
            break;
        case REBOOT:
            break;
        case RESET_FACTORY:
            break;
        case UPDATE_FW: 
            fptr = fopen(UPDATE_FW_PATH, "r");
            jsonData = fgets(buff, 1024, fptr);
            fclose(fptr);
            break;
        case PLAYBACK: 
            fptr = fopen(PLAYBACK_PATH, "r");
            jsonData = fgets(buff, 1024, fptr);
            fclose(fptr);
            break;
        case TWOWAY_AUDIO:
            break;
        case RECORD:
            break;
        case GET_MAC:
            break;
        default:
            printf("Read Data ERROR!");
            break;
    }
    return jsonData;
}

void handleData(header_package_t *hdPackage, char *jsonData)
{
    switch (hdPackage->messageID)
    {
        case CHANGE_PWD: 
            change_pwd(jsonData);
            break;
        case GET_INFO: 
            get_info();
            break;
        case GET_ISP:
            get_isp();
            break;
        case GET_URL: 
            get_url();
            break;
        case REBOOT: 
            reboot();
            break;
        case RESET_FACTORY: 
            reset_factory();
            break;
        case UPDATE_FW: 
            update_fw(jsonData);
            break;
        case PLAYBACK: 
            playback(jsonData);
            break;
        case TWOWAY_AUDIO: 
            twoway_audio();
            break;
        case RECORD: 
            record();
            break;
        case GET_MAC:
            get_mac();
            break;
        default:
            printf("Handle Data ERROR!!!\n");
            break;
    }
}

void change_pwd(char *jsonData)
{
    json_object *obj_server = NULL, *current_pwd = NULL, *new_pwd = NULL;
    obj_server = json_tokener_parse(jsonData);

    json_object_object_get_ex(obj_server, "new_pwd", &new_pwd);
    printf("%s \n", json_object_to_json_string(new_pwd)); 
}

void update_fw(char *jsonData)
{
    json_object *obj_server = NULL, *linkUpdate = NULL;
    obj_server = json_tokener_parse(jsonData);

    json_object_object_get_ex(obj_server, "ota_server", &linkUpdate);
    printf("%s \n", json_object_to_json_string(linkUpdate));
    // printf("%s", jsonData);
}

void get_mac(void)
{
    int s;
    struct ifreq buffer;

    s = socket(PF_INET, SOCK_DGRAM, 0);
    memset(&buffer, 0x00, sizeof(buffer));
    strcpy(buffer.ifr_name, "eth0");
    ioctl(s, SIOCGIFHWADDR, &buffer);
    close(s);
    for( s = 0; s < 6; s++ )
    {
        printf("%.2X ", (unsigned char)buffer.ifr_hwaddr.sa_data[s]);
    }

    printf("\n");
}

void playback(char *jsonData)
{
    json_object *obj_server = NULL;
    obj_server = json_tokener_parse(jsonData);
    printf("%s \n", json_object_to_json_string(obj_server));
}

void get_info(void)
{
    printf("Hello from get_info! \n");
}

void get_isp(void)
{
    printf("Hello from get_isp! \n");
}

void get_url(void)
{
    printf("Hello from get_url! \n");
}

void reboot(void)
{
    printf("Hello from reboot! \n");
}

void reset_factory(void)
{
    printf("Hello from reset_factory! \n");
}

void twoway_audio(void)
{
    printf("Hello from twoway_audio! \n");
}

void record(void)
{
    printf("Hello from record! \n");
}

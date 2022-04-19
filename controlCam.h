#ifndef _CONTROLCAM_H_
#define _CONTROLCAM_H_

#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <stdlib.h>
#include <json-c/json.h>
#include <json-c/json_util.h>
#include <json-c/json_object.h>


#define PORT            7000
#define magic_Bytes     61324
// #define IP_Addr         "127.0.0.1"

#define CHANGE_PWD      1001
#define GET_INFO        1002
#define GET_ISP         1003
#define GET_URL         1004
#define REBOOT          1005
#define RESET_FACTORY   1006
#define UPDATE_FW       1007
#define PLAYBACK        1008
#define TWOWAY_AUDIO    1009
#define RECORD          1010
#define GET_MAC         1051

#define CHANGE_PWD_PATH     "JSON_Folder/change_pwd.json"
#define GET_INFO_PATH       "JSON_Folder/get_info.json"
#define GET_ISP_PATH        "JSON_Folder/get_isp.json"
#define GET_URL_PATH        "JSON_Folder/get_url.json"
#define REBOOT_PATH         "JSON_Folder/reboot_path.json"
#define RESET_FACTORY_PATH  "JSON_Folder/reset_factory.json"
#define UPDATE_FW_PATH      "JSON_Folder/update_fw.json"
#define PLAYBACK_PATH       "JSON_Folder/playback.json"
#define TWOWAY_AUDIO_PATH   "JSON_Folder/twoway_audio.json"
#define RECORD_PATH         "JSON_Folder/record.json"

typedef struct
{
    unsigned short int magicBytes;
    unsigned short int size;
    unsigned short int messageID;
    unsigned short int sessionID;
} header_package_t;

void decodeData(uint8_t *buffer, header_package_t *hdPackage, uint8_t *jsonTmp);
void encodeData(uint8_t *sendBuffer, unsigned short int magicBytes, unsigned short int size, unsigned short int messID, unsigned short int sessID,const char *jsonData);
char *readDataFromFile(uint16_t messID);
void handleData(header_package_t *hdPackage, char *jsonData);


void change_pwd(char *jsonData);
void get_info(void);
void get_isp(void);
void get_url(void);
void reboot(void);
void reset_factory(void);
void update_fw(char *jsonData);
void playback(char *jsonData);
void twoway_audio(void);
void record(void);
void get_mac(void);
void fail(void);


#endif
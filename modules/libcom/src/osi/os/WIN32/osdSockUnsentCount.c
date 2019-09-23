/*************************************************************************\
* EPICS BASE is distributed subject to a Software License Agreement found
* in file LICENSE that is included with this distribution.
\*************************************************************************/

#define epicsExportSharedSymbols
#include "osiSock.h"
#include <mstcpip.h>

/*
 * epicsSocketUnsentCount ()
 * See https://docs.microsoft.com/en-us/windows/win32/api/mstcpip/ns-mstcpip-tcp_info_v0
 */
int epicsSocketUnsentCount(SOCKET sock) {
#if defined (_WIN32) && WINVER >= _WIN32_WINNT_WIN10
/* Windows 10 Version 1703 / Server 2016 */
    DWORD infoVersion = 0, bytesReturned;
    TCP_INFO_v0 tcpInfo;
    int status;
    if ((status = WSAIoctl(sock, SIO_TCP_INFO, &infoVersion, sizeof(infoVersion),
        &tcpInfo, sizeof(tcpInfo), &bytesReturned, NULL, NULL)) == 0)
        return tcpInfo.BytesInFlight;
#endif
    return -1;
}

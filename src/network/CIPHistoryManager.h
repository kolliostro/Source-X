/**
* @file CIPHistoryManager.h
* @brief Manages IP connections data.
*/

#ifndef _INC_CIPHISTORYMANAGER_H
#define _INC_CIPHISTORYMANAGER_H

#include "CSocket.h"
#include <deque>


/***************************************************************************
 *
 *
 *	struct HistoryIP			Simple interface for IP history maintainence
 *
 *
 ***************************************************************************/
struct HistoryIP
{
    CSocketAddressIP m_ip;
    int m_pings;
    int m_connecting;
    int m_connected;
    bool m_blocked;
    int m_ttl;
    int64 m_blockExpire;
    int m_pingDecay;

    void update(void);
    bool checkPing(void); // IP is blocked -or- too many pings to it?
    void setBlocked(bool isBlocked, int timeout = -1); // timeout in seconds
};

typedef std::deque<HistoryIP> IPHistoryList;



/***************************************************************************
 *
 *
 *	class IPHistoryManager		Holds IP records (bans, pings, etc)
 *
 *
 ***************************************************************************/
class IPHistoryManager
{
private:
    IPHistoryList m_ips;		// list of known ips
    int64 m_lastDecayTime;	// last decay time

public:
    IPHistoryManager(void);
    ~IPHistoryManager(void);

private:
    IPHistoryManager(const IPHistoryManager& copy);
    IPHistoryManager& operator=(const IPHistoryManager& other);

public:
    void tick(void);	// period events

    HistoryIP& getHistoryForIP(const CSocketAddressIP& ip);	// get history for an ip
    HistoryIP& getHistoryForIP(const char* ip);				// get history for an ip
};

#endif // _INC_CIPHISTORYMANAGER_H
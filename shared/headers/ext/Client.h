///////////////////////////////////////////////////////////////////
// Prepared for BCIT ELEX4618, April 2022, by Craig Hennessey
///////////////////////////////////////////////////////////////////
#pragma once

#include <string>
#include <opencv2/opencv.hpp>

// SET MACROS AND COMPILE USING CMAKELISTS!!
#if defined(WIN4618)
#pragma comment("Using WIN4618 for CClient")
#elif defined(PI4618)
#pragma comment("Using PI4618 for CClient")
#else
#pragma comment("MAKE SURE TO DEFINE EITHER WIN4618 OR PI4618! COMPILE WILL FAIL!")
#endif

//#define WIN4618
//#define PI4618

#ifdef WIN4618
#include "Winsock2.h"
#endif

#ifdef PI4618
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
typedef int SOCKET;
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <thread>
#endif

class CClient
{
private:
#ifdef WIN4618
  WSADATA _wsdat;
#endif

  int _port;
  std::string _addr;
  SOCKET _socket;
  
  bool setblocking(SOCKET fd, bool blocking);

public:
  CClient();
	~CClient();

  void connect_socket(std::string addr, int port);
  void close_socket();

  void tx_str(std::string str);
  bool rx_str(std::string &str);
  bool rx_im(cv::Mat &im);
};



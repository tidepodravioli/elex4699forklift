///////////////////////////////////////////////////////////////////
// Prepared for BCIT ELEX4618, April 2022, by Craig Hennessey
///////////////////////////////////////////////////////////////////
#pragma once

//#define WIN4618
//#define PI4618

#if defined(WIN4618)
#pragma comment("Using WIN4618 for CServer")
#elif defined(PI4618)
#pragma comment("Using PI4618 for CServer")
#else
#pragma comment("CServer : MAKE SURE TO DEFINE EITHER WIN4618 OR PI4618! COMPILE WILL FAIL!")
#endif

#include <iostream>
#include <string>
#include <mutex>
#include <vector>

//#ifdef PI4618
#include <opencv2/opencv.hpp>
//#endif

class CServer
{
private:
  bool _server_exit;
  cv::Mat _txim;
  
  std::mutex _image_mutex;
  std::mutex _rx_mutex;
  std::mutex _tx_mutex;
  std::vector<std::string> _cmd_list;
  std::vector<std::string> _send_list;

  //CUSTOM CODE - RAFAEL BANALAN 2025/05/15
  std::vector<std::string> _connected_ips;
  std::mutex _ip_mutex;

  
  bool setblocking(int fd, bool blocking);

public:
  CServer();
	~CServer();

  // Start server listening (probably best to do in a separate thread)
  void start(int port);
  void stop();

  // Set the image to transmit
  void set_txim (cv::Mat &im);

  // Get a vector of the commands the server has read
  void get_cmd (std::vector<std::string> &cmds);

  // Send a response
  void send_string (std::string send_str);

  //CUSTOM CODE - RAFAEL BANALAN 2025/05/15
  //Gets a list of the connected IP's
  void get_connected_ips(std::vector<std::string> &ips);
};


/*
NOTE: If you see this error when running your program on the Pi then follow the instructions below.

Xlib: sequence lost(0x10061 > 0x6d) in reply type 0x1c!
[xcb] Unknown request in queue while dequeuing
[xcb] Most likely this is a multi - threaded client and XInitThreads has not been called
[xcb] Aborting, sorry about that.
main : .. / .. / src / xcb_io.c : 165 : dequeue_pending_request : Assertion `!xcb_xlib_unknown_req_in_deq' failed.
2021 - 03 - 31 16:31 : 31 sigHandler : Unhandled signal 6, terminating

------------------------------------

Install X11 with :

sudo apt-get install libx11-dev

------------------------------------

Include X11 library AFTER the OpenCV header:

#include <opencv2/opencv.hpp>
#include <X11/Xlib.h>

------------------------------------

Call XInitThreads in main or constructor:

XInitThreads();

------------------------------------

Add directive to linker:
- lX11

*/

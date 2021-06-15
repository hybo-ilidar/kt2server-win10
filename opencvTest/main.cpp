

// Hybo-KT LIDAR Development Project
// Viewer/Logger program
// 15 March 2021
// OpenCV 2.4.0 / pthread
// Son, Youngbin
// tech@hybo.co

// 4 May 2021 - Row count is changed to 40

#define _CRT_SECURE_NO_WARNINGS

#include <winsock.h>
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <queue>

#pragma comment(lib, "Ws2_32.lib")
#include "main.h"
#include <highgui.h>
#include <cv.h>

#include <iostream>

// timer definition
unsigned long long int _timeOffset;
unsigned long long int tic(void);
unsigned long long int toc(void);

// host clock definition
unsigned long long int _clockOffset;
double timeHost(void);


int main(void) {
  int th_id;
  int status;
  int argument=0;
  int ret;
  
  sched_param param;

  pthread_t sensor;
  pthread_t udpserver;

  // timer initialization
  _timeOffset = tic();
  _clockOffset = _timeOffset;

  // Thread initiation
  pthread_attr_t tattrCritical;
  ret = pthread_attr_init(&tattrCritical);
  ret = pthread_attr_getschedparam(&tattrCritical, &param);
  param.sched_priority = THREAD_PRIORITY_TIME_CRITICAL;
  ret = pthread_attr_setschedparam(&tattrCritical, &param);
  th_id = pthread_create(&sensor, &tattrCritical, tSerial, (void*)argument);
  if(th_id < 0) perror("Thread create error : ");
  th_id = pthread_create(&udpserver, NULL, tUdpServer, (void*)argument);
  
  // Thread termination
  pthread_join(sensor, (void**)&status);
  pthread_join(udpserver, (void**)&status);

  return 0;
}

unsigned long long int tic(void) {
  LARGE_INTEGER l0, l1;
  double freq;
  if (!QueryPerformanceFrequency(&l0)) { printf("Failed to get frequency\n"); return 0; }
  freq = (double)(l0.QuadPart) / 1e6; // microseconds
  QueryPerformanceCounter(&l1);
  return (unsigned long long int)(l1.QuadPart / freq);
}

unsigned long long int toc(void) {
  uint64_t t1 = tic();
  uint64_t dt = t1 - _timeOffset;
  return dt;
}

double timeHost(void) {
  uint64_t t1 = tic();
  uint64_t dt = t1 - _clockOffset;
  return ((double)dt)/1000000.;
}






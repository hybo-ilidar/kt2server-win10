

// Hybo-KT LIDAR Development Project
// Viewer/Logger program
// 15 March 2021
// OpenCV 2.4.0 / pthread
// Son, Youngbin
// tech@hybo.co

// 4 May 2021 - Row count is changed to 40

#define _CRT_SECURE_NO_WARNINGS


#ifndef MAIN_H
#define MAIN_H

#define HAVE_STRUCT_TIMESPEC
#include "pthreads/pthread.h"
#include <queue>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <highgui.h>

// Timer function
extern unsigned long long int _timeOffset;
unsigned long long int tic(void);
unsigned long long int toc(void);
double timeHost(void);

void *tSerial(void *thread_argument);
void *tUdpServer(void *thread_argument);

#endif




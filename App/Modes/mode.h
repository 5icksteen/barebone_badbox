#pragma once

#include "BSP_BadBox.h"
#include "FuncHolder.h"
#include "EventLoop.h"

extern void mode1();
extern void mode2();

FuncHolder modes(mode1);
EventLoop<> events;

#include "mode1.h"
#include "mode2.h"

#pragma once

#include "FuncHolder.h"

void mode1();
void mode2();

FuncHolder modes(mode1);
EventLoop events;

#include "mode1.h"
#include "mode2.h"

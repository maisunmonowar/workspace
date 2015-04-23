#pragma once
#ifndef _DLL_H_
#define _DLL_H_

#define DLLIMPORT __declspec (dllexport)

DLLIMPORT int32_t spiltAndStitch(char* argv[]);
#endif 

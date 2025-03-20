#pragma once

#ifdef  ECLIPSE_ENGINE_EXPORTS 
#define  ECLIPSE_ENGINE __declspec(dllexport)
#else
#define  ECLIPSE_ENGINE __declspec(dllimport)
#endif
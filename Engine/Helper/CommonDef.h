#pragma once

#define _ABSTRACT class
#define _INTERFACE class
#define _CALLBACK void

#define SAFE_RELEASE(ptr)  if( (ptr) ) { (ptr)->Release(); (ptr) = nullptr; }
#define SAFE_DELETE(ptr)   if( (ptr) ) { delete (ptr); (ptr) = nullptr; }

// 간단하고 빠른 스왑, but 안정성이 부족
#define SWAP(a, b) {(a)^=(b)^=(a)^=(b);}

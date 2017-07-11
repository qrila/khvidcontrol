#ifndef _wrap_hpp
#define _wrap_hpp
#include <iostream>
#include <cstdint>
#include <cstring>
#include <chrono>

#define PSTR(s) \
	((const char *)(s)) 

#define boolean bool
#define word(a,b) (((a)<<8) + b)
#define highByte(a) (((a)&0xff00) >> 8)
#define lowByte(a) ((a)&0xff)
#define B1 0b1
#define B00000111 0b00000111
#define strncmp_P(a,b,c) strncmp(a,b,c)
#define strcmp_P(a,b) strcmp(a,b)
#define strlen_P(x) strlen(x)
#define strncpy_P(a,b,c) strncpy(a,b,c)
#define DEC 0
#define HEX 0
#define F(a) a

#include <string>
#define String std::string

#include "IPAddress.h"

class CSerial {
private:

public:
	void begin(int baud);
	void print(String message);
	void println(String message);
	void println(int value, int);
	void print(int value, int);
	void println(int value);
	void print(int value);
	void print(IPAddress& ip);
};

static CSerial Serial;

int random(int a, int b);
long millis();
String IPAddressAsString(const IPAddress ip);

#endif

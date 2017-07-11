#include "wrap.hpp"

String IPAddressAsString(const IPAddress ip) {
	String out = std::to_string(ip._address.bytes[0]) + "." +
	             std::to_string(ip._address.bytes[1]) + "." +
	             std::to_string(ip._address.bytes[2]) + "." +
	             std::to_string(ip._address.bytes[3]);
	return out;
}


void CSerial::begin(int baud) {}

void CSerial::print(IPAddress& ip) {
	std::cout << IPAddressAsString(ip);
}

void CSerial::print(String message) {
	std::cout << message;
}

void CSerial::println(int value, int) {
	std::cout << value;
}

void CSerial::print(int value, int) {
	std::cout << value;
}

void CSerial::print(int value) {
	std::cout << value;
}

void CSerial::println(int value) {
	std::cout << value;
}

void CSerial::println(String message) {
	std::cout << message << std::endl;
}

int random(int a, int b) {
	return std::rand() % (b - a) + a;
}

long millis() {
	auto time = std::chrono::system_clock::now().time_since_epoch();
	return std::chrono::duration_cast<std::chrono::milliseconds>(time).count();
}
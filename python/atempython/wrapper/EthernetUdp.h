#ifndef __ethernet_udp_h
#define __ethernet_udp_h
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <list>
#include "wrap.hpp"


using namespace boost::asio;
class EthernetUDP {
private:
	std::shared_ptr<io_service> iosvc;
	std::shared_ptr<ip::udp::socket> sock;
	String current_packet;
	std::list<String> incoming;
	
	int read_seek;
	
	IPAddress remote_ip;
	int remote_port;
	
	boost::array<char, 1500> recvbuf;
	ip::udp::endpoint remote_endpoint;
public:
	int begin(const int local_port) {
		iosvc = std::make_shared<io_service>();
		sock = std::make_shared<ip::udp::socket>(*iosvc, ip::udp::endpoint(ip::udp::v4(), local_port));
		start_receive();
		return 1;
	}
	
	int beginPacket(const IPAddress rip, const int rport) {
		current_packet = "";
		remote_ip = rip;
		remote_port = rport;
		return 1;
	}
	
	int endPacket() {
		ip::udp::endpoint endpoint;
		ip::udp::resolver resolver(*iosvc);
		endpoint = *resolver.resolve({ip::udp::v4(), IPAddressAsString(remote_ip), std::to_string(remote_port)});
		sock->send_to(buffer(current_packet, current_packet.length()), endpoint);
		return 1;
	}
	
	void write(String message) {
		current_packet += message;
	}
	
	void write(uint8_t *message, int length) {
		std::string str(message, message+length); 
		write(str);
	}
	
	//	
	void handle_receive(const boost::system::error_code &err, std::size_t nbytes) {
		if (nbytes == 0) {
			exit(1);
		} else {
			String str(recvbuf.begin(), recvbuf.begin() + nbytes);
			incoming.push_back(str);
		}

		start_receive();
	}
	
	void start_receive() {
		sock->async_receive_from(
			buffer(recvbuf),
			remote_endpoint,
			boost::bind(
				&EthernetUDP::handle_receive,
				this,
				placeholders::error,
				placeholders::bytes_transferred
			)
		);
	}

	void poll() {
		iosvc->poll();
	}
	
	void run() {
		iosvc->run();
	}
	
	// read
	int parsePacket() {
		poll();
		read_seek = 0;
		if(incoming.empty()) {
			current_packet = "";
			return 0;
		}
		
		current_packet = incoming.front();
		incoming.pop_front();
		return current_packet.length();
	}
	
	int available() {
		return current_packet.length() - read_seek;
	}
	
	int read() {
		return current_packet[read_seek++];
	}
	
	int read(unsigned char *out, size_t nbytes) {
		int length = available();
		if (nbytes > length) {
			nbytes = length;
		}
		for (int i = 0; i < nbytes; i++) {
			out[i] = read();
		}
		
		return nbytes;
	}
	
	int peek() {
		return current_packet[read_seek + 1];
	}
	
};

#endif

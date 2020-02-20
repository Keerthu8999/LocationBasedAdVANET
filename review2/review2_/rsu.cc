#include "agent.h"
#include<packet.h>
#include<iostream>
#include "rsu.h"
#include<fstream>
#include<cmu-trace.h>
#include<random.h>
#include<tcl.h>
#include<vector>
#include<bits/stdc++.h>

using namespace std;

int hdr_rsu::offset_;
std::ifstream in("/home/keyrooh/kmeans/2.txt");
double x,y;

static class RsuHeaderClass : public PacketHeaderClass {
public:
	RsuHeaderClass() : PacketHeaderClass("PacketHeader/Rsu", 
					      sizeof(hdr_rsu)) {
		bind_offset(&hdr_rsu::offset_);
	}
} class_rsuhdr;

static class RsuClass : public TclClass {
public:
	RsuClass() : TclClass("Agent/Rsu") {}
	TclObject* create(int, const char*const*) {
		return (new RsuAgent());
	}
} class_rsu;

RsuAgent::RsuAgent() : Agent(PT_RSU)
{
	bind("packetSize_", &size_);
	bind("offer_", &offer);
}
double RsuAgent::offerCalc()
{
    std::ifstream in("/home/keyrooh/kmeans/2.txt");
    double x,y;
    in>>x>>y;
    std::cout<<x<<"    "<<y<<std::endl;
    return x;
	
}
double RsuAgent::xCalc()
{
    
    std::cout<<x<<"    "<<y<<std::endl;
    return x;
	
}
double RsuAgent::yCalc()
{
    std::ifstream in("/home/keyrooh/kmeans/2.txt");
    double x,y;
    in>>x>>y;
    std::cout<<x<<"    "<<y<<std::endl;
    return y;
	
}
int RsuAgent::command(int argc, const char*const* argv)
{
  if (argc == 2) {
    if (strcmp(argv[1], "send") == 0) {
      // Create a new packet
	while(in>>x>>y){
      Packet* pkt = allocpkt();
      // Access the Ping header for the new packet:
      hdr_rsu* hdr = hdr_rsu::access(pkt);
      
      //in>>x>>y;
      hdr->offer = offer;
      hdr->x = x;
      hdr->y = y;
      Tcl& tcl1 = Tcl::instance();
      tcl1.evalf("puts \" The offer in send packet is %f\t%f\t%f\" ",hdr->offer,hdr->x,hdr->y);
      // Set the 'ret' field to 0, so the receiving node knows
      // that it has to generate an echo packet
      hdr->ret = 0;
      // Store the current time in the 'send_time' field
      hdr->send_time = Scheduler::instance().clock();
      
      // Send the packet
      send(pkt, 0);
}
      // return TCL_OK, so the calling function knows that the
      // command has been processed
      return (TCL_OK);
    }
    /*if(strcmp(argv[1], "printOffer") == 0) {
	printOffer();
	return TCL_OK; 
    }*/
  }
  // If the command hasn't been processed by PingAgent()::command,
  // call the command() function for the base class
  return (Agent::command(argc, argv));
}


void RsuAgent::recv(Packet* pkt, Handler*)
{
  // Access the IP header for the received packet:
  hdr_ip* hdrip = hdr_ip::access(pkt);
  // Access the Ping header for the received packet:
  hdr_rsu* hdr = hdr_rsu::access(pkt);
  //print data
  Tcl& tcl1 = Tcl::instance();
  //hdr->offer = offerCalc(offer);
  tcl1.evalf("puts \" The offer in recv packet is %f\t%f\t%f\" ",hdr->offer,hdr->x,hdr->y);
// Is the 'ret' field = 0 (i.e. the receiving node is being pinged)?
  if (hdr->ret == 0) {
	// Send an 'echo'. First save the old packet's send_time
	double stime = hdr->send_time;
	// Discard the packet
	Packet::free(pkt);
	// Create a new packet
	Packet* pktret = allocpkt();
	// Access the Ping header for the new packet:
	
	hdr_rsu* hdrret = hdr_rsu::access(pktret);
	//hdrret->offer = offerCalc(offer);
	// Set the 'ret' field to 1, so the receiver won't send another echo
	hdrret->ret = 1;
	// Set the send_time field to the correct value
	hdrret->send_time = stime;
	// Send the packet
	send(pktret, 0);
	char out[100];
	// Prepare the output to the Tcl interpreter. Calculate the round
	// trip time
	sprintf(out, "%s recv %d %3.1f", name(), 
	        hdrip->src_.addr_ >> Address::instance().NodeShift_[1], 
	            (Scheduler::instance().clock()-hdr->send_time) * 1000);
	Tcl& tcl = Tcl::instance();
	tcl.eval(out); 
} }/*else {
	// A packet was received. Use tcl.eval to call the Tcl
	// interpreter with the ping results.
	// Note: In the Tcl code, a procedure 'Agent/Ping recv {from rtt}'
	// has to be defined which allows the user to react to the ping
	// result.
	char out[100];
	// Prepare the output to the Tcl interpreter. Calculate the round
	// trip time
	sprintf(out, "%s recv %d %3.1f", name(), 
	        hdrip->src_.addr_ >> Address::instance().NodeShift_[1], 
	            (Scheduler::instance().clock()-hdr->send_time) * 1000);
	Tcl& tcl = Tcl::instance();
	tcl.eval(out);
	// Discard the packet
	Packet::free(pkt);
  }
} */

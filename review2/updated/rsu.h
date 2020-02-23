#include "agent.h"
#include "tclcl.h"
#include "packet.h"
#include "address.h"
#include "ip.h"
#include<mobilenode.h>
#include<packet.h>
#include<node.h>
#include<string.h>
#include<vector>
long long int size = 100000;
struct hdr_rsu {
	char ret;
	double send_time;
	double offer;
	double x;
	double y;
        double time;
	char ad[100000];
	// Header access methods
	static int offset_; // required by PacketHeaderManager
	inline static hdr_rsu* access(const Packet* p) {
		return (hdr_rsu*) p->access(offset_);
	}
};
class RsuAgent : public Agent {
public:
	RsuAgent();
	double offer;	
	double x;
	double y;
	double time;
	char ad[100000];
	struct details {
	double x_c;
	double y_c;
	double time;
	string ad_des;
	};
	virtual int command(int argc, const char*const* argv);
	virtual void recv(Packet*, Handler*);
	//virtual void printCategory(char*);
};

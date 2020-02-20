#include "agent.h"
#include<packet.h>
struct hdr_rsu {
	char ret;
	double send_time;
	double offer;
	double x;
	double y;
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
	virtual double offerCalc();
        virtual double xCalc();
	virtual double yCalc();
	virtual int command(int argc, const char*const* argv);
	virtual void recv(Packet*, Handler*);
};

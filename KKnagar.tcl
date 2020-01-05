# set number of nodes
#set opt(nn) 47

# set activity file
#set opt(af) $opt(config-path)
#append opt(af) /activity.tcl

# set mobility file
#set opt(mf) $opt(config-path)
#append opt(mf) /mobility.tcl

# set start/stop time
#set opt(start) 0.0
#set opt(stop) 100.0

# set floor size

#set opt(min-x) 305.14
#set opt(min-y) 4089.63

#copying
set val(chan)           Channel/WirelessChannel    ;# channel type
set val(prop)           Propagation/TwoRayGround   ;# radio-propagation model
set val(netif)          Phy/WirelessPhy            ;# network interface type
set val(mac)            Mac/802_11                 ;# MAC type
set val(ifq)            Queue/DropTail/PriQueue    ;# interface queue type
set val(ll)             LL                         ;# link layer type
set val(ant)            Antenna/OmniAntenna        ;# antenna model
set val(ifqlen)         50                         ;# max packet in ifq
set val(nn)             51                          ;# number of mobilenodes
set val(rp)             AODV                       ;# routing protocol
# set floor size
set opt(x) 4000
set opt(y) 6151
# ======================================================================
# Main Program
# ======================================================================


#
# Initialize Global Variables
#
set ns_ [new Simulator] 
 
#Setup topography object 
set topo       [new Topography] 
$topo load_flatgrid $opt(x) $opt(y) 
create-god $val(nn) 
set pacdelrat [open PacketdeliveryRatio.tr w] 
$ns_ trace-all $pacdelrat 
set th [open Throughput.tr w] 
$ns_ trace-all $th 
set paclossrat [open PacketlossRatio.tr w] 
$ns_ trace-all $paclossrat 
set e2edelay [open EndtoEndDelay.tr w] 
$ns_ trace-all $e2edelay 
 
#Open the NS trace file 
set tracefile [open KKnagar.tr w] 
$ns_  trace-all $tracefile 
 
#Open  the NAM trace file 
set namfile [open KKnagar.nam w] 
$ns_ namtrace-all $namfile 
$ns_ namtrace-all-wireless $namfile $opt(x) $opt(y) 
set chan [new $val(chan)];#Create wireless channel 

#
#  Create the specified number of mobilenodes [$val(nn)] and "attach" them
#  to the channel. 
#  Here two nodes are created : node(0) and node(1)

# configure node

        $ns_ node-config -adhocRouting $val(rp) \
			 -llType $val(ll) \
			 -macType $val(mac) \
			 -ifqType $val(ifq) \
			 -ifqLen $val(ifqlen) \
			 -antType $val(ant) \
			 -propType $val(prop) \
			 -phyType $val(netif) \
			 -channelType $val(chan) \
			 -topoInstance $topo \
			 -agentTrace ON \
			 -routerTrace ON \
			 -macTrace OFF \
			 -movementTrace ON			
			 
	for {set i 0} {$i < $val(nn) } {incr i} {
		set node_($i) [$ns_ node]	
		$node_($i) random-motion 0	
		$ns_ initial_node_pos $node_($i) 20	;# disable random motion
	}

#
# Provide initial (X,Y, for now Z=0) co-ordinates for mobilenodes
#
#$node_(0) set X_ 5.0
#$node_(0) set Y_ 2.0
#$node_(0) set Z_ 0.0

#$node_(1) set X_ 390.0
#$node_(1) set Y_ 385.0
#$node_(1) set Z_ 0.0

#
# Now produce some simple node movements
# Node_(1) starts to move towards node_(0)
#
#$ns_ at 50.0 "$node_(1) setdest 25.0 20.0 15.0"
#$ns_ at 10.0 "$node_(0) setdest 20.0 18.0 1.0"

# Node_(1) then starts to move away from node_(0)
#$ns_ at 100.0 "$node_(1) setdest 490.0 480.0 15.0" 

# Setup traffic flow between nodes
# TCP connections between node_(0) and node_(1)

source mobility.tcl
$node_(47) set X_ 2300.0 
$node_(47) set Y_ 5500.0
$node_(47) set Z_ 0.0 


$node_(48) set X_ 500.0 
$node_(48) set Y_ 5000.0
$node_(48) set Z_ 0.0 


$node_(49) set X_ 1000.0 
$node_(49) set Y_ 4600.0 
$node_(49) set Z_ 0.0 


#Third Party

$node_(50) set X_ 50.0 
$node_(50) set Y_ 2000.0
$node_(50) set Z_ 0.0 

 

$ns_ at 0.0 "$node_(47) setdest 2300.0 5500.0 1500.0"
$ns_ at 0.0 "$node_(48) setdest 500.0 5000.0 2000.0"
$ns_ at 0.0 "$node_(49) setdest 1000.0 4600.0 2000.0"

$ns_ at 0.0 "$node_(50) setdest 50.0 2000.0 1500.0"


$ns_ color 1 Green
$ns_ color 2 Black
$ns_ color 3 Red
$ns_ color 4 Blue

set vehlist [list 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46] 
set APlist [list 47 48 49 ]
set NM 47
set AP 3
set TP 3

#blah
#set server $node_(3)
#set router $node_(49)
#set client $node_(0)

#———- Creating Duplex Link—————-#




foreach nil $vehlist { 
	$ns_ at 0.0 "$node_($nil) add-mark m0 orange"
	
} 
foreach nia $APlist { 
	$ns_ at 0.0 "$node_($nia) add-mark m0 SeaGreen " 
	$ns_ at 0.0 "$node_($nia) label RSU" 
	
}

	$ns_ at 0.0 "$node_(50) add-mark m0 red"
	$ns_ at 0.0 "$node_(50) label Third_Party"
	


#Agent definition 
proc attach-cbr-traffic {node sink size interval} { 
	global ns_ 
	set source [new Agent/UDP] 
	$source set class_ 2 
	$ns_ attach-agent $node $source 
	set traffic [new Application/Traffic/CBR] 
	$traffic set packetSize_ $size 
	$traffic set interval_ $interval 
	$traffic attach-agent $source 
	$ns_ connect $source $sink 
	return $traffic 
} 


$ns_ duplex-link $node_(50) $node_(47) 1Mb 10ms DropTail
$ns_ duplex-link $node_(50) $node_(48) 1Mb 10ms DropTail
$ns_ duplex-link $node_(50) $node_(49) 1Mb 10ms DropTail


foreach nil $vehlist { 
set tcp [new Agent/TCP]
$ns_ attach-agent $node_($nil) $tcp
set sink [new Agent/TCPSink]
$ns_ attach-agent $node_(47) $sink
$ns_ connect $tcp $sink
set ftp [new Application/FTP]
$ftp attach-agent $tcp
$tcp set fid_ 1
$ns_ at 3.0 "$ftp start"
$ns_ at 500.0 "$ftp stop"


set tcp1 [new Agent/TCP]
$ns_ attach-agent $node_($nil) $tcp1
set sink1 [new Agent/TCPSink]
$ns_ attach-agent $node_(48) $sink1
$ns_ connect $tcp1 $sink1
set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1
$tcp1 set fid_ 2
$ns_ at 2.0 "$ftp1 start"
$ns_ at 500.0 "$ftp1 stop"


set tcp2 [new Agent/TCP]
$ns_ attach-agent $node_($nil) $tcp2
set sink2 [new Agent/TCPSink]
$ns_ attach-agent $node_(49) $sink2
$ns_ connect $tcp2 $sink2
set ftp2 [new Application/FTP]
$ftp2 attach-agent $tcp2
$tcp2 set fid_ 3
$ns_ at 3.0 "$ftp2 start"
$ns_ at 500.0 "$ftp2 stop"



}

#$ns_ at 0.5 "record"






#
# Tell nodes when the simulation ends
#
for {set i 0} {$i < $val(nn) } {incr i} {
    $ns_ at 500.0 "$node_($i) reset";
}
$ns_ at 500.0 "stop"
$ns_ at 500.01 "puts \"NS EXITING...\" ; $ns_ halt"
proc stop {} {
    global ns_ tracefd
    $ns_ flush-trace
    close $tracefd
}

puts "Starting Simulation..."
$ns_ run


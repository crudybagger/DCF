#include <stdio.h>
#include <string>
#include <omnetpp.h>
#include <math.h>
#include <cmessage.h>
#include <coutvector.h>
#include "User.h"
#include "param.h"
#include "packet_m.h"

Define_Module(User);
int User::no_users = 0;
User::User(){
    User::no_users += 1;
    id = User::no_users;
    rts = NULL;
    deferAccess = NULL;
    resumeAccess = NULL;

}
User::~User(){
    User::no_users -= 1;
    cancelAndDelete(rts);
    cancelAndDelete(deferAccess);
    cancelAndDelete(resumeAccess);
}

void User::initialize(){
    allowed = true;
    std::string s = "rts." + std::to_string(id);
    rts = new cMessage(s.c_str());
    start = new cMessage("start");
    scheduleAt(exponential(0.01), start);
    deferAccess = new cMessage("deferAccess");
    resumeAccess = new cMessage("resumeAccess");
}

void User::handleMessage(cMessage *msg){
    //pre-process the message
    std::string m = msg->getName();
     std::string m_type = "", m_id = "";
     bool id_start = false;
     for(char c : m){
         if(c == '.')
             id_start = true;
         else if(id_start)
             m_id.push_back(c);
         else
             m_type.push_back(c);
     }
     if(m_id.size() == 0)
         m_id.push_back('0');


     if(strcmp(m_type.c_str(), "deferAccess") == 0){
         allowed = false;
         cancelEvent(start);
     }
     else if(strcmp(m_type.c_str(), "resumeAccess") == 0){
         cancelEvent(start);
         allowed = true;
         scheduleAt(SIMTIME_DBL(simTime()+exponential(1/pow(10,6))), start);
     }
     else if(strcmp(m_type.c_str(), "start") == 0){
         if(allowed)
             sendDelayed(rts->dup(), exponential(DIFS), "out");
     }
     else if(strcmp(m_type.c_str(), "cts") == 0){

         if(std::stoi(m_id) != id){
             cancelEvent(deferAccess);
             cancelEvent(start);
             scheduleAt(SIMTIME_DBL(simTime()) + small_delay, deferAccess);
         }else{
             pack *p = new pack("data");
             p->setName("data");
             p->setTm(SIMTIME_DBL(simTime()));
             p->setSz(lr*obsTime);
             p->setId(id);
             sendDelayed(p, SIFS, "out");
         }

     }
     else if(strcmp(m_type.c_str(), "ack") == 0){
         cancelEvent(resumeAccess);
         scheduleAt(SIMTIME_DBL(simTime() + DIFS), resumeAccess);
     }
}


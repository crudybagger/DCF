#include <stdio.h>
#include <string>
#include <omnetpp.h>
#include <math.h>
#include <cmessage.h>
#include <coutvector.h>
#include "User.h"
#include "param.h"

Define_Module(User);
int User::no_users = 0;
User::User(){
    User::no_users += 1;
    id = User::no_users;
    rts = NULL;
    deferAccess = NULL;
    resumeAccess = NULL;
    allowed = true;
}
User::~User(){
    User::no_users -= 1;
    cancelAndDelete(rts);
    cancelAndDelete(deferAccess);
    cancelAndDelete(resumeAccess);
}

void User::initialize(){

    std::string s = "rts." + std::to_string(id);
    rts = new cMessage(s.c_str());
    start = new cMessage("start");
}

void User::handleMessage(cMessage *msg){
    //pre-process the message
    std::string m = msg->getName();
     std::string m_type, m_id;
     bool id_start = false;
     for(char c : m){
         if(c == '.')
             id_start = true;
         else if(id_start)
             m_id.push_back(c);
         else
             m_type.push_back(c);
     }
     if(strcmp(m_type.c_str(), "deferAccess") == 0){
         allowed = false;
         cancelAndDelete(start);
     }
     else if(strcmp(m_type.c_str(), "resumeAccess") == 0){
         allowed = true;
         scheduleAt(SIMTIME_DBL(simTime()), start);
     }
     else if(strcmp(m_type.c_str(), "start") == 0){
         if(allowed)
             sendDelayed(rts, exponential(DIFS), "out");
     }
     else if(strcmp(m_type.c_str(), "cts") == 0){
         if(std::stoi(m_id) == id){

         }
         else
             scheduleAt(SIMTIME_DBL(simTime()), deferAccess);
     }
}


#include <stdio.h>
#include <string>
#include <vector>
#include <omnetpp.h>
#include <math.h>
#include <cmessage.h>
#include <coutvector.h>
#include <set>
#include "AP.h"
#include "param.h"
#include "packet_m.h"
Define_Module(AP);

AP::AP(){
    cts = new cMessage("");
    ack = NULL;
}
AP::~AP(){
    cancelAndDelete(cts);
}
void AP::initialize(){
    curr = 0;
    ack = new cMessage("ack");
}
 void AP::handleMessage(cMessage *msg){
     //get the message and sender.
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
     //what if the message is...
     if(strcmp(m_type.c_str(),"rts") == 0){
         cancelEvent(cts);
         //A Request to Send(rts)
         //generate a CTS for current user
         std::string s = "cts." + m_id;
         cts = new cMessage(s.c_str());
//         double x = small_delay;
         sendDelayed(cts->dup(), SIFS, "out");
         for(int i = 1; i <= 5; i++){
             std::string o = "out" + std::to_string(i);
             sendDelayed(cts->dup(), SIFS, o.c_str());
//             x += small_delay;
         }

     }
     else if(strcmp(m_type.c_str(), "data") == 0){
         //we recieved a packet
         pack *p = check_and_cast<pack *>(msg);
         pkid[curr] = p->getId();
         curr++;
         delete p;
         //we send back an acknowlegement
//         double x = small_delay;
         sendDelayed(ack->dup(), SIFS, "out");
         for(int i = 1; i <= 5; i++){
             std::string o = "out" + std::to_string(i);
             sendDelayed(ack->dup(), SIFS, o.c_str());
//             x += small_delay;
         }
     }
 }

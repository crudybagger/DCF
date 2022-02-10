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
Define_Module(AP);

AP::AP(){
    cts = NULL;
}
AP::~AP(){
    cancelAndDelete(cts);
}
void AP::initialize(){

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
         //A Request to Send(rts)
         //generate a CTS for current user
         std::string s = "cts." + m_id;
         cts = new cMessage(s.c_str());
         sendDelayed(cts, SIFS, "out");
     }
 }

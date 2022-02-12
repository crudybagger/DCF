#ifndef AP_H_
#define AP_H_

class AP : public cSimpleModule {
public:
    cMessage *cts, *ack;
    int pkid[1000];
    int curr;

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *str);
public:
    AP();
    virtual ~AP();
};

#endif /* AP_H_ */

/*
 * User.h
 *
 *  Created on: 09-Feb-2022
 *      Author: ASUS
 */

#ifndef USER_H_
#define USER_H_


class User : public cSimpleModule {

public:
    static int no_users;
    int id;
    bool allowed;
    cMessage *rts, *deferAccess, *resumeAccess;
    cMessage *start;
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
public:
    User();
    virtual ~User();
};

#endif /* USER_H_ */

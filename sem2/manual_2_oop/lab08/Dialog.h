#ifndef VYSOKOV_VLADIMIR_RIS_25_2B_LABS_PSTU_CS_DIALOG_H
#define VYSOKOV_VLADIMIR_RIS_25_2B_LABS_PSTU_CS_DIALOG_H
#include "Event.h"
#include "Vector.h"

class Dialog : public Vector {
public:
    Dialog();
    virtual ~Dialog();
    virtual void GetEvent(Event &event);
    virtual int Execute();
    virtual void handleEvent(Event &event);
    virtual void ClearEvent(Event &event);
    int Valid();
    void EndExec();
protected:
    int EndState;
};


#endif //VYSOKOV_VLADIMIR_RIS_25_2B_LABS_PSTU_CS_DIALOG_H

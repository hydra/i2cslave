/*
 Copyright (c) 2012-2013 Dominic Clifton.  All right reserved.
 */
#ifndef SCHEDULEDACTION_H
#define SCHEDULEDACTION_H

#ifdef LINUX
#include <sys/time.h>
#endif

class ScheduledAction {
public:
  void reset();
  void setDelayMicros(unsigned long delayMicros);
  void setDelayMillis(unsigned long delayMillis);
  unsigned long getLateBy(void);
  int getMissedActions(void);
  bool isActionDue(void);

private:
#ifdef LINUX
  timeval tempTime;
  unsigned long micros(void);
#endif

  unsigned long nextActionAt;
  unsigned long delayMicros;
  unsigned int missedActions;
  unsigned long lateBy;

};

#endif

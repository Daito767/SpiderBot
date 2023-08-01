#ifndef COMMAND_H
#define COMMAND_H

#include <Arduino.h>

struct Command {
  String type;
  int count;
  int speed;
};

#endif // COMMAND_H

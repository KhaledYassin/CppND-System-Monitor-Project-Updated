#include <iostream>
#include <thread>
#include <chrono>

#include "cpu.h"
#include "linux_parser.h"
#include "ncurses_display.h"
#include "system.h"

int main() {
  System system;
  NCursesDisplay::Display(system);
  return 0;
}
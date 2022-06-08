#include "user.h"
#include <stdio.h>

// Greetings and
int main() {

  User user = {"Big", "Lebowski", 42};
  StandardGreeting(&user);
  FormalGreeting(&user);
  InformalGoodbye(&user);
  FormalGoodbye(&user);

  return 0;
}


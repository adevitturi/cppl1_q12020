#include <iostream>
#include <vector>

#include "vector3.h"

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  const ekumen::math::Vector3 p(1, 2, 3);
  ekumen::math::Vector3 q;
  q = p;

  std::cout << "Hello world." << std::endl;

  return 0;
}

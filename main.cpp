#include <iostream>
#include <string>

int main(int argc, char **argv) {

if(argc != 3) {
  std::cerr << "please specify environment variable name to print and expected output" << std::endl;
  return EXIT_FAILURE;
}

char* enval = std::getenv(argv[1]);
if(!enval) {
  std::cerr << "environment variable " << argv[1] << " not found/set" << std::endl;
  return EXIT_FAILURE;
}

std::string pat(argv[2]);
std::string val(enval);

std::cout << val << std::endl;

if(val != pat) {
  std::cerr << "expected output does not match" << std::endl;
  return EXIT_FAILURE;
}

return EXIT_SUCCESS;
}

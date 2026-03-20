#include "utils.h"
#include <sstream>
using namespace std;

unsigned int ConvertStrToUnsigned(const char *value) {
  stringstream strValue;
  strValue << value;
  unsigned int intValue;
  strValue >> intValue;
  return intValue;
}

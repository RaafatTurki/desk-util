#include "./utils.h"

bool strtob(const string& str) {
  string lower_str = str;
  transform(lower_str.begin(), lower_str.end(), lower_str.begin(), ::tolower);

  if (lower_str == "true" || lower_str == "1" || lower_str == "yes" || lower_str == "on") {
    return true;
  } else if (lower_str == "false" || lower_str == "0" || lower_str == "no" || lower_str == "off") {
    return false;
  } else {
    // Default to false for unrecognized input
    return false;
  }
}

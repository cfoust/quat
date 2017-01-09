#include "Utils.h"

namespace QUAT {
std::string fa_icon(const char16_t * icon) {
  std::string iconString;
  cocos2d::StringUtils::UTF16ToUTF8(icon, iconString);
  return iconString;
}
};

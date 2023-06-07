#include "lib.hpp"
#include "pugixml.hpp"
#include <cstring>
#include <iostream>
#include <list>
#include <string_view>
#include <vector>

std::string_view getShortName(pugi::xml_node node) {
  return node.find_child([](pugi::xml_node node) { return node.name() == std::string_view{"SHORT-NAME"}; })
      .text()
      .as_string();
}

std::string getPath(pugi::xml_node node) {
  if (node.empty()) {
    return "";
  }
  std::vector<pugi::xml_node> paths{};
  for (pugi::xml_node i = node; !i.empty(); i = i.parent()) {
    paths.push_back(i);
  }
  std::string result;
  for (auto it = paths.rbegin(); it != paths.rend(); it++) {
    std::string_view short_name = getShortName(*it);
    if (short_name.empty()) {
      continue;
    }
    result += "/";
    result += short_name;
  }
  return result;
}

bool load(std::string_view path) {
  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file(path.data());
  return result;
}
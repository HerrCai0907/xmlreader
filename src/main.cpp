#include "pugixml.hpp"
#include <cstring>
#include <iostream>
#include <list>
#include <ranges>
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

int main(int argc, char *argv[]) {
  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file(argv[1]);
  if (!result)
    return -1;

  for (;;) {
    std::string cmd;
    std::cin >> cmd;

    for (auto const xpath_node : doc.select_nodes(cmd.c_str())) {
      xpath_node.node().print(std::cout, "  ");
      std::cout << getPath(xpath_node.node()) << "\n";
    }
  }
}

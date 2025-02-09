#include "tool_type.hpp"

Tool_type* Tool_type::shovel = new Tool_type("SHVL");
Tool_type* Tool_type::hoe = new Tool_type("HOE");
Tool_type* Tool_type::sword = new Tool_type("SWRD");
Tool_type* Tool_type::pickaxe = new Tool_type("PICK");
Tool_type* Tool_type::axe = new Tool_type("AXE");

Tool_type::Tool_type(char* name) : name{name}
{
}
Tool_type::~Tool_type()
{
}

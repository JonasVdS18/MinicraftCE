#ifndef TOOL_TYPE_HPP
#define TOOL_TYPE_HPP
class Tool_type
{
  public:
    Tool_type(char* name);
    ~Tool_type();
    char* name;
    static Tool_type* shovel;
    static Tool_type* hoe;
    static Tool_type* sword;
    static Tool_type* pickaxe;
    static Tool_type* axe;
};
#endif

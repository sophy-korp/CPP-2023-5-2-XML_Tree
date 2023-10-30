#pragma once
#include<fstream>
#include<vector>

class XML_Node {
public:
    XML_Node(const std::string& tag, const int& value, std::weak_ptr<XML_Node> parent)
        : m_tag(tag), m_val(value), m_parent(parent) {};
    ~XML_Node() = default;
    void AddChild(std::shared_ptr<XML_Node> child);
    int GetVal();
    std::string GetTag();
    void SetParent(std::weak_ptr<XML_Node> new_parent);
    void EraseChild(std::shared_ptr<XML_Node> child);
    std::weak_ptr<XML_Node> GetParent();
    void Save(std::ofstream& file, std::string tab = "");
    void ChildrenToParent();

private:
    std::weak_ptr<XML_Node> m_parent;
    std::string m_tag;
    int m_val;
    std::vector<std::shared_ptr<XML_Node>> m_children;
};

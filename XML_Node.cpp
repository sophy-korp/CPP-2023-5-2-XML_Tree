#include"XML_Node.h"

void XML_Node::AddChild(std::shared_ptr<XML_Node> child) {
    m_children.push_back(child);
}

int XML_Node::GetVal() {
    return m_val;
}

std::string XML_Node::GetTag() {
    return m_tag;
}

void XML_Node::SetParent(std::weak_ptr<XML_Node> new_parent) {
    m_parent = new_parent;
}

void XML_Node::EraseChild(std::shared_ptr<XML_Node> child) {
    m_children.erase(std::find(m_children.begin(), m_children.end(), child));
}

std::weak_ptr<XML_Node> XML_Node::GetParent() {
    return m_parent;
}

void XML_Node::Save(std::ofstream& file, std::string tab) {

    file << tab + "<" + m_tag + "> " << m_val << std::endl;
    for (auto&& child : m_children) {
        child->Save(file, tab + "    ");
    }
    file << tab + "</" + m_tag + "> " << std::endl;
}

void XML_Node::ChildrenToParent() {
    for (auto&& child : m_children) {
        child->SetParent(m_parent);
        m_parent.lock()->AddChild(child);
    }
}


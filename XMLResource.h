#pragma once
#include<memory>
#include<string>
#include<list>
#include "XML_Node.h"

using iterator = std::list<std::shared_ptr<XML_Node>>::iterator;
class XMLResource {
public:
	
	static std::unique_ptr<XMLResource> Create(const std::string& path);
	void Save(const std::string& path);
	void Load(const std::string& path);
	iterator Add(const std::string& tag, const int& value, const iterator& parent);
	iterator Find(const int& val);
	iterator Find(const std::string& tag);
	bool Erase(iterator it);
	iterator begin();
	iterator end();
private:
	class XMLResourceClone;
	XMLResource() = default;
	std::list<std::shared_ptr<XML_Node>> m_vertices;
};

class XMLResource::XMLResourceClone : public XMLResource {
	using XMLResource::XMLResource;
};

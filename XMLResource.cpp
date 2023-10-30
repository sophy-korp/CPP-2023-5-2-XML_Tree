#include"XMLResource.h"
#include<iostream>
#include<fstream>
#include<sstream>

iterator XMLResource::begin() {
	return m_vertices.begin();
}

iterator XMLResource::end() {
	return m_vertices.end();
}

iterator XMLResource::Find(const int& val) {
	iterator it = begin();
	while (it != end()) {
		if ((*it)->GetVal() == val) {
			return it;
		}
		it++;
	}
	return it;
}

iterator XMLResource::Find(const std::string& tag) {
	iterator it = begin();
	while (it != end()) {
		if ((*it)->GetTag() == tag) {
			return it;
		}
		it++;
	}
	return it;
}

iterator XMLResource::Add(const std::string& tag, const int& value, const iterator& parent) {
	std::shared_ptr<XML_Node> node = std::make_shared<XML_Node>(tag, value, *parent);
	(*parent)->AddChild(node);
	m_vertices.push_back(node);
	return std::find(begin(), end(), node);
}

bool XMLResource::Erase(iterator it) {
	try {
		if ((*it)->GetParent().expired()) {
			throw std::exception();
		}
		(*it)->ChildrenToParent();
		(*it)->GetParent().lock()->EraseChild(*it);
		m_vertices.erase(it);
		return true;
	}
	catch (...) {
		return false;
	}
}

std::unique_ptr<XMLResource> XMLResource::Create(const std::string& path) {
	std::unique_ptr<XMLResource> tree = std::make_unique<XMLResourceClone>();
	try {
		tree->Load(path);
	}
	catch (...) {
		std::cout << "Load error" << std::endl;
		tree = std::make_unique<XMLResourceClone>();
	}
	return tree;
}

void XMLResource::Load(const std::string& path) {
	std::ifstream input_file;
	input_file.open(path, std::ios::in);

	if (!input_file.is_open()) {
		throw std::exception();
	}

	std::string word;
	std::weak_ptr<XML_Node> parent;
	while (input_file >> word) {
		if (word[0] == '<' && word[word.size() - 1] == '>') {
			if (word[1] == '/') {
				parent = parent.lock()->GetParent();
			}
			else {
				word.erase(0, 1);
				word.erase(word.end() - 1);
				int value;

				if (!(input_file >> value)) {
					throw std::exception();
				}

				std::shared_ptr<XML_Node> node = std::make_shared<XML_Node>(word, value, parent);
				if (!parent.expired()) {
					parent.lock()->AddChild(node);
				}
				m_vertices.push_back(node);
				parent = node;
			}
		}

		else {
			throw std::exception();
		}
	}
}

void XMLResource::Save(const std::string& path) {
	std::ofstream output_file;
	output_file.open(path, std::ios::out);
	(*m_vertices.begin())->Save(output_file);
}

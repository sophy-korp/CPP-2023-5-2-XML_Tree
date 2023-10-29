#include"XMLResource.h"

int main() {
	const std::string path = "C:\\Users\\Admin\\source\\repos\\Lab2_XMLTree\\Lab2_XMLTree\\tree.txt";
	std::unique_ptr<XMLResource> resource = XMLResource::Create(path);
	resource->Save("output.txt");
	iterator it = resource->Find(4);
	resource->Add("new", 5, it);
	it = resource->Find(4);
	resource->Erase(it);
	resource->Save("output2.txt");
	return 0;
}
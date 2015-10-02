
#pragma once

#include "Model/XMLSettings/DOM/dom_document.h"
#include "Model/XMLSettings/DOM/dom_element.h"
#include "Model/XMLSettings/DOM/dom_node.h"

class XMLSettings;

class XMLSettingsAppModel
{
public:
	XMLSettingsAppModel();

	void load(const std::string &filename);
	void load(uicore::IODevicePtr device);
	void save(const std::string &filename);
	void save(uicore::IODevicePtr device);

	XMLSettings get_root();

private:
	DomDocument document;
};


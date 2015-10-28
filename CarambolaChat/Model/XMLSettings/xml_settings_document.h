
#pragma once

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
	uicore::XmlDocumentPtr document;
};


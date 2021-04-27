#pragma once

#include <string>
#include <vector>
#include <Volt.hpp>

struct InventoryItem {
	std::string name, description;
	volt::Texture thumbnail;

	InventoryItem(const std::string& name, const std::string& description, const std::string& thumbnail_path);
};

class Inventory {
private:
	std::vector<InventoryItem*> m_items;
	InventoryItem* m_selected;
public:
	Inventory();
	~Inventory();
	void AddItem(const std::string& name, const std::string& description, const std::string& thumbnail_path);
	bool HasItem(const std::string& name);

	void Draw(volt::Window& window);

	const std::vector<InventoryItem*>& GetItems();
};

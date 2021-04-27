#pragma once
#include "core/Inventory.hpp"
#include <algorithm>
#include "ui/MultiLineLabel.hpp"

InventoryItem::InventoryItem(const std::string& name, const std::string& description, const std::string& thumbnail_path) : name(name), description(description), thumbnail(thumbnail_path) {
}

Inventory::Inventory() : m_selected(nullptr) {}

Inventory::~Inventory() {
	for (auto item : m_items) {
		delete item;
	}
}

void Inventory::AddItem(const std::string& name, const std::string& description, const std::string& thumbnail_path) {
	m_items.emplace_back(new InventoryItem(name, description, thumbnail_path));
}

bool Inventory::HasItem(const std::string& name) {
	auto found = std::find_if(m_items.begin(), m_items.end(), [&name](const InventoryItem* item) {return item->name == name; });
	if (found != m_items.end()) {
		return true;
	}
	return false;
}

void Inventory::Draw(volt::Window& window) {
	volt::Vec2 size = { (float)window.getSize().x, (float)window.getSize().y };
	volt::Vec2 mouse_pos = { (float)window.getMousePos().x, (float)window.getMousePos().y };
	
	volt::Quad main_panel({ 0.1f * size.width, 0.05f * size.height }, { 0.8f * size.width, 0.8f * size.height }, {0.1f,0.1f,0.1f,0.67f});
	window.drawQuad(main_panel, SEPERATE);

	if (m_selected) {
		volt::Font* font = volt::Font::get(volt::fonts::SEGOE);
		float text_width = font->widthOf(m_selected->name, size.height * 0.10f);

		MultiLineLabel desc(m_selected->description, "width: " + std::to_string((main_panel.size.width * 0.98f) - (main_panel.size.height * 0.80f)) + "px;height: 64%;left: " + std::to_string(main_panel.pos.x + (main_panel.size.width * 0.03f) + (main_panel.size.height * 0.80f)) + "px;bottom: 30%;text-size: 0.06h;text-colour:#FFFFFF;");
		Environment env;
		env.window = &window;
		desc.Update(env);
		desc.Draw(window);
		window.drawString(m_selected->name, { main_panel.pos.x + (main_panel.size.width / 2.0f) - (text_width / 2.0f), main_panel.pos.y + (main_panel.size.height * 0.90f)}, size.height * 0.10f, volt::fonts::SEGOE, {1.0f,1.0f,1.0f,1.0f});
		window.drawTexture(m_selected->thumbnail, { main_panel.pos.x + (main_panel.size.width * 0.01f), main_panel.pos.y + (main_panel.size.height * 0.02f) }, {main_panel.size.height * 0.80f,main_panel.size.height * 0.80f });

		volt::Vec4 col = { 1.0f,1.0f,1.0f,1.0f };

		if (mouse_pos.x >= main_panel.pos.x + (main_panel.size.width * 0.02f) && mouse_pos.x <= main_panel.pos.x + (main_panel.size.width * 0.02f) + font->widthOf("Back", 0.06f * size.height)) {
			if (mouse_pos.y >= main_panel.pos.y + (main_panel.size.height * 0.87f) && mouse_pos.y <= main_panel.pos.y + (main_panel.size.height * 0.93f)) {
				col = { 0.07f,0.53f, 0.66f,1.0f };
				if (window.isMouseJustPressed()) {
					m_selected = nullptr;
				}
			}
			
		}
		
		window.drawString("Back", { main_panel.pos.x + (main_panel.size.width * 0.02f), main_panel.pos.y + (main_panel.size.height * 0.9f) }, 0.06f * size.height, volt::fonts::SEGOE, col);
	}
	else {
		for (int i = 0; i < m_items.size(); i++) {
			float px = main_panel.pos.x + (0.02f * main_panel.size.width) + (0.14f * (float)(i % 7) * main_panel.size.width);
			float py = (0.65f * size.height) - ((float)(i / 7) * 0.14f * main_panel.size.width);
			float sx = main_panel.size.width * 0.12f;
			window.drawTexture(m_items[i]->thumbnail, { px, py }, { main_panel.size.width * 0.12f,main_panel.size.width * 0.12f });

			if (mouse_pos.x >= px && mouse_pos.x <= px + sx && mouse_pos.y >= py && mouse_pos.y <= py + sx) {
				volt::Quad hover({ px, py }, { sx,sx }, { 0.2f,0.2f,0.2f,0.5f });
				window.drawQuad(hover, SEPERATE);
				if (window.isMouseJustPressed()) {
					m_selected = m_items[i];
				}
			}
		}
	}

	
}

const std::vector<InventoryItem*>& Inventory::GetItems() {
	return m_items;
}

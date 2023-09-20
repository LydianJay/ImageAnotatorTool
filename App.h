#pragma once
#include "GLSimp2DWidget.h"
#include "stb_image/stb_image.h"
#include "stb_image_write.h"
#include <iostream>
#include <memory>
#include <vector>


class App {

public:
	
	App();

	void runApp();
private:
	void handlePixelEdit(s2d::MouseState ms, s2d::KeyState ks);
	

private:
	uint32_t m_width = 800, m_height = 800;
	s2d::Texture m_texture;
	bool m_isAlreadyLoaded = false;
	std::shared_ptr<s2d::S2DGraphics> m_graphics;
	std::shared_ptr<s2d::S2DWindow> m_window;
	s2d::Color* m_pixelData = nullptr;
	uint32_t m_pointCount = 0, m_rectCount = 0;
	s2d::Vec2f m_startPos = { 0,0 }, m_endPos = {0, 0};
	bool m_renderLine = false;
	bool m_show = true;
	std::vector<std::pair<s2d::Vec2f, s2d::Vec2f>> m_lines;


};


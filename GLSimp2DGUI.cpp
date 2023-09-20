#include "GLSimp2DGUI.h"

s2d::S2DGUI::S2DGUI() {
	m_graphics = nullptr; m_width = 0; m_height = 0;
}

s2d::S2DGUI::S2DGUI(S2DGraphics* g) {
	m_graphics = g;
	g->getScreenParam(&m_width, &m_height);
}

void s2d::S2DGUI::initGUI(S2DGraphics* g) {
	m_graphics = g;
	g->getScreenParam(&m_width, &m_height);
}

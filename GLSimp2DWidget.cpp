#include "GLSimp2DWidget.h"

#include <iostream>
s2d::GLWidgetBase::GLWidgetBase(std::string text, float x, float y, float w, float h) {
	m_text = text; m_x = x; m_y = y; m_width = w; m_height = h;
}

void s2d::GLWidgetBase::setText(std::string text) {
	m_text = text;
}

std::string s2d::GLWidgetBase::getText() {
	return m_text;
}

void s2d::GLWidgetBase::setSize(float w, float h) {
	m_width = w; m_height = h;
}

s2d::Vec2f s2d::GLWidgetBase::getSize() {
	return {m_width, m_height};
}

void s2d::GLWidgetBase::setPos(float x, float y) {
	m_x = x; m_y = y;
}

s2d::Vec2f s2d::GLWidgetBase::getPos() {
	return {m_x, m_y};
}

void s2d::GLWidgetBase::setTextSize(float w, float h) {
	m_tW = w; m_tH = h;
}

s2d::Vec2f s2d::GLWidgetBase::getTextSize() {
	return {m_tW, m_tH};
}

void s2d::GLWidgetBase::setBackgroundColor(s2d::Color clr) {
	m_bg = clr;
}


void s2d::GLWidgetBase::setBorderColor(s2d::Color clr) {
	m_borderColor = clr;
}

void s2d::GLWidgetBase::draw(s2d::S2DGraphics* g) {
	g->drawWireFrameRect({ m_x, m_y }, {m_width, m_height}, m_bSize, m_borderColor);
	
	uint32_t tSize = m_text.size();
	float w = ((float)m_width / tSize);


	g->drawString(m_text, m_x + (w * 0.2), m_y + (((float)m_height * 0.2) / 2.0), w - ((float)w * 0.2), m_height - ((float)m_height * 0.2));


}

s2d::GLWidgetLabel::GLWidgetLabel() : GLWidgetBase(){
}

s2d::GLWidgetLabel::GLWidgetLabel(std::string text, float x, float y, float w, float h) :GLWidgetBase(text, x, y, w, h) {}





s2d::GLWidgetTextBox::GLWidgetTextBox() : GLWidgetBase(){}

s2d::GLWidgetTextBox::GLWidgetTextBox(uint32_t charCount, float x, float y, float tW, float tH) : GLWidgetBase("", x, y, tW * (charCount + 1), tH) {
	m_maxChar = charCount;
}

void s2d::GLWidgetTextBox::setMaxChar(uint32_t c) {
	m_maxChar = c;
	
}

void s2d::GLWidgetTextBox::update(s2d::KeyState ks, s2d::MouseState ms) {
	
	s2d::Vec2f pos = this->getPos();
	s2d::Vec2f sz = this->getSize();
	

	if (ms.state == S2D_MOUSE_CLICK) {
		
		m_isActive = ((ms.pos.x >= pos.x && ms.pos.x <= pos.x + sz.x) && (ms.pos.y >= pos.y && ms.pos.y <= pos.y + sz.y));
	}

	
	if (m_isActive) {
		setBorderColor(s2d::PXLCLR_GREEN);
		if (ks.state == S2D_KEY_PRESSED) {

			if ( (ks.key >= 'A' && ks.key <= 'Z') || (ks.key >= '0' && ks.key <= '9')) {
				std::string text = this->getText();
				
				if (text.size() < m_maxChar) {

					text.push_back(ks.key);
					this->setText(text);

				}

				
			}
			else if (ks.key == VK_BACK) {
				std::string text = this->getText();
				if(!text.empty()){
					text.pop_back();
					this->setText(text);
				}
					
			}
		}

	}
	else {
		setBorderColor(s2d::PXLCLR_RED);
	}
	

}

void s2d::GLWidgetTextBox::draw(s2d::S2DGraphics* g){
	
	g->drawWireFrameRect({ m_x, m_y }, { m_width, m_height }, m_bSize, m_borderColor);
	float w = ((float)m_width / m_maxChar);
	g->drawString(m_text, m_x + (w * 0.2), m_y + (((float)m_height * 0.2) / 2.0), w - ((float)w * 0.2), m_height - ((float)m_height * 0.2));

}

s2d::GLWidgetButton::GLWidgetButton() : GLWidgetBase(){}

bool s2d::GLWidgetButton::isPressed() {
	
	
	return m_wasPressed;
}

void s2d::GLWidgetButton::draw(s2d::S2DGraphics* g) {

	

	//g->drawWireFrameRect({ m_x, m_y }, { m_width, m_height }, m_bSize, m_borderColor);
	g->drawRect( m_x - (m_width * 0.15), m_y - (m_height * 0.15), m_width + (m_width * 0.15) / 2, m_height + (m_height * 0.15), m_bg);
	float w = ((float)m_width / m_text.size());
	g->drawString(m_text, m_x + (w * 0.2), m_y + (((float)m_height * 0.2) / 2.0), w - ((float)w * 0.2), m_height - ((float)m_height * 0.2));


}

void s2d::GLWidgetButton::update(s2d::MouseState ms) {

	s2d::Vec2f pos = this->getPos();
	s2d::Vec2f sz = this->getSize();
	if (ms.state == S2D_MOUSE_CLICK) {

		if ((ms.pos.x >= pos.x && ms.pos.x <= pos.x + sz.x) && (ms.pos.y >= pos.y && ms.pos.y <= pos.y + sz.y)) {
			setBorderColor(s2d::PXLCLR_BLUE);
			m_wasPressed = true;
			return;
		}
		
		
	}
	m_wasPressed = false;
	setBorderColor(s2d::PXLCLR_RED);
}

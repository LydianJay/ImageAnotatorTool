#pragma once
#include <string>
#include "gls2d/GLSimp2DGraphics.h"
namespace s2d {
	


	class GLWidgetBase {
	public:
		GLWidgetBase() = default;
		GLWidgetBase(std::string text, float x, float y, float w, float h);
		void setText(std::string text);
		std::string getText();
		void setSize(float w, float h);
		s2d::Vec2f getSize();
		void setPos(float x, float y);
		s2d::Vec2f getPos();
		void setTextSize(float w, float h);
		s2d::Vec2f getTextSize();

		void setBackgroundColor(s2d::Color clr);
		void setBorderColor(s2d::Color clr);
		virtual void draw(s2d::S2DGraphics* g);


	protected:
		std::string m_text;
		float m_width = 0, m_height = 0, m_x = 0, m_y = 0;
		float m_bSize = 1;
		float m_tW, m_tH;
		s2d::Color m_bg = s2d::PXLCLR_BLACK;
		s2d::Color m_borderColor = s2d::PXLCLR_WHITE;


	};


	class GLWidgetLabel : public GLWidgetBase {
	public:
		GLWidgetLabel();

		GLWidgetLabel(std::string text, float x, float y, float w, float h);
	private:


	};


	class GLWidgetTextBox : public GLWidgetBase {
	public:
		GLWidgetTextBox();
		GLWidgetTextBox(uint32_t charCount, float x, float y, float tW, float tH);
		void setMaxChar(uint32_t c);
		void update(s2d::KeyState ks, s2d::MouseState ms);
		void draw(s2d::S2DGraphics* g) override;
	private:
		bool m_isActive = false;
		uint32_t m_maxChar = 1;
	};


	class GLWidgetButton : public GLWidgetBase {
	public:
		GLWidgetButton();
		bool isPressed();
		void draw(s2d::S2DGraphics* g) override;
		void update(s2d::MouseState ms);
		
	private:
		bool m_wasPressed = false;
		
	};







}



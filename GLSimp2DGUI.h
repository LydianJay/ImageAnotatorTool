#pragma once
#include "gls2d/GLSimp2DGraphics.h"



namespace s2d {



	class S2DGUI {
	public:
		S2DGUI();
		S2DGUI(S2DGraphics* ctx);
		void initGUI(S2DGraphics* ctx);
		




	private:
		uint32_t m_width, m_height;
		S2DGraphics* m_graphics;


	};





}




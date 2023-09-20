#include "App.h"



App::App() {


	m_window = std::make_shared<s2d::S2DWindow>(m_width,m_height, "AnnotatorApp", S2D_WINDOW_NO_RESIZE);
	m_graphics = std::make_shared<s2d::S2DGraphics>(*m_window);
	m_graphics->initGlyphs(s2d::PXLCLR_WHITE, s2d::PXLCLR_BLACK);
	
}

void App::runApp() {



	
	
	
	s2d::GLWidgetButton button;
	button.setText("OPEN");
	button.setSize(100, 50);
	button.setPos(0, 0);
	button.setBackgroundColor({125,125,125});
	
	s2d::GLWidgetButton saveButton;
	saveButton.setText("SAVE");
	saveButton.setSize(100, 50);
	saveButton.setPos(150, 0);
	saveButton.setBackgroundColor({ 125,125,125 });


	while (!m_window->WindowShouldClose()) {
		
		s2d::KeyState ks = m_window->GetKeyState();
		s2d::MouseState ms = m_window->GetMouseState();


		

		handlePixelEdit(ms, ks);

		if (button.isPressed()) {
			
			char buffer[MAX_PATH];
			m_window->openFileExplorer(buffer, MAX_PATH);
			int x, y, z;
			unsigned char* data = stbi_load(buffer, &x, &y, &z, 4);
			
			if(!m_isAlreadyLoaded) {
				
				m_texture = m_graphics->createTexture(data, x, y);
				m_isAlreadyLoaded = true;
				m_pixelData = reinterpret_cast<s2d::Color*>(data);
				
			}
			else {
				stbi_image_free(m_pixelData);
				m_pixelData = reinterpret_cast<s2d::Color*>(data);
				m_graphics->resetTexture(data, x, y, &m_texture);
			}
		}


		if (saveButton.isPressed()) {

			
			
			
			if (m_isAlreadyLoaded) {

				char filePath[MAX_PATH];
				memset(filePath, 0, MAX_PATH);
				if (m_window->saveFileExplorer(filePath, MAX_PATH)) {
					int w, h;
					stbi_write_png(filePath, m_texture.width, m_texture.height, 4, (const void*)m_pixelData, m_texture.width * 4);
				}
				else {
					DWORD dwError = CommDlgExtendedError();
					if (dwError != 0) {
						MessageBoxA(NULL, "Error occurred!", "Error", MB_ICONERROR | MB_OK);
						std::cout << dwError << '\n';
					}
					else {
						MessageBoxA(NULL, "Save operation canceled by user!", "Canceled", MB_ICONWARNING | MB_OK);
					}
				}
			}
		}

		if(m_isAlreadyLoaded)
			m_graphics->drawRect(0, 0, m_width, m_height, s2d::PXLCLR_WHITE, m_texture);

		if (m_renderLine) {
			m_graphics->drawLine({ m_startPos.x, m_startPos.y }, { m_endPos.x, m_endPos.y }, 1.0f, s2d::PXLCLR_WHITE);
		}

		for (auto& l : m_lines) {

			auto v1 = l.first, v2 = l.second;

			
			m_graphics->drawLine({ v1.x, v1.y }, { v2.x, v2.y }, 1.0f, s2d::PXLCLR_RED);
		}


		button.update(ms);
		button.draw(m_graphics.get());
		saveButton.update(ms);
		saveButton.draw(m_graphics.get());

		m_graphics->flushBuffer();
		m_window->SwapWindowBuffers();
		m_window->ProcessMessage();
		
	}


}

void App::handlePixelEdit(s2d::MouseState ms, s2d::KeyState ks) {

	s2d::Vec2f pos = ms.pos;
	if(ms.state == S2D_MOUSE_CLICK){
		m_startPos = pos;
	}
	else if (ms.state == S2D_MOUSE_HELD) {
		
		m_endPos = pos;
		m_renderLine = true;
	}
	else if(ms.state == S2D_MOUSE_RELEASED) {
		m_renderLine = false;
		
		m_lines.push_back(std::make_pair(m_startPos, m_endPos));

	}
	

	if (ks.state == S2D_KEY_PRESSED) {

		switch (ks.key) {
		case 'Z':
			if (!m_lines.empty())
				m_lines.pop_back();
			break;
		default:
			break;
		}
	}






}


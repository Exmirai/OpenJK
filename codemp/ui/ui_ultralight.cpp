/*
===========================================================================
Copyright (C) 2013 - 2015, OpenJK contributors

This file is part of the OpenJK source code.

OpenJK is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License version 2 as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, see <http://www.gnu.org/licenses/>.
===========================================================================
*/

// cl_main.c  -- client main loop

#include "ui_local.h"
#include <string>
#include <vector>
#include "Ultralight/Ultralight.h"
#include <JavaScriptCore/JavaScript.h>

using namespace ultralight;

class PageLoadListener : LoadListener {
	///
	/// Called when the page begins loading new URL into main frame
	///
	void OnBeginLoading(ultralight::View* caller) {
	
	}

	///
	/// Called when the page finishes loading URL into main frame
	///
	void OnFinishLoading(ultralight::View* caller) {
	
	}

	///
	/// Called when the history (back/forward state) is modified
	///
	void OnUpdateHistory(ultralight::View* caller) {
	
	}

	///
	/// Called when all JavaScript has been parsed and the document is ready.
	/// This is the best time to make any initial JavaScript calls to your page.
	///
	void OnDOMReady(ultralight::View* caller) {

	}
};


// Injector
void UI_Injector_WriteMemory(void) {

}



//
RefPtr<Renderer> _renderer;
RefPtr<View> _view;
PageLoadListener listener;

void UI_Ultralight_LoadMenus(void) {
	fileHandle_t h;
	size_t len = trap->FS_Open("menus/html/main.html", &h, FS_READ);
	char* str = (char*)malloc(len + 1);
	trap->FS_Read(str, len, h);
	String buffer(str);
	_view->LoadHTML(buffer);
}

void UI_Ultralight_Init(void) {
	_renderer = Renderer::Create();
	_view = _renderer->CreateView(uiInfo.uiDC.glconfig.vidWidth, uiInfo.uiDC.glconfig.vidHeight, false);
	_view->set_load_listener(listener);
	UI_Ultralight_LoadMenus();
}

void UI_Ultralight_Update(void) {
	_renderer->Update();
	_renderer->Render();
}

void UI_Ultralight_Render(void) {
	RefPtr<Bitmap> bm = _view->bitmap();
	bm->LockPixels();

	bm->UnlockPixels();
}

void UI_Ultralight_KeyEvent(int key, qboolean down) {
	KeyEvent ke;
	ke.native_key_code = key;
	_view->FireKeyEvent(ke);
}

void UI_Ultralight_MouseEvent(int dx, int dy) {
	MouseEvent me;
	me.x = dx;
	me.y = dy;
	_view->FireMouseEvent(me);

}

void UI_Ultralight_Shutdown(void) {
	_view->Release();
	_renderer->Release();
}
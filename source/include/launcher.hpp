/*
 *	 Copyright (C) 2018 Qub³d Engine Group.
 *	 All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without modification,
 *  are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice, this
 *  list of conditions and the following disclaimer.
 *
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *  this list of conditions and the following disclaimer in the documentation and/or
 *  other materials provided with the distribution.
 *
 *  3. Neither the name of the copyright holder nor the names of its contributors
 *  may be used to endorse or promote products derived from this software without
 *  specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 *  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

// This tells the compiler to not use SDL's main function
#ifndef SDL_MAIN_HANDLED
	#define SDL_MAIN_HANDLED
#endif

// This tells GLEW that it's using a static lib
#ifndef GLEW_STATIC
	#define GLEW_STATIC
#endif

#include <memory>
#include <cstdio>
#include <GL/glew.h>
#include <logging/logging.hpp>
#include <SDL.h>
#include <SDL_events.h>

class Launcher
{
public:
	Launcher();
	~Launcher();

	void run();
	bool isRunning();
	void setIsRunning(bool isRunning);

	SDL_Window* getWindow();
	SDL_GLContext getGLContext();

private:

	void initSystems();
	void mainGameLoop();
	void quitGame();

protected:
	bool m_isRunning = false;
	SDL_Window* m_mainWindow;
	SDL_GLContext m_glContext;
	std::shared_ptr<qub3d::Logger> m_logger;

};

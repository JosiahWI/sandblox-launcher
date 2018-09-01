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

#include "launcher.hpp"
#include <cstdlib>
#include <sstream>

Launcher::Launcher( )
{

}

Launcher::~Launcher( )
{

}

void Launcher::run( )
{
	initSystems( );
	mainGameLoop( );
	quitGame( );
}

bool Launcher::isRunning( )
{
	return m_isRunning;
}

void Launcher::setIsRunning( bool isRunning )
{
	m_isRunning = isRunning;
}

SDL_Window* Launcher::getWindow( )
{
	return m_mainWindow;
}

SDL_GLContext Launcher::getGLContext( )
{
	return m_glContext;
}

void Launcher::initSystems( )
{
	/*
	 * Intialise logger with logging file path and logging verbosity, which is set to everything,
	 * this will be until the Settings manager is implemented
	*/

	char* dataPath;
	char* basePath = SDL_GetBasePath( );
	dataPath = basePath ? basePath : SDL_strdup( ". /" );


	string_t logging_path( dataPath );

	m_logger = std::shared_ptr<qub3d::Logger>( new qub3d::Logger( ) );
	m_logger->init( logging_path + "/Launcher.log", qub3d::LogVerbosity::DEBUG );

	//-----------------SDL and openGL-------------------

	SDL_Init( SDL_INIT_EVERYTHING );

	m_mainWindow = SDL_CreateWindow(
									 "BlockForge Launcher",
									 SDL_WINDOWPOS_CENTERED,
									 SDL_WINDOWPOS_CENTERED,
									 800, 600,
									 SDL_WINDOW_OPENGL );
	if ( m_mainWindow == nullptr )
	{
		// In the case that the window could not be made...
		ERROR( string_t("Could not create window: ") + SDL_GetError( ) );
		exit( EXIT_FAILURE );
	}

	m_glContext = SDL_GL_CreateContext( m_mainWindow );
	if ( m_glContext == nullptr )
	{
		ERROR( string_t("Could not create OpenGL Context: ") + SDL_GetError( ) );
		exit( EXIT_FAILURE );
	}

	GLenum err = glewInit( );
	if ( err != GLEW_OK )
	{
		// Problem: glewInit failed, something is seriously wrong.
		std::stringstream message; // Create a use LogMessage_t (typedef for stringstream), not just concentating with "+", because glewGetErrorString is a grumpy function.
		message  << "GLEW initialisation failed: " << glewGetErrorString( err );
		ERROR( message.str() );
		exit( EXIT_FAILURE );
	}

	// Print out GLEW version for confirmation
	std::stringstream message; // Create a use LogMessage_t (typedef for stringstream), not just concentating with "+", because glewGetErrorString is a grumpy function.
	message  << "Status: Using GLEW version " << glewGetString( GLEW_VERSION );
	DEBUG(message.str());

	glewExperimental = true;

	INFO( "Systems Initialized & Launcher Started!" );
}

void Launcher::mainGameLoop( )
{
	m_isRunning = true;

	while ( m_isRunning )
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		if(event.type == SDL_QUIT)
		{
			m_isRunning = false;
		}
	}
}

void Launcher::quitGame( )
{
	INFO("Quitting the Launcher");
	SDL_DestroyWindow( m_mainWindow );
	SDL_Quit( );
	// Destroy logger to close the files.
	m_logger->destroy( );
}

#include <troll.h>

#include "light_grid.h"
#include "lights_app.h"

#include <stdio.h>


using Troll::Point;
using Troll::Rect;

using Troll::Color;

using Troll::Surface;

using Troll::Graphics;

using Troll::System;
using Troll::Screen;

using Troll::KeyInput;
using Troll::MouseInput;


void ShowLogo();

LightsApp::LightsApp()
{

}

bool LightsApp::Init()
{
	if(!System::Init()) // Initialize system
        return false;
	
    if(!System::SetupScreen(320,480)) // Create screen
        return false;
	
	System::SetScreenTitle("Lights"); // Set window caption

    Screen::ShowCursor(false); // Hide cursor to show logo screen
	
	ShowLogo(); // show logo 
	
    Screen::ShowCursor(true); // Restore cursor 
	
	// Loag game images
	if(!header.LoadImage("images/header.bmp"))
		return false;

	if(!light_on.LoadImage("images/light_on.bmp"))
		return false;
	
	if(!light_off.LoadImage("images/light_off.bmp"))
		return false;
	
	if(!footer.LoadImage("images/footer.bmp"))
		return false;

	x_sel = 0; // selection (to play using keyboard, instead mouse)
	y_sel = 0;
	
	szPiece  = light_on.GetSurface().GetSize();	
    y_offset = header.GetSurface().GetHeight();	
	
	finish = false;

	return true;
}

void LightsApp::Run() // main routine
{
	bool quit = false;

	while(!quit) // main loop
    {
        Screen::StartFrame();

		MouseInput::Update(); //Update Input
		KeyInput::Update();
	
		quit = Logic();
				
        if(!Screen::SkipFrame())
        {
			Render();
        }
    }
}

bool LightsApp::Logic()
{
	/* Input logic */
	bool quit = KeyInput::IsKeyDown(Troll::ESCAPE);

	if(KeyInput::IsKeyPressed(Troll::RIGHT) && x_sel < 4)
		x_sel ++;
	if(KeyInput::IsKeyPressed(Troll::LEFT) && x_sel > 0)
		x_sel --;
	
	if(KeyInput::IsKeyPressed(Troll::DOWN) && y_sel < 4)
		y_sel ++;
	if(KeyInput::IsKeyPressed(Troll::UP) && y_sel > 0)
		y_sel --;
	
	Point pt;
	MouseInput::GetRelativePosition(pt);

	if(pt.x != 0 || pt.y != 0) // if mouse position changed 
	{
		MouseInput::GetPosition(pt);
		x_sel = pt.x/szPiece.x;
		y_sel = (pt.y - y_offset)/szPiece.y;
	}
	
	if(MouseInput::IsButtonReleased(0) || KeyInput::IsKeyPressed(Troll::RETURN)) // if 'Enter' or click
	{
		if(x_sel < 5 && y_sel >= 0 && y_sel < 5)
			grid.ToggleLight(x_sel,y_sel);
	}

	/* Game logic */
	
	if(grid.HasFinished())
	{
		if(grid.GetLevel() < grid.GetMaxLevel())
			grid.SetLevel(grid.GetLevel() + 1);
		else
			finish = true;
	}
	return quit;
}

void LightsApp::Render() // Render current frame
{
	Surface & screen = Screen::GetSurface(); // Get surface screen
    Graphics g(screen); // Create a Graphics object

	screen.Clear();
	
	screen.Blit(header.GetSurface()); // Blit header
	
	Rect rc(0,y_offset,szPiece.x,szPiece.y);	
	
	for(int i = 0; i < 5; i++) // Draw each light
	{
		for(int j = 0; j < 5; j ++)
		{
			const Surface & light = grid.IsLightOn(j,i) ? // choice light (on or off)
				                    light_on.GetSurface():
			                        light_off.GetSurface();
			
			screen.Blit(light,rc.GetPosition());
			
			if(x_sel == j && y_sel == i)
				g.DrawRect(rc,Color::RED); // Draw the selection rect
			
			rc.x += szPiece.x;
		}
		rc.x = 0;
		rc.y += szPiece.y;
	}
	
	if(finish)
	{
		g.DrawRoundRectFill(Rect(10,260,300,100),8,Color(0,0,192,140));
		g.DrawRoundRect(Rect(10,260,300,100),8,Color(0,0,192,192));
		g.DrawText(Point(100,285),"Congratulations!!!",Color::WHITE);
	}
		
	screen.Blit(footer.GetSurface(),Point(0,rc.y));
	
	char strLevel[10];
	sprintf(strLevel,"%d",grid.GetLevel());
	
	g.DrawText(Point(90,422),strLevel, Color::RED);

	Screen::Flip(); // Draw to screen (page flip, or blit)
}
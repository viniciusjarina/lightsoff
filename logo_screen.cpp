#include <troll.h>

#include "logo_screen.h"

using namespace Troll;

void ShowLogo()
{
	Image logoImage;
	int i;

	if(!logoImage.LoadImage("images/logo.bmp"))
		return;

	const Surface & logo   =  logoImage.GetSurface();
	Surface & screen =  Screen::GetSurface();
	int nFPS		 =  Screen::GetFPS();
	int nTotalFrames = nFPS; // 1 seconds
	Point logoPos((screen.GetWidth() - logo.GetWidth())/2, (screen.GetHeight() - logo.GetHeight())/2);
	
	for(i = 0; i < nTotalFrames; i++)
	{
		Screen::StartFrame();

		unsigned char alpha = (i*255)/(nTotalFrames);
		

		if(!Screen::SkipFrame())
		{
			screen.Clear();
			screen.DrawAlpha(logo,logoPos,alpha);
			Screen::Flip();
		}

	}

	for(i = 0; i < nTotalFrames; i++)
	{
		Screen::StartFrame();

		if(!Screen::SkipFrame())
		{
			screen.Clear();
			screen.Blit(logo,logoPos);
			
			Screen::Flip();
		}
	}

	for(i = nTotalFrames; i > 0; i--)
	{
		Screen::StartFrame();

		unsigned char alpha = (i*255)/nTotalFrames;

		if(!Screen::SkipFrame())
		{
			screen.Clear();
			screen.DrawAlpha(logo,logoPos,alpha);
			Screen::Flip();
		}
	}
	
}
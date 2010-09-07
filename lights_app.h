#ifndef __LIGHTS_APP_H__
#define __LIGHTS_APP_H__

class LightsApp
{
public:
	LightsApp();

	bool Init();

	void Run();
	


	bool Logic();
	void Render();

private:

	Troll::Image header;
	Troll::Image light_on;
	Troll::Image light_off;
	Troll::Image footer;

	LightGrid grid;
    
    	
    int x_sel;
    int y_sel;
	
	Troll::Size szPiece;
	
    int y_offset;
	
	
	bool finish;;
};

#endif //__LIGHTS_APP_H__
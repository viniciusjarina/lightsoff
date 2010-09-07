#ifndef __LIGHT_GRID_H__
#define __LIGHT_GRID_H__

class LightGrid
{
private:
	enum {MAX_LEVEL = 20};

	unsigned long m_grid;
	unsigned long m_nCurrentLevel;

	static const unsigned long  m_sLevels[MAX_LEVEL];

	inline void ToggleOneLight(int x, int y)
	{
		if(IsLightOn(x,y))
			m_grid &= ~(1<<(y*5+ x));
		else
			m_grid |=  (1<<(y*5+ x));			
	}

public:

	LightGrid();

	inline void SetLevel(unsigned long nLevel)
	{
		m_nCurrentLevel = nLevel;
		m_grid = m_sLevels[nLevel];
	}

	inline unsigned long GetLevel() const 
	{
		return m_nCurrentLevel;
	}

	static inline unsigned long GetMaxLevel()
	{
		return MAX_LEVEL;
	}

	inline bool IsLightOn(int x,int y) const 
	{
		return (m_grid&(1<<(y*5+ x))) != 0;
	}
	
	inline void ToggleLight(int x, int y)
	{
		if(x > 0)
			ToggleOneLight(x - 1, y);
		if(x < 4)
			ToggleOneLight(x + 1, y);

		if(y > 0)
			ToggleOneLight(x, y - 1);
		if(y < 4)
			ToggleOneLight(x, y + 1);
		
		ToggleOneLight(x, y);		
	}

	inline bool HasFinished() const
	{
		return m_grid == 0;
	}
};

#endif // __LIGHT_GRID_H__
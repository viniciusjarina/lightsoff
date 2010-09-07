#include "light_grid.h"

const unsigned long LightGrid::m_sLevels[MAX_LEVEL] =
{
	0x000000,
	0x23AB88,
	0x1B8823B,
	0x426C84,
	0x111110,
	0x1FF83FF,
	0x5400,
	0x15FEFF5,
	// TODO: Add more levels here
};

LightGrid::LightGrid():
m_nCurrentLevel(1)
{
	m_grid = m_sLevels[m_nCurrentLevel];
}




#pragma once
#include <windows.h>

class DrayAssist
{
public: 
	DrayAssist() 
	{
		is_start_point_y_down = false;
		m_start_point.x = 0;
		m_start_point.y = 0;
	}

	void SetIsStartPointYDown(bool isDown)
	{
		is_start_point_y_down = isDown;
	}

	void SetStartPoint(int x, int y)
	{
		m_start_point.x = x;
		m_start_point.y = y;
	}

	void MouseDown(int x, int y)
	{
		m_down_point.x = x;
		m_down_point.y = y;                
	}
	POINT MouseMove(int x, int y)
	{
		POINT new_point;
		new_point.x = m_start_point.x + (x - m_down_point.x);

		if(is_start_point_y_down)
			new_point.y = m_start_point.y + (y - m_down_point.y);
		else
			new_point.y = m_start_point.y - (y - m_down_point.y);

		m_start_point.x = new_point.x;
		m_start_point.y = new_point.y;
		m_down_point.x = x;
		m_down_point.y = y;

		return new_point;
	}
private:

	POINT m_down_point;
	POINT m_start_point;

	bool is_start_point_y_down;

};
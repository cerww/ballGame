#include "block.h"

void block::draw(drawRenderer& r)const {
	r.draw({ m_pos.x * 40.0f + 10,m_pos.y * 30.0f,40.0f,30.0f }, fullPicUV, Rectangle::getFlatColor().id, {150,250,160,200},1.0f);	
}

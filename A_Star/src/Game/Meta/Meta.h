#pragma once

#include <vector>

#include "../../../../lib/ci_ext/object.hpp"

class Cell;
class Meta :public ci_ext::Object
{

	double m_dRatioOfWall;
	bool m_bEnable;
	const int m_iResetTime;
	int m_iResetTimer;

	std::vector<Cell*> m_NormalCells;
	void CreateWalls();
	void SetGoal();
	template <class T>
	void VectorShuffle(std::vector<T> &vec);
		

public:
	Meta();
	~Meta();

	void update() override;



};


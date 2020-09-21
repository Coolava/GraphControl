#pragma once
#include <vector>
#include <memory>
#include "CPlot.h"

using namespace std;
class CPlotContainer
{
private:
	vector<unique_ptr<CPlot>> Container;

public:
	/*Return containers ref*/
	virtual vector<unique_ptr<CPlot>>& getContainer();

	virtual unique_ptr<CPlot>& getPlot(size_t index);

	virtual size_t AddPlot(unique_ptr<CPlot> plot);
};


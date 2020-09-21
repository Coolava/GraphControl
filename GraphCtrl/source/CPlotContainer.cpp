
#include "CPlotContainer.h"

vector<unique_ptr<CPlot>>& CPlotContainer::getContainer()
{
	return Container;
}

unique_ptr<CPlot>& CPlotContainer::getPlot(size_t index)
{
	return Container.at(index);
}

size_t CPlotContainer::AddPlot(unique_ptr<CPlot> plot)
{
	Container.push_back(std::move(plot));

	return Container.size();
}

#pragma once

enum class GraphType
{
	Default,
	Circle = Default,
	Linear
};

template<typename T>
class Axis
{
public:
	Axis():begin(T()),end(T()){};
	Axis(T _begin, T _end) :begin(_begin), end(_end) {}
	T begin;
	T end;

	inline T size() { return (end - begin); }

	bool operator!=(const Axis& a)
	{
		if (begin != a.begin || end != a.end)
			return true;
		else
			return false;
	}
};

template<typename T>
class CResolution
{
public:
	CResolution():x(T()),y(T()) {};
	CResolution(T _x, T _y) :x(_x), y(_y) {}
	T x;
	T y;

	bool operator!=(const CResolution& a)
	{
		if (x != a.x || y != a.y)
			return true;
		else
			return false;
	}
};
class CAxisInfo
{
public:
	CAxisInfo() {}
	CAxisInfo(const CAxisInfo& info)
	{
		xAxis.begin = info.xAxis.begin;
		xAxis.end = info.xAxis.end;
		yAxis.begin = info.yAxis.begin;
		yAxis.end = info.yAxis.end;
		Resolution.x = info.Resolution.x;
		Resolution.y = info.Resolution.y;

		//prev.reset(new CAxisInfo());
	}
	CAxisInfo(CRect rc)
	{
		xAxis.begin = 0;
		xAxis.end = (Gdiplus::REAL)rc.Width();
		yAxis.begin = 0;
		yAxis.end = (Gdiplus::REAL)rc.Height() - 1;
		Resolution.x = (Gdiplus::REAL)rc.Width();
		Resolution.y = (Gdiplus::REAL)rc.Height() - 1;

		prev.reset(new CAxisInfo());
	}
	CAxisInfo(Axis<Gdiplus::REAL> _xAxis, Axis<Gdiplus::REAL> _yAxis, CResolution<Gdiplus::REAL> _Resolution)
		: xAxis(_xAxis), yAxis(_yAxis), Resolution(_Resolution) {}
	/*Pixel, Start and End of x Axis.*/
	Axis<Gdiplus::REAL> xAxis = { 0,0 };
	/*Pixel, Start and End of y Axis.*/
	Axis<Gdiplus::REAL> yAxis = { 0,0 };

	/*number of points*/
	CResolution< Gdiplus::REAL> Resolution = { 0,0 };

	bool isUpdated()
	{
		if (prev->xAxis != this->xAxis
			|| prev->yAxis != this->yAxis
			|| prev->Resolution != this->Resolution)
		{
			prev.reset(new CAxisInfo(*this));
			return true;
		}
		else
		{
			return false;
		}
	}
private:
	std::unique_ptr<CAxisInfo> prev;
};

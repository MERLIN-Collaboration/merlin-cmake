#include "InterpolatedApertures.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
//Circle



//RectEllipse


//Returns true if the point (x,y,z) is within the aperture.
bool InterpolatedRectEllipseAperture::PointInside (double x, double y, double z) const
{
//	MerlinProfile::StartProcessTimer("APERTURE");
//	cout << "InterpolatedRectEllipse Aperture" << endl;
	ap apFront;
	ap apBack;

	apFront.s = 0;
	apFront.ap1 = 0;
	apFront.ap2 = 0;
	apFront.ap3 = 0;
	apFront.ap4 = 0;

	apBack.s = 0;
	apBack.ap1 = 0;
	apBack.ap2 = 0;
	apBack.ap3 = 0;
	apBack.ap4 = 0;

	if(z < 0)
	{
		z = 0;
	}

	//The z coordinate is used to find the other aperture components
	for(size_t n=0; n < ApertureList.size(); n++)
	{
		if(ApertureList[n].s > z)
		{
			apBack = InterpolatedAperture::ApertureList[n-1];
			apFront = InterpolatedAperture::ApertureList[n];
			//cout << "Got aperture at " << n << "\tTotal size: " << ApertureList.size() << endl;
			break;
		}
	}
	
	//We now have the aperture before and after the particle.
	//It must now be calculated at the point where the particle is currently.
	
	//y = mx + c
	//m = (y1 - y0) / (x1 - x0)
	double delta_s = apFront.s - apBack.s;
	double g1 = (apFront.ap1 - apBack.ap1) / delta_s;
	double g2 = (apFront.ap2 - apBack.ap2) / delta_s;
	double g3 = (apFront.ap3 - apBack.ap3) / delta_s;
	double g4 = (apFront.ap4 - apBack.ap4) / delta_s;

	//c = y - mx
	double c1 = apFront.ap1 - (g1 * apFront.s);
	double c2 = apFront.ap2 - (g2 * apFront.s);
	double c3 = apFront.ap3 - (g3 * apFront.s);
	double c4 = apFront.ap4 - (g4 * apFront.s);

	double rect_half_width = (g1 * z) + c1;
	double rect_half_height = (g2 * z) + c2;
	double ellipse_half_horizontal = (g3 * z) + c3;
	double ellipse_half_vertical = (g4 * z) + c4;

	//aper_1 = half width rectangle
	//aper_2 = half heigth rectangle
	//aper_3 = half horizontal axis ellipse (or radius if circle)
	//aper_4 = half vertical axis ellipse
	
	if(((x*x)/(ellipse_half_horizontal*ellipse_half_horizontal)) + ((y*y)/(ellipse_half_vertical*ellipse_half_vertical)) > 1)
	{
		//Particle is NOT inside the eliptical aperture component
//		if(Print == true)

//		cout << "Not in ellipse: " << x*x << "\t" << ellipse_half_horizontal*ellipse_half_horizontal << "\t" << y*y << "\t" << (ellipse_half_vertical*ellipse_half_vertical); 
//		cout << "\t" << ((x*x)/(ellipse_half_horizontal*ellipse_half_horizontal)) + ((y*y)/(ellipse_half_vertical*ellipse_half_vertical)) << endl;

//		MerlinProfile::EndProcessTimer("APERTURE");
		return 0;
	}
	else if(fabs(x) > rect_half_width || fabs(y) > rect_half_height)
	{
		//Particle is NOT inside the rectangular aperture component
//		if(Print == true)
//		cout << "Not in rectangle:\tx: " << x << "\t" << rect_half_width << "\ty: " << y << "\t" << rect_half_height << endl;
//		cout << "x1: " << apBack.ap1 << "\tx2: " << apFront.ap1 << "\ty1: " << apBack.ap2 << "\ty2: " << apFront.ap2 << endl;
//		MerlinProfile::EndProcessTimer("APERTURE");
		return 0;
	}
	else
	{
		//Particle is inside both components, and is inside the aperture
//		if(Print == true)
//		cout << "RECTELLIPSE APERTURE CHECK ok" << endl;
//		MerlinProfile::EndProcessTimer("APERTURE");
		return 1;
	}
}

double InterpolatedRectEllipseAperture::GetRadiusAt (double phi, double z) const
{
	std::cerr << "Not yet implemented: InterpolatedRectEllipseAperture::GetRadiusAt()" << std::endl;
	exit(EXIT_FAILURE);
}


void InterpolatedRectEllipseAperture::EnablePrint()
{
	Print = true;
}


inline bool InterpolatedCircularAperture::PointInside (double x, double y, double z) const
{
//	cout << "InterpolatedCircular Aperture: PointInside()" << endl;
	ap apFront;
	ap apBack;

	apFront.s = 0;
	apFront.ap1 = 0;
	apFront.ap2 = 0;
	apFront.ap3 = 0;
	apFront.ap4 = 0;

	apBack.s = 0;
	apBack.ap1 = 0;
	apBack.ap2 = 0;
	apBack.ap3 = 0;
	apBack.ap4 = 0;

	if(z < 0)
	{
		z = 0;
	}

	//The z coordinate is used to find the other aperture components
	for(size_t n=0; n < ApertureList.size(); n++)
	{
		if(ApertureList[n].s > z)
		{
			apBack.s = InterpolatedAperture::ApertureList[n-1].s;
			apBack.ap3 = InterpolatedAperture::ApertureList[n-1].ap3;

			apFront.s = InterpolatedAperture::ApertureList[n].s;
			apFront.ap3 = InterpolatedAperture::ApertureList[n].ap3;
			if(apFront.ap3 == 0 || apBack.ap3 == 0)
			{
				cout << z << endl;
				cout << apFront.s << endl;
				cout << apBack.s << endl;
				cout << apFront.ap3 << endl;
				cout << apBack.ap3 << endl;
				cout << ApertureList[n].ap3 << endl;
				cout << ApertureList[n-1].ap3 << endl;
				abort();
			}
			break;
		}
		if(n == (ApertureList.size()-1))
		{
			cout << "no aperture found" << endl;
			cout << "z: " << z << endl;
			for(size_t m=0; m < ApertureList.size(); m++)
			{
				cout << ApertureList[m].s << endl;
			}
			abort();
		}
	}

	//We now have the aperture before and after the particle.
	//It must now be calculated at the point where the particle is currently.
	
	//y = mx + c
	//m = (y1 - y0) / (x1 - x0)
	double delta_s = apFront.s - apBack.s;
	double g = (apFront.ap3 - apBack.ap3) / delta_s;

	//c = y - mx
	double c = apFront.ap3 - (g * apFront.s);

	//aper_3 = half horizontal axis ellipse (or radius if circle)
	double r2 = pow((g * z) + c,2);
if((x*x+y*y<r2) == 0)
{
	//cout << "Interpolated Circular aperture: " << (x*x) + (y*y) << "\tR: " << r2 << "\t" << apFront.ap3 << "\t" << apBack.ap3 << endl;
	return false;
}
    return x*x+y*y<r2;
}

double InterpolatedCircularAperture::GetRadiusAt (double phi, double z) const
{
	ap apFront;
	ap apBack;

	apFront.s = 0;
	apFront.ap1 = 0;
	apFront.ap2 = 0;
	apFront.ap3 = 0;
	apFront.ap4 = 0;

	apBack.s = 0;
	apBack.ap1 = 0;
	apBack.ap2 = 0;
	apBack.ap3 = 0;
	apBack.ap4 = 0;

	//The z coordinate is used to find the other aperture components
	for(size_t n=0; n < ApertureList.size(); n++)
	{
		if(ApertureList[n].s > z)
		{
			apBack = InterpolatedAperture::ApertureList[n-1];
			apFront = InterpolatedAperture::ApertureList[n];
			break;
		}
	}

	//We now have the aperture before and after the particle.
	//It must now be calculated at the point where the particle is currently.
	
	//y = mx + c
	//m = (y1 - y0) / (x1 - x0)
	double delta_s = apFront.s - apBack.s;
	double g = (apFront.ap3 - apBack.ap3) / delta_s;

	//c = y - mx
	double c = apFront.ap3 - (g * apFront.s);

	//aper_3 = half horizontal axis ellipse (or radius if circle)
	double r2 = pow((g * z) + c,2);
	return sqrt(r2);
}

double InterpolatedCircularAperture::GetRadius () const
{
	std::cerr << "Not yet implemented: InterpolatedCircularAperture::GetRadius()" << std::endl;
	exit(EXIT_FAILURE);
//    return sqrt(r2);
}




/*
inline void InterpolatedRectEllipseAperture::SetRectHalfWidth(double w)
{
	rect_half_width = w;
}

inline void InterpolatedRectEllipseAperture::SetRectHalfHeight(double h)
{
	rect_half_height = h;
}

inline void InterpolatedRectEllipseAperture::SetEllipseHalfHorizontal(double h)
{
	ellipse_half_horizontal = h;
}

inline void InterpolatedRectEllipseAperture::SetEllipseHalfVertical(double v)
{
	ellipse_half_vertical = v;
}
*/
/*
	cout << delta_s << "\t" << gradient << "\tFront: " << apFront.ap1 << "\tBack: " <<  apBack.ap1 << endl;
	cout << delta_s << "\t" << gradient << "\tFront: " << apFront.ap2 << "\tBack: " <<  apBack.ap2 << endl;
	cout << delta_s << "\t" << gradient << "\tFront: " << apFront.ap3 << "\tBack: " <<  apBack.ap3 << endl;
	cout << delta_s << "\t" << gradient << "\tFront: " << apFront.ap4 << "\tBack: " <<  apBack.ap4 << endl;
	cout << delta_s << "\t" << gradient << "\tFront: " << apFront.s << "\tBack: " <<  apBack.s << endl;
cout << endl;
	cout << delta_s << "\t" << gradient << "\tFront: " << apFront1.ap1 << "\tBack: " <<  apBack1.ap1 << endl;
	cout << delta_s << "\t" << gradient << "\tFront: " << apFront1.ap2 << "\tBack: " <<  apBack1.ap2 << endl;
	cout << delta_s << "\t" << gradient << "\tFront: " << apFront1.ap3 << "\tBack: " <<  apBack1.ap3 << endl;
	cout << delta_s << "\t" << gradient << "\tFront: " << apFront1.ap4 << "\tBack: " <<  apBack1.ap4 << endl;
	cout << c << endl;
abort();
*/


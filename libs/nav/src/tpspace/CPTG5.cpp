/* +---------------------------------------------------------------------------+
   |                     Mobile Robot Programming Toolkit (MRPT)               |
   |                          http://www.mrpt.org/                             |
   |                                                                           |
   | Copyright (c) 2005-2016, Individual contributors, see AUTHORS file        |
   | See: http://www.mrpt.org/Authors - All rights reserved.                   |
   | Released under BSD License. See details in http://www.mrpt.org/License    |
   +---------------------------------------------------------------------------+ */

#include "nav-precomp.h" // Precomp header
#include <mrpt/nav/tpspace/CPTG5.h>
#include <mrpt/system/os.h>

using namespace mrpt;
using namespace mrpt::nav;
using namespace std;
using namespace mrpt::system;
using namespace mrpt::utils;

IMPLEMENTS_SERIALIZABLE(CPTG5,CParameterizedTrajectoryGenerator,mrpt::nav)

void CPTG5::setParams(const mrpt::utils::TParameters<double> &params)
{
	this->K = params["K"];
	CPTG_DiffDrive_CollisionGridBased::setParamsCommon(params);
	// The constant curvature turning radius used in this PTG:
	R = V_MAX / W_MAX;
}


void CPTG5::readFromStream(mrpt::utils::CStream &in, int version)
{
	CPTG_DiffDrive_CollisionGridBased::internal_readFromStream(in);

	switch (version)
	{
	case 0:
		MRPT_TODO("continue")
		break;
	default:
		MRPT_THROW_UNKNOWN_SERIALIZATION_VERSION(version)
	};
}

void CPTG5::writeToStream(mrpt::utils::CStream &out, int *version) const
{
	if (version) 
	{
		*version = 0;
		return;
	}

	CPTG_DiffDrive_CollisionGridBased::internal_writeToStream(out);

//	out << V_MAX << W_MAX
	MRPT_TODO("continue")

}
std::string CPTG5::getDescription() const
{
	char str[100];
	os::sprintf(str,100,"Type#5PTG:CS");
	return std::string(str);
}

void CPTG5::ptgDiffDriveSteeringFunction( float alpha, float t,float x, float y, float phi, float &v, float &w ) const
{
	MRPT_UNUSED_PARAM(x); MRPT_UNUSED_PARAM(y); MRPT_UNUSED_PARAM(phi);
	const float T = 0.847f*std::sqrt(std::abs(alpha))*R/V_MAX;

	if (t< T)
	{
		// l+
		v = V_MAX;
		w = W_MAX * min( 1.0f , 1.0f - (float)exp( -square(alpha) ));
	}
	else
	{
		// s+:
		v = V_MAX;
		w = 0;
	}

	// Turn in the opposite direction??
	if (alpha<0)
		w*=-1;

	v*=K;
	w*=K;

}

bool CPTG5::PTG_IsIntoDomain( double x, double y ) const
{
	// If signs of K and X are different, it is not into the domain:
	if ((K*x)<0)
		return false;

	if (fabs(y)>=R)
	{
		// Segmento de arriba:
		return (fabs(x)>R-0.10f);
	}
	else
	{
		// The circle at (0,R):
		return (square(x)+square(fabs(y)-(R+0.10f)))>square(R);
	}
}


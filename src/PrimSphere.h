// Sphere Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "IPrim.h"
#include "ray.h"

// ================================ Sphere Primitive Class ================================
/**
 * @brief Sphere Geaometrical Primitive class
 * @ingroup modulePrimitive
 * @author Sergey G. Kosov, sergey.kosov@project-10.de
 */
class CPrimSphere : public IPrim
{
public:
	/**
	 * @brief Constructor
		 * @param origin Position of the center of the sphere
		 * @param radius Radius of the sphere
	 */
	CPrimSphere(Vec3f origin, float radius, Vec3f color)
		: IPrim(color)
		, m_origin(origin)
		, m_radius(radius)
	{}
	virtual ~CPrimSphere(void) = default;

	virtual intersect(Ray& ray)const override {
		float dir_norm = ray.dir.dot(ray.dir);
		float d_tb = 2 * ray.dir.dot(ray.org - m_origin);
		float L_norm = (ray.org - m_origin).dot(ray.org - m_origin) - m_radius * m_radius;

		float threshold = pow(d_tb,2.0) - (4 * dir_norm * L_norm);

		if (threshold < 0)
		{
			return false;
		}

		float t1 = ((-d_tb) + sqrt(threshold)) / (dir_norm * 2);

		float t2 = ((-d_tb) - sqrt(threshold)) / (dir_norm * 2);

		float t;

		if (t1 < t2)
			t = t1;
		else {
			t = t2;
		}	

		if ((t > Epsilon) && (t < ray.t))
		{
			ray.t = t;
			return true;
		}
		else {
			return false;
		}
	}
	
	
private:
	Vec3f m_origin;	///< Position of the center of the sphere
	float m_radius;	///< Radius of the sphere
};


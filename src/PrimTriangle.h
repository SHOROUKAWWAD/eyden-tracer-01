// Triangle Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "IPrim.h"
#include "ray.h"

// ================================ Triangle Primitive Class ================================
/**
 * @brief Triangle Geometrical Primitive class
 * @ingroup modulePrimitive
 * @author Sergey G. Kosov, sergey.kosov@project-10.de
 */
class CPrimTriangle : public IPrim
{
public:
	/**
	 * @brief Constructor
	 * @param a Position of the first vertex
	 * @param b Position of the second vertex
	 * @param c Position of the third vertex
	 */
	CPrimTriangle(const Vec3f& a, const Vec3f& b, const Vec3f& c)
		: IPrim()
		, m_a(a)
		, m_b(b)
		, m_c(c)
  	{}
	virtual ~CPrimTriangle(void) = default;
	
	virtual bool intersect(Ray& ray) const override
	{
		Vec3f norm_edge1 = (m_b - ray.org).cross(m_a - ray.org);
		Vec3f norm_edge2 = (m_c - ray.org).cross(m_b - ray.org);
		Vec3f norm_edge3 = (m_a - ray.org).cross(m_c - ray.org);

		float Area = norm_edge1.dot(ray.dir) + norm_edge2.dot(ray.dir) + norm_edge3.dot(ray.dir);
		float L1 = norm_edge1.dot(ray.dir) / Area;
		if (L1 < 0 || L1>1) {
			return false;
		}
		float L2 = norm_edge2.dot(ray.dir) / Area;
		if (L2 < 0 || L2 >1) {
			return false;
		}
		float L3= norm_edge3.dot(ray.dir) / Area;
		if ( L3 < 0 || L3 > 1)
		{
			return false;
		}
		Vec3f pvec = L1 * m_a + L2 * m_b + L3 * m_c;
		float t = pvec[0] / ray.dir[0];

		if (t < Epsilon || t > ray.t)
		{
			return false;
		}
		ray.t = t;
		return true;
	}

	
private:
	Vec3f m_a;		///< Position of the first vertex
	Vec3f m_b;		///< Position of the second vertex
	Vec3f m_c;		///< Position of the third vertex
};

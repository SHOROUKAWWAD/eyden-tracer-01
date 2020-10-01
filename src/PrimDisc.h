#pragma once

#include "IPrim.h"
#include "ray.h"

// --- IMPLENET class CPrimDisc ---
// --- PUT YOUR CODE HERE ---

class CPrimDisc :public IPrim {

Public:

	CPrimDisc(const Vec3f origin, const Vec3f& normal, const float radius, Vec3f color) 
		: IPrim(color),
		m_normal(normal),
		m_origin(origin),
		m_radius(radius)
	{
		cv::normalize(m_normal);

	}
	virtual ~CPrimDisc(void) = default;

	virtual intersect(Ray& ray)const override {
		float numerator = m_normal.dot(m_origin - ray.org);
		float denominator = m_normal.dot(ray.dir);
		float t;

		if (denominator == 0) {
			return 0;
		}
		else {
			t = numerator / denominator;
		}

		if (norm(ray.org + ray.dir * t - m_origin) > m_radius) {
			return false;
		}
		else {
			ray.t = t;
			return true;
		}
	}

private:

	Vec3f m_normal;
	Vec3f m_origin;
	float m_radius;
};
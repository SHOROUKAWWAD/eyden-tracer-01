#pragma once

#include "ICamera.h"
#include "ray.h"

// --- IMPLENET class CCameraOrthographic ---
// --- PUT YOUR CODE HERE ---
class CCamerOrthographic:public ICamera {

public:
	CCamerOrthographic(Size resolution, const Vec3f& pos, const Vec3f& dir, const Vec3f& up, float angle)
	:ICamera(resolution),
		m_pos(pos),
		m_dir(dir),
		m_up(up)
	{

		m_focus = 1 / tan((Pif * angle) / 360);
		m_zAxis = m_dir;
		m_xAxis = cv::normalize(m_zAxis.cross(m_up));
		m_yAxis = cv::normalize(m_zAxis.cross(m_xAxis));
	}
	virtual ~CCamerOrthographic(void) = default;
	virtual void InitRay(Ray& ray, int x, int y) override{

		float ndcx = (float)(x + 0.5) / getResolution().width;
		float ndcy = (float)(x + 0.5) / getResolution().height;
		float sscx = (float)(2 * ndcx - 1);
		float sscy = (float)2 * ndcy - 1;
		ray.org = m_pos;
		ray.t = std::numeric_limits<float>::max();
		ray.dir = cv::normalize(m_zAxis * m_focus + getAspectRatio * sscx * m_xAxis + sscy * m_yAxis);

	}
private:
	// input values
	Vec3f m_pos;			///< Camera origin (center of projection)
	Vec3f m_dir;			///< Camera viewing direction
	Vec3f m_up;				///< Camera up-vector
	float m_focus;	///< The focal length
	float m_aspect;
	// preprocessed values
	Vec3f m_xAxis;			///< Camera x-axis in WCS
	Vec3f m_yAxis;			///< Camera y-axis in WCS
	Vec3f m_zAxis;			///< Camera z-axis in WCS
};
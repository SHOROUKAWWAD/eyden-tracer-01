# Practical Assignment 1
**Deadline**: 01.10.2020

**Name**: SHOROUK AWWAD
## Foreword
### Implementation of a Minimal Ray Tracing System

Each basic ray tracing system in principle consists of only four simple parts:
- **Camera: Primary Ray Generation** for generating the rays to be cast from a virtual camera into the scene.
- **Geometry: Ray-Geometry Intersection** for finding the (closest) intersection of a ray with the scene to be rendered.
- **Shading** for calculating the ’color’ of the ray.
- **Light** (ignoring for this assignment)

In this exercise, you will build a __minimal__ ray tracing system by implementing first three tasks. To make this easier, you are provided with a basic ray tracing framework so that you just have to __fill in__ the missing core parts.
- Download and install [CMake](https://cmake.org)
- Download (, build) and install [OpenCV](https://opencv.org) library
- Fork the current repository
- Using CMake generate the solution for eyden-tracer for your favorite IDE (_e.g._ Microsoft Visual Studio or XCode)
- Check that you can build and run _eyden-tracer_
- Do the assignment
- Add new folder "renders" to repository and save there the resulting renders (_i.e._ rendered images)
- Submit assignment by making a pull request

The provided ray tracing framework contains a number of useful C++ classes, which you will need for the practical exercises:
- OpenCV class Vec3f, which incorporates standard vector operations such as addition, subtraction, dot product, cross product, _etc._
- In order to handle and save image data, an OpenCV class Mat is included that handles pixels of type Vec3f. Pixels are stored in BGR (Blue, Green, Red) format, where each color component ranges from 0.0 to 1.0. For example, black=(0, 0, 0), white=(1, 1, 1), red=(0, 0, 1). With function imwrite(String& fileName, Mat& img) image data is saved into file. The bmp, jpg, _etc._ file formats are supported. See main.cpp on how to use this class.
- A structure Ray, where a ray is defined by its origin Vec3f _org_, its direction Vec3f _dir_, and its length float _t_.
- An __abstract interface__ base class IPrim for handling scene geometric primitives. For each primitive class derived from this base class (_e.g._ CPrimSphere or CPrimTriangle), the pure virtual method ```IPrim::intersect(Ray& ray) const = 0``` has to be implemented (see below).
- Furthermore an __abstract interface__ base class ICamera for handling the camera parameters. For each derived class (_e.g._ CCameraPerspective), the pure virtual method ```ICamera::InitRay(Ray& ray, int x, int y) = 0``` has to be implemented. Whereby x and y specify the pixel coordinates in Raster Coordinate System which should be used to initialize the ray.

## Problem 1 (5 + 10 + 5 Points)
Before implementing anything read through the presented classes and main.cpp and try to understand the object structure as well as internal dependencies. In this exercise your task now is to implement the missing parts in main.cpp, PrimPlane.h, PrimSphere.h, PrimTriangle.h, PrimDisc.h, CameraPerspective.h and CameraOrthographic.h.
> A the solution for this problem can be found in OpenRT library: www.openrt.org However it is highly recommended to solve this problem using lecture slides only and resorting to the solution only as a last resort. 

### 1.1 Primary Ray Generation
Implement perspective camera model into your eyden-tracer (in CameraPerspective.h). Fill in the appropriate code into the constructor and InitRay-method. Test your camera implementation with the four corner rays of the image and camera model cam1. The ray.dir would be: (−0.5543, −0.415508, −0.721183), (0.5543, −0.415508, −0.721183), (−0.5543, 0.415508, −0.721183) and (0.5543, 0.415508, −0.721183).
### 1.2 Ray Tracing
The heart of every ray tracer is to find the closest intersection of a ray with a scene consisting of a certain number of geometric primitives. This eventually requires to compute intersections between rays and those primitives. For the three provided primitive classes CPrimPlane (in PrimPlane.h), CPrimSphere (in PrimSphere.h), and CPrimTriangle (in PrimTriangle.h) implement the intersection methods ```CPrimPlane::intersect(Ray& ray) const```, ```CPrimSphere::intersect(Ray& ray) const```, and ```CPrimTriangle::intersect(Ray& ray) const``` using the formulas from the lecture. The semantics of intersect should be as follows:
    - Return true if and only if a valid intersection has been found in the interval (Epsilon, ray::t). Epsilon is defined in types.h.
    - If a valid intersection has been found with the primitive, set ray::t to the distance to this intersection point (if current t < ray.t).
Find the __closest__ intersection of the ray with the scene by just testing all in main.cpp defined primitives (s1, s2, s3, and p1) sequentially.
### 1.3 Shading
Just use constant colors for each primitive, and assign each pixel the color of the primitive the ray has hit. For this exercise, you can hard-code the color of the objects. To obtain the same image as below, use colors red RGB(1, 0, 0) for s1, green RGB(0, 1, 0) for s2, blue RGB(0, 0, 1) for s3, yellow RGB(1, 1, 0) for p1, cyan RGB(0, 1, 1) for t1, and white RGB(1, 1, 1) for t2.

For testing, use the already in main.cpp hard-coded example scene after finishing all implementation tasks in this assignment sheet. Render images (800×600 pixels) with the following camera definitions, and save them in “perspective1.jpg”, “perspective2.jpg” and ”perspective3.jpg”, respectively.
pos = (0, 0, 10), dir = (0, 0, −1), up = (0, 1, 0), angle = 60°
pos = (−8, 3, 8), dir = (1, −.1, −1), up = (0, 1, 0), angle = 45°
pos = (−8, 3, 8), dir = (1, −.1, −1), up = (1, 1, 0), angle = 45°

If your ray tracer works as expected, the first resulting image should look like this:
![perspective1.jpg](https://github.com/Jacobs-University/eyden-tracer-01/blob/master/doc/perspective1.jpg)

## Problem 2 (30 Points)
### Disc primitive
Implenet the ```CPrimDisc``` class. 

You can derive this class from ```CPrimPlane```, or directly from ```IPrim```. In contrast to the plane primitive, disc has one more parameter: _r_ - the radius of the disc. The intersection algorithm can be also based on the ray - plane intersection algorithm with one defference: discard intersection if ||**p** - **a**|| > _r_

Once implemented, create an instance of ```CPrimDisc``` class in main.cpp and replace sphere s1 with the disc. Render it with magenta color. 

## Problem 3 (50 Points)
### Orthographic Camera
Implement the ```CCameraOrthographic``` class.

You can derive ```CCameraOrthographic``` from ```ICamera``` class. Implement ray generation according to the lecture slides.

Once implemented, create an instance of ```CCameraOrthographic``` class in main.cpp as cam4. You can place it in the same position and orient it in the same direction as cam3. Render orthographic4.jpg image and compare it to perspective3.jpg. Make orthographic4.jpg look similar to perspective3.jpg by adjusting the parameters of cam4 camera.
> Hint: think about the size of the orthographic camera sensor


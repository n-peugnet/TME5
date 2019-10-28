/*
 * PixelJob.h
 *
 *  Created on: 23 oct. 2019
 *      Author: 3872867
 */

#pragma once

#include "Job.h"
#include "Vec3D.h"
#include "Rayon.h"
#include "Scene.h"
#include <vector>

using namespace pr;

Color computeColor(const Sphere &obj, const Rayon &ray, const Vec3D &camera,
		std::vector<Vec3D> &lights);
int findClosestInter(const Scene &scene, const Rayon &ray);
Color computeColor(const Sphere &obj, const Rayon &ray, const Vec3D &camera,
		std::vector<Vec3D> &lights);

namespace pr {

class PixelJob: Job {
	std::vector<Vec3D> &lights;
	Scene &scene;
	int x;
	int y;
	Color *pixels;
public:
	PixelJob(std::vector<Vec3D> lights, Scene &s, int x, int y, Color *pixels) :
			lights(lights), scene(s), x(x), y(y), pixels(pixels) {}
	void run() {
		std::cout << x << ':' << y << std::endl;
		Vec3D screenPoint = scene.getScreenPoints()[x][y];
		Rayon ray(scene.getCameraPos(), screenPoint);

		int targetSphere = findClosestInter(scene, ray);

		if (targetSphere == -1) {
			// keep background color
			return;
		} else {
			const Sphere &obj = *(scene.begin() + targetSphere);
			// pixel prend la couleur de l'objet
			Color finalcolor = computeColor(obj, ray, scene.getCameraPos(),
					lights);
			// le point de l'image (pixel) dont on vient de calculer la couleur
			Color &pixel = pixels[y * scene.getHeight() + x];
			// mettre a jour la couleur du pixel dans l'image finale.
			pixel = finalcolor;
		}
	}
	virtual ~PixelJob() {
	}

private:
};

}  // namespace pr

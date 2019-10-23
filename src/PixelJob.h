/*
 * PixelJob.h
 *
 *  Created on: 23 oct. 2019
 *      Author: 3872867
 */

#pragma once

#include "Job.h"
#include "Scene.h"
#include "Vec3D.h"
#include "Sphere.h"
#include "Rayon.h"
#include "Color.h"

Color computeColor(const Sphere & obj, const Rayon & ray, const Vec3D & camera, std::vector<Vec3D> & lights);

namespace pr {

class PixelJob: Job {
	Scene & scene;
	Vec3D & screenPoint;
public:
	PixelJob(Scene & s, Vec3D screenPoint): scene(s), screenPoint(screenPoint) {
		Rayon  ray(scene.getCameraPos(), screenPoint);

		int targetSphere = findClosestInter(scene, ray);

		if (targetSphere == -1) {
			// keep background color
			continue ;
		} else {
			const Sphere & obj = *(scene.begin() + targetSphere);
			// pixel prend la couleur de l'objet
			Color finalcolor = computeColor(obj, ray, scene.getCameraPos(), lights);
			// le point de l'image (pixel) dont on vient de calculer la couleur
			Color & pixel = pixels[y*scene.getHeight() + x];
			// mettre a jour la couleur du pixel dans l'image finale.
			pixel = finalcolor;
		}
	}


private:
};

}  // namespace pr

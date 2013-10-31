/**
 * osg.cpp - try to find out the number of triangles on the scene
 * usage:	./OSG [osg model]
 * version: 0.1
 * 30/10/2013 by NIE Xin
 * reference: http://trac.openscenegraph.org/projects/osg//browser/OpenSceneGraph/trunk/examples/osggeometry/osggeometry.cpp
 * -------------------------------------------------------------------------------------------------------------------------
 * The idea of finding triangles to create a NodeVisitor visiting go over the scene. For each geodo encountered, go through
 * it's drawables. Then we use the triangle functor to access triangles and push them to a list. So the number of triangles of
 * is equal to the number of elements in this list.
 */

#include <iostream>
#include <string>

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Vec3>
#include <osg/TriangleFunctor>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
#include <osgViewer/Viewer>

class CountTriangles: public osg::NodeVisitor {
public:
	CountTriangles() :
			totalTriangles(0), totalGeodes(0), totalDrawables(0) {
		setTraversalMode(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN);// visit all children
	}

	// triangle functor
	struct GetVertex {
		// triangle vertices
		osg::Vec3Array* vertexList;

		void operator()(const osg::Vec3& v1, const osg::Vec3& v2,
				const osg::Vec3& v3, bool) const {
			vertexList->push_back(v1);
			vertexList->push_back(v2);
			vertexList->push_back(v3);
		}
	};

	// will be called to every Geode
	virtual void apply(osg::Geode& geode) {
		++this->totalGeodes;
		std::cout << "Geode #" << this->totalGeodes << ": " << geode.getName() << std::endl;
		// go through every drawalbe
		for (unsigned int i = 0; i < geode.getNumDrawables(); ++i) {
			++this->totalDrawables;
			osg::Drawable* drawable = geode.getDrawable(i);

			// print some info about drawable
			std::cout << "\t" << "Drawable #" << i + 1 << std::endl;
			std::cout << "\t\t" << "Library: " << drawable->libraryName()
					<< std::endl;
			std::cout << "\t\tClass: " << drawable->className() << std::endl;

			// access to drawable's triangles and put them into a list
			osg::TriangleFunctor<GetVertex> tf;
			tf.vertexList = new osg::Vec3Array;
			drawable->accept(tf);

			// count triangles in the array list
			int triangles = tf.vertexList->getNumElements();
			this->totalTriangles += triangles;
			std::cout << "\t\t" << "Triangles number: "
					<< triangles << std::endl;

		}

		traverse(geode);
	}

	int getTotalTriangles() {
		return this->totalTriangles;
	}

	int getTotalGeodes() {
		return this->totalGeodes;
	}

	int getTotalDrawables() {
		return this->totalDrawables;
	}

protected:
	int totalTriangles;
	int totalGeodes;
	int totalDrawables;
};

int main(int argc, char** argv) {
	// read osg model
	osg::ArgumentParser arguments(&argc, argv);
	osg::ref_ptr<osg::Node> root = osgDB::readNodeFiles(arguments);

	if (!root) {
		OSG_FATAL<< arguments.getApplicationName() << "Loading data error" << std::endl;

		return -1;	// no data loaded
	}

	// counting triangles
	CountTriangles countTriangles;
	root->accept(countTriangles);

	// setup scene view
	osgViewer::Viewer viewer;
	viewer.setSceneData(root.get());


	std::cout << "\nTotal geodes: " << countTriangles.getTotalGeodes() << std::endl;
	std::cout << "Total drawables: " << countTriangles.getTotalDrawables() << std::endl;
	std::cout << "Total triangles: " << countTriangles.getTotalTriangles() << std::endl;

	return viewer.run();
}

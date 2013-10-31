//
//  main.cpp
//  OSG
//
//  Created by Genie on 30/10/2013.
//  Copyright (c) 2013 niexin. All rights reserved.
//
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

int main( int argc, char** argv )
{
    osgViewer::Viewer viewer;
//    viewer.setSceneData( osgDB::readNodeFile("cessna.osg") );
    return viewer.run();
}


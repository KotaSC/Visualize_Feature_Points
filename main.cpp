#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include "importPointClouds.h"
#include "writeSPBR.h"

#include <kvs/PolygonObject>
#include <kvs/PointObject>
#include <kvs/glut/Application>
#include <kvs/glut/Screen>
#include <kvs/Camera>
#include <kvs/PointRenderer>
#include <kvs/Coordinate>

#define ADJUST_POINT_DENSITIES_MODE

const char OUT_FILE[] = "SPBR_DATA/output.spbr";

int main( int argc, char** argv ) {
    char outSPBRfile[128];
    strcpy( outSPBRfile, OUT_FILE );

    if ( argc != 3 ) {
        std::cerr << "USAGE: $ ./vfp [input.spbr] [output.spbr]" << std::endl;
        exit(1);
    } else {
        strcpy( outSPBRfile, argv[2] );
    }

    // Import "point cloud data（.ply, argv[1]）" that user selected
    ImportPointClouds *ply = new ImportPointClouds( argv[1] );
    ply->updateMinMaxCoords();
    std::cout << "\nPLY Min, Max Coords:" << std::endl;
    std::cout << "Min : " << ply->minObjectCoord() << std::endl;
    std::cout << "Max : " << ply->maxObjectCoord() << std::endl;
    std::cout << "Number of points: " << ply->numberOfVertices() << std::endl;


    // Write to SPBR file
    WritingDataType type = Ascii;
    writeSPBR(  ply,
                outSPBRfile,
                type
                );

    // Convert "kvs::PolygonObject" to "kvs::PointObject"
    kvs::PointObject* object = new kvs::PointObject( *ply );
    object->setSize( 1 );
    object->updateMinMaxCoords();

    // Exec. SPBR
    std::string out_noised_spbr( outSPBRfile );
    std::string EXEC("spbr ");
    EXEC += out_noised_spbr;
    system( EXEC.c_str() );

    return 0;
}
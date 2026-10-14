/*
 * Author:
 * 2026/06/26 - Yuqing Liang (BIMCoder Liang)
 * bim.frankliang@foxmail.com
 * 
 *
 * Use of this source code is governed by a LGPL-2.1 license that can be found in
 * the LICENSE file.
 */

#pragma once
#include "XYZ.h"
#include "OctreeCollector.h"
#include <vector>

namespace LNLib
{
    class LNLIB_EXPORT Octant {
    public:
        std::vector<Octant*> Children;
        LNLib::XYZ Center;
        double Extent;
        std::vector<int> PointIndices;
        bool IsLeaf;

        Octant(LNLib::XYZ center, double extent, std::vector<int> indices, bool isLeaf);
        ~Octant();
    };


    bool LNLIB_EXPORT Inside(const LNLib::XYZ& query, double radius, Octant* octant);
    bool LNLIB_EXPORT Overlaps(const LNLib::XYZ& query, double radius, Octant* octant);
    bool LNLIB_EXPORT Contains(const LNLib::XYZ& query, double radius, Octant* octant);


    Octant* LNLIB_EXPORT OctreeConstruction(const std::vector<LNLib::XYZ>& db, int leafSize, double minExtent);

    bool LNLIB_EXPORT OctreeRadiusSearchFast(Octant* root, const std::vector<LNLib::XYZ>& db,
        RadiusNnResultSet& resultSet, const LNLib::XYZ& query);

    bool LNLIB_EXPORT OctreeRadiusSearch(Octant* root, const std::vector<LNLib::XYZ>& db,
        RadiusNnResultSet& resultSet, const LNLib::XYZ& query);

    bool LNLIB_EXPORT OctreeKnnSearch(Octant* root, const std::vector<LNLib::XYZ>& db,
        KnnResultSet& resultSet, const LNLib::XYZ& query);
}
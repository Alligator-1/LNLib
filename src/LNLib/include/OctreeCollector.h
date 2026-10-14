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
#include <vector>
#include <limits>
#include "LNLibDefinitions.h"

namespace LNLib
{
    struct DistIndex {
        double Distance;
        int Index;

        DistIndex() : Distance(std::numeric_limits<double>::max()), Index(0) {}
        DistIndex(double dist, int index) : Distance(dist), Index(index) {}

        bool operator<(const DistIndex& other) const {
            return Distance < other.Distance;
        }
    };

    class LNLIB_EXPORT KnnResultSet{
    public:
        KnnResultSet(int capacity);

        int Size() const;
        bool Full() const;
        double WorstDist() const;
        void AddPoint(double dist, int index);

        // [LNLib C API] expose results for external bindings.
        const std::vector<DistIndex>& Results() const { return DistIndexList; }

    private:
        int Capacity;
        int Count;
        double WorstDistValue;
        std::vector<DistIndex> DistIndexList;
        int ComparisonCounter;
    };

    class LNLIB_EXPORT RadiusNnResultSet {
    public:
        RadiusNnResultSet(double radius);

        int Size() const;
        double WorstDist() const;
        void AddPoint(double dist, int index);

        // [LNLib C API] expose results for external bindings.
        const std::vector<DistIndex>& Results() const { return DistIndexList; }

    private:
        double Radius;
        int Count;
        std::vector<DistIndex> DistIndexList;
        int ComparisonCounter;
    };
}





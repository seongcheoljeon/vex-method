/*
author:         Seongcheol Jeon
created date:   2021.01.05
description:    Houdini Custom Functions 
*/

#ifndef __METHOD_H__
#define __METHOD_H__


#include <voplib.h>

#define     SWAP(a, b)      { a^=b; b^=a; a^=b; }


vector Cam2WorldCoordinate(vector coordinate)
{
    return vtransform("space:camera", "space:world", coordinate);
}


vector Cam2NDCCoordinate(vector coordinate)
{
    return ptransform("space:camera", "space:ndc", coordinate);
}


vector CalcImgResolution(vector direction)
{
    vector resDir;
    renderstate("image:resolution", resDir);
    return resDir * direction;
}


vector CalcOcclusion(vector origin; vector dir; string scope)
{
    return filtershadow(origin, Cam2WorldCoordinate(dir), 0, "scope", scope, "angle", 0, "samples", 0);
}


vector SolveNormal(vector origin; matrix3 dir; string scope)
{
    vector dirx = set(dir.xx, dir.xy, dir.xz);
    vector diry = set(dir.yx, dir.yy, dir.yz);
    vector dirz = set(dir.zx, dir.zy, dir.zz);

    float occx = CalcOcclusion(origin, dirx, scope).x;
    float occy = CalcOcclusion(origin, diry, scope).y;
    float occz = CalcOcclusion(origin, dirz, scope).z;

    return set(occx, occy, occz);
}


vector SolveMotionVector()
{
    vector curtPos = Cam2NDCCoordinate(getblurP(0));
    vector nextPos = Cam2NDCCoordinate(getblurP(1));
    vector diffPos = nextPos - curtPos;
    return CalcImgResolution(diffPos);
}


#endif

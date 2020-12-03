#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <tuple>
#include <vector>
#include <algorithm>
#include <iterator>

namespace calculate_convex
{
    using glm::mat3;
    using glm::vec2;
    using glm::vec3;

    using PointContainer = std::vector<vec2>;

    float calculateTriangleArea(vec2 a, vec2 b, vec2 c)
    {
        mat3 areaMat;
        areaMat[0] = vec3(a.x, b.x, c.x);
        areaMat[1] = vec3(a.y, b.y, c.y);
        areaMat[2] = vec3(1, 1, 1);

        return glm::determinant(areaMat) / 2.0f;
    }

    //line must be a->b
    auto splitPointsWithLineAndCalculatePossitiveArea(const PointContainer &points, vec2 a, vec2 b)
        -> std::tuple<std::vector<float>, PointContainer>
    {
        constexpr float err = 0.001f;
        std::vector<float> areasAboveLine;
        auto areaAboveLinePredFunc = [&areasAboveLine, a, b, err](vec2 i) {
            float area = calculateTriangleArea(a, b, i);
            if (area - err > 0.0f)
            {
                areasAboveLine.push_back(area);
                return true;
            }
            else
                return false;
        };
        PointContainer pointsAboveLine;
        auto aboveLinePointInserter = std::back_inserter(pointsAboveLine);
        std::copy_if(points.begin(), points.end(), aboveLinePointInserter, areaAboveLinePredFunc);
        return {std::move(areasAboveLine), std::move(pointsAboveLine)};
    }

    PointContainer calculate2DConvexOnlyAboveSub(const PointContainer &points, vec2 a, vec2 b)
    {
        auto [aboveAreas, abovePoints] =
            splitPointsWithLineAndCalculatePossitiveArea(points, a, b);
        PointContainer result;

        if (aboveAreas.size() <= 1)
        {
            std::copy(abovePoints.begin(), abovePoints.end(), std::back_inserter(result));
        }
        else
        {
            auto aboveSplitPointPosition = std::max_element(aboveAreas.begin(), aboveAreas.end()) - aboveAreas.begin();
            auto r1 = calculate2DConvexOnlyAboveSub(abovePoints, a, abovePoints[aboveSplitPointPosition]);
            auto r2 = calculate2DConvexOnlyAboveSub(abovePoints, abovePoints[aboveSplitPointPosition], b);
            std::copy(r1.begin(), r1.end(), std::back_inserter(result));
            result.push_back(abovePoints[aboveSplitPointPosition]);
            std::copy(r2.begin(), r2.end(), std::back_inserter(result));
        }
        return result;
    }

    PointContainer calculate2DConvex(const PointContainer &points)
    {
        auto leftPoint = *std::min_element(points.begin(), points.end(), [](auto l, auto r) { return l.x < r.x; });
        auto rightPoint = *std::max_element(points.begin(), points.end(), [](auto l, auto r) { return l.x < r.x; });
        PointContainer result;
        auto r1 = calculate2DConvexOnlyAboveSub(points, leftPoint, rightPoint);
        auto r2 = calculate2DConvexOnlyAboveSub(points, rightPoint, leftPoint);
        result.push_back(leftPoint);
        std::copy(r1.begin(), r1.end(), std::back_inserter(result));
        result.push_back(rightPoint);
        std::copy(r2.begin(), r2.end(), std::back_inserter(result));
        return result;
    }

} // namespace calculate_convex
